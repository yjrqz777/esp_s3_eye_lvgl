#include <stdio.h>
#include <stdlib.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "qma7981.h"
static const char *TAG = "i2c-simple-example";

#define I2C_MASTER_SCL_IO           GPIO_NUM_5      /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           GPIO_NUM_4      /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0           /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          400000                     /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000

#define QMA7981_ADDR                        0x12        /*!< Slave address of the QMA7981 */
#define QMA7981_WHO_AM_I_REG_ADDR           0x00        /*!< Register addresses of the "who am I" register */
#define QMA7981_PWR_MGMT_1_REG_ADDR         0x11        /*!< Register addresses of the power managment register */

#define QMA7981_DXM 0x01											//QMA7981寄存器X轴加速度地址
#define QMA7981_DYM 0x03											//QMA7981寄存器Y轴加速度地址
#define QMA7981_DZM 0x05											//QMA7981寄存器Z轴加速度地址

#define QMA7981_start_convert_cmd 0xC0					//设置QMA7981为active模式的指令

#define QMA7981_MAX_VALUE 0x1FFF							//满量程读数

/**@brief Read a sequence of bytes from a QMA7981 sensor registers*/
static esp_err_t QMA7981_register_read(uint8_t reg_addr, uint8_t *data, size_t len)
{
return i2c_master_write_read_device(I2C_MASTER_NUM, QMA7981_ADDR, &reg_addr, 1, data, len, I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);
}

/**@brief Write a byte to a QMA7981 sensor register*/
static esp_err_t QMA7981_register_write_byte(uint8_t reg_addr, uint8_t data)
{
int ret;
uint8_t write_buf[2] = {reg_addr, data};
ret = i2c_master_write_to_device(I2C_MASTER_NUM, QMA7981_ADDR, write_buf, sizeof(write_buf), I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);
return ret;
}

/**@brief i2c master initialization*/
static esp_err_t i2c_master_init(void)
{

int i2c_master_port = I2C_MASTER_NUM;

i2c_config_t conf = {
    .mode = I2C_MODE_MASTER,
    .sda_io_num = I2C_MASTER_SDA_IO,
    .scl_io_num = I2C_MASTER_SCL_IO,
    .sda_pullup_en = GPIO_PULLUP_ENABLE,
    .scl_pullup_en = GPIO_PULLUP_ENABLE,
    .master.clk_speed = I2C_MASTER_FREQ_HZ,
};

i2c_param_config(i2c_master_port, &conf);
return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

Kalman_Typedef bias_Kalman;

double KalmanFilter(Kalman_Typedef *klm, double input)
{
    //预测协方差方程：k时刻系统估算协方差 = k-1时刻的系统协方差 + 过程噪声协方差
    klm->Now_P = klm->LastP + klm->Q;
    //卡尔曼增益方程：卡尔曼增益 = k时刻系统估算协方差 / （k时刻系统估算协方差 + 观测噪声协方差）
    klm->Kg = klm->Now_P / (klm->Now_P + klm->R);
    //更新最优值方程：k时刻状态变量的最优值 = 状态变量的预测值 + 卡尔曼增益 * （测量值 - 状态变量的预测值）
    klm->out = klm->out + klm->Kg * (input -klm->out);//因为这一次的预测值就是上一次的输出值
    //更新协方差方程: 本次的系统协方差赋给 klm->LastP 为下一次运算准备。
    klm->LastP = (1-klm->Kg) * klm->Now_P;
	
	return (klm->out);
}

void Kalman_Init(Kalman_Typedef *klm, const double klm_Q, const double klm_R)//温度klm_Q=0.01 klm_R=0.25
{
	klm->LastP=0.02;		//上次估算协方差
	klm->Now_P=0;			//当前估算协方差
	klm->out=0;				//卡尔曼滤波器输出
	klm->Kg=0;				//卡尔曼增益
	klm->Q=klm_Q;			//Q:过程噪声协方差 Q参数调滤波后的曲线平滑程度，Q越小越平滑;
	klm->R=klm_R;			//R:观测噪声协方差 R参数调整滤波后的曲线与实测曲线的相近程度，R越小越接近(收敛越快)
}

static int do_i2cdetect_cmd()
{
    uint8_t address;
    printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\r\n");
    for (int i = 0; i < 128; i += 16) {
        printf("%02x: ", i);
        for (int j = 0; j < 16; j++) {
            fflush(stdout);
            address = i + j;
            i2c_cmd_handle_t cmd = i2c_cmd_link_create();
            i2c_master_start(cmd);
            i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, 0x1);
            i2c_master_stop(cmd);
            esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 50 / portTICK_PERIOD_MS);
            i2c_cmd_link_delete(cmd);
            if (ret == ESP_OK) {
                printf("%02x ", address);
            } else if (ret == ESP_ERR_TIMEOUT) {
                printf("UU ");
            } else {
                printf("-- ");
            }
        }
        printf("\r\n");
    }

    // i2c_driver_delete(I2C_MASTER_NUM);
    return 0;
}

void qma7981_main(void)
{
    uint8_t data[2];
    
    int16_t XA;
    int16_t YA;
    int16_t ZA;
    Kalman_Init(&bias_Kalman,1e-5,0.01);
    float X_AXIS_A;
    float Y_AXIS_A;
    float Z_AXIS_A;
    
    ESP_ERROR_CHECK(i2c_master_init());		//初始化I2C
    do_i2cdetect_cmd();
    ESP_LOGI(TAG, "I2C initialized successfully");
    ESP_ERROR_CHECK(QMA7981_register_read(QMA7981_WHO_AM_I_REG_ADDR, data, 1));		//读取设备ID，正常是0xE7
    ESP_LOGI(TAG, "WHO_AM_I = %X", data[0]);
    ESP_ERROR_CHECK(QMA7981_register_write_byte(QMA7981_PWR_MGMT_1_REG_ADDR, QMA7981_start_convert_cmd));		//设置为active模式
    
    while(1)
    {	//读取和转换
        ESP_ERROR_CHECK(QMA7981_register_read(QMA7981_DXM, data, 2));
        XA = (data[0] & 0xFC) | (data[1]<< 8);
        ESP_ERROR_CHECK(QMA7981_register_read(QMA7981_DYM, data, 2));
        YA = (data[0] & 0xFC) | (data[1]<< 8);
        ESP_ERROR_CHECK(QMA7981_register_read(QMA7981_DZM, data, 2));
        ZA = (data[0] & 0xFC) | (data[1]<< 8);
        
        XA /= 4;
        YA /= 4;
        ZA /= 4;
        
        X_AXIS_A = (float) XA / QMA7981_MAX_VALUE * 2;
        Y_AXIS_A = (float) YA / QMA7981_MAX_VALUE * 2;
        Z_AXIS_A = (float) ZA / QMA7981_MAX_VALUE * 2;
        // printf("X_RAW = %d , Y_RAW = %d , Z_RAW = %d . \n", XA, YA, ZA);
        // printf("X_A = %.3f g, Y_A = %.3f g, Z_A = %.3f g. \n", X_AXIS_A, Y_AXIS_A, Z_AXIS_A);

        KalmanFilter(&bias_Kalman, X_AXIS_A);
        X_AXIS_A=bias_Kalman.out;


        // printf("%.3f,%.3f,%.3f\n", X_AXIS_A, Y_AXIS_A, Z_AXIS_A);
        // vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
