| Supported Targets | ESP32-S3 |
| ----------------- | -------- |

# esp_s3_eye_lvgl
# lvgl:8.3.10
# esp_idf:5.04
# st7789 240x240
# rlottie master


Online Image Converter : https://lvgl.io/tools/imageconverter

在线gif剪切网站 : https://tool.lu/gifscaler/


中文字体转换网站 : https://lvgl.io/tools/fontconverter 注意 字体后缀ttf，必须小写


添加freertos—pdf

2024年2月29日21:31:37：测试usb console 但是必须使用串口芯片，usb串口无法接收数据，故失败

2024年3月3日20:16:59：
squareline设计ui 实现加载wifi名称
set_property(TARGET ${COMPONENT_LIB} APPEND PROPERTY LINK_INTERFACE_MULTIPLICITY 3) 设置相互依赖组

https://api.m.taobao.com/rest/api3.do?api=mtop.common.getTimestamp



2024年3月14日21:43:43： 加入获取网络时间
 | 2024年3月15日
成功

2024年7月15日23:54:31 擦拭flash
esptool.py --port COM3 erase_flash


2024年7月21日16:25:02 ~~用巴发云测试OTA~~


2024年7月24日23:35:32 IDF使用5.1.2

2024年7月27日12:55:22 squareline 项目丢失，重新构建并上传

2024年7月29日23:40:31 ~~尝试使用tinyUSB使用MSC 未成功运行失败~~


2025年3月29日17:01:01 del tinyUSB 移植 rlottie 在第四页 lvgl fs ok