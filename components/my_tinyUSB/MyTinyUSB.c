
#include "esp_log.h"
#include "MyTinyUSB.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"



#include <errno.h>
#include <dirent.h>
#include "esp_check.h"
#include "tinyusb.h"
#include "tusb_msc_storage.h"
#include "diskio_impl.h"
#include "diskio_sdmmc.h"



// #include "sd_fat_fs.h"


static const char *TAG = "MyTinyUSB";

// /* TinyUSB descriptors
//    ********************************************************************* */
// #define EPNUM_MSC       1
// #define TUSB_DESC_TOTAL_LEN (TUD_CONFIG_DESC_LEN + TUD_MSC_DESC_LEN)

// enum {
//     ITF_NUM_MSC = 0,
//     ITF_NUM_TOTAL
// };

// enum {
//     EDPT_CTRL_OUT = 0x00,
//     EDPT_CTRL_IN  = 0x80,

//     EDPT_MSC_OUT  = 0x01,
//     EDPT_MSC_IN   = 0x81,
// };

// static uint8_t const desc_configuration[] = {
//     // Config number, interface count, string index, total length, attribute, power in mA
//     TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, TUSB_DESC_TOTAL_LEN, TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP, 100),

//     // Interface number, string index, EP Out & EP In address, EP size
//     TUD_MSC_DESCRIPTOR(ITF_NUM_MSC, 0, EDPT_MSC_OUT, EDPT_MSC_IN, TUD_OPT_HIGH_SPEED ? 512 : 64),
// };

// static tusb_desc_device_t descriptor_config = {
//     .bLength = sizeof(descriptor_config),
//     .bDescriptorType = TUSB_DESC_DEVICE,
//     .bcdUSB = 0x0200,
//     .bDeviceClass = TUSB_CLASS_MISC,
//     .bDeviceSubClass = MISC_SUBCLASS_COMMON,
//     .bDeviceProtocol = MISC_PROTOCOL_IAD,
//     .bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE,
//     .idVendor = 0x303A, // This is Espressif VID. This needs to be changed according to Users / Customers
//     .idProduct = 0x4002,
//     .bcdDevice = 0x100,
//     .iManufacturer = 0x01,
//     .iProduct = 0x02,
//     .iSerialNumber = 0x03,
//     .bNumConfigurations = 0x01
// };

// static char const *string_desc_arr[] = {
//     (const char[]) { 0x09, 0x04 },  // 0: is supported language is English (0x0409)
//     "TinyUSB",                      // 1: Manufacturer
//     "TinyUSB Device",               // 2: Product
//     "123456",                       // 3: Serials
//     "Example MSC",                  // 4. MSC
// };
// /*********************************************************************** TinyUSB descriptors*/

// #define BASE_PATH "/sdcard" // base path to mount the partition



// static void _mount(void)
// {
//     ESP_LOGI(TAG, "Mount storage...");
//     ESP_ERROR_CHECK(tinyusb_msc_storage_mount(BASE_PATH));


//     // List all the files in this directory
//     ESP_LOGI(TAG, "\nls command output:");
//     struct dirent *d;
//     DIR *dh = opendir(BASE_PATH);
//     if (!dh) {
//         if (errno == ENOENT) {
//             //If the directory is not found
//             ESP_LOGE(TAG, "Directory doesn't exist %s", BASE_PATH);
//         } else {
//             //If the directory is not readable then throw error and exit
//             ESP_LOGE(TAG, "Unable to read directory %s", BASE_PATH);
//         }
//         return;
//     }
//     //While the next entry is not readable we will print directory files
//     while ((d = readdir(dh)) != NULL) {
//         printf("%s\n", d->d_name);
//     }
//     return;
// }


void MyTinyUSB_Main(void)
{
//     // xTaskCreate(test_picture, "test_picture", 4096*10, NULL, 2, NULL);
//     // test_picture();

//     ESP_LOGI(TAG,"MyTinyUSB_Main called\n");


//     ESP_LOGI(TAG, "Initializing storage...");

//     static sdmmc_card_t *card = NULL;
//     // ESP_ERROR_CHECK(storage_init_sdmmc(&card));

//     const tinyusb_msc_sdmmc_config_t config_sdmmc = {
//         .card = card
//     };
//     ESP_ERROR_CHECK(tinyusb_msc_storage_init_sdmmc(&config_sdmmc));

//     //mounted in the app by default
//     _mount();

//     ESP_LOGI(TAG, "USB MSC initialization");
//     const tinyusb_config_t tusb_cfg = {
//         .device_descriptor = &descriptor_config,
//         .string_descriptor = string_desc_arr,
//         .string_descriptor_count = sizeof(string_desc_arr) / sizeof(string_desc_arr[0]),
//         .external_phy = false,
//         .configuration_descriptor = desc_configuration,
//     };
//     ESP_ERROR_CHECK(tinyusb_driver_install(&tusb_cfg));
//     ESP_LOGI(TAG, "USB MSC initialization DONE");

    while (1)
    {
        ESP_LOGI(TAG,"called\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    

}


