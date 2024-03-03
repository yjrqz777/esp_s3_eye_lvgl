| Supported Targets | ESP32-S3 |
| ----------------- | -------- |

# esp_s3_eye_lvgl
# lvgl:8.3.10
# esp_idf:5.04
# st7789 240x240


Online Image Converter : https://lvgl.io/tools/imageconverter

在线gif剪切网站 : https://tool.lu/gifscaler/


中文字体转换网站 : https://lvgl.io/tools/fontconverter 注意 字体后缀ttf，必须小写


添加freertos—pdf

2024年2月29日21:31:37：测试usb console 但是必须使用串口芯片，usb串口无法接收数据，故失败

2024年3月3日20:16:59：
squareline设计ui 实现加载wifi名称
set_property(TARGET ${COMPONENT_LIB} APPEND PROPERTY LINK_INTERFACE_MULTIPLICITY 3) 设置相互依赖组



