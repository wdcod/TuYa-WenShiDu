# TuYa-WenShiDu
涂鸦温湿度传感器
This project is developed using Tuya SDK, which enables you to quickly develop branded
apps connecting and controlling smart scenarios of many devices.
For more information, please check Tuya Developer Website.

可以连接WIFI，将温湿度信息、亮度信息上传到涂鸦物联平台，单片机使用国产的CKS32F031K6T6，价格低、引脚多，可完全兼容ST同型号单片机。
It can be connected to WiFi and upload the temperature, humidity and brightness information to the graffiti IOT platform. The single chip microcomputer uses the domestic cks32f031k6t6 with low price and many pins, which is fully compatible with the same model of St single chip microcomputer.


温湿度传感器采用SHT30，亮度信息通过光敏电阻采集，红外感应可与OLED屏幕配合，进行低功耗管理，有人走过或者在模块前挥手，OLED才显示。
The temperature and humidity sensor adopts sht30, the brightness information is collected through the photosensitive resistance, and the infrared induction can cooperate with the OLED screen for low-power management. Only when someone walks by or waves in front of the module can the OLED display.


OLED采用排针+排母方式连接，更方便DIY，电池供电采用大电流、低压降的芯片，外接锂电池可以带充放电一体模块，最高支持6V，锂电池包可放在OLED屏幕下。
OLED uses pin + bus connection, which is more convenient for DIY. The battery power supply adopts chip with high current and low voltage drop. The external lithium battery can be equipped with integrated charging and discharging module, which can support up to 6V. The lithium battery pack can be placed under the OLED screen.


目前代码已经把温湿度、亮度信息上报完成，因为暂时没有锂电池，所以没有电池信息上报，预留了接口和位置，加了锂电池可以直接用ADC读取数值后上报。
21
At present, the code has reported the temperature, humidity and brightness information. Because there is no lithium battery for the time being, there is no battery information reporting. The interface and location are reserved. With the lithium battery added, the value can be directly read by ADC and reported.


OLED屏幕可以显示各种信息，比如温湿度、亮度等等。OLED库封装了一些函数，目前显示的是各个传感器的值，用户可以直接在while(1)修改自己想要的格式。
24
OLED screen can display all kinds of information, such as temperature, humidity, brightness and so on. OLED library encapsulates some functions. At present, it displays the values of each sensor. Users can directly modify the format they want in while (1).

额外外引了一组IIC和串口，可以添加其他东西并方便调试。 代码使用STM32Cube IDE编写，打开.project即可
29
​


额外外引了一组IIC和串口，可以添加其他东西并方便调试。 代码使用STM32Cube IDE编写，打开.project即可

