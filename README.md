# 基于Qt和STM32的加密密码管理系统
## 概述
该项目实现了一个综合的加密密码管理系统，涵盖了密码的加密存储、查看与修改等功能，并通过自定义控件和QSS提供了美观且易用的用户界面。
系统在PC端基于Qt框架开发，采用QCA库进行加解密操作，并将加密后的密码数据存储到SQLite数据库中。
通过串口与STM32开发板进行数据通信，从而能将更敏感的加密数据传输并存储到连接的EEPROM中，STM32端运行FreeRTOS进行数据管理，并利用指纹识别外设进行身份验证，进一步增强了系统的安全性。
## 文件组织
### driver_and_application
存放STM32的驱动、应用代码

### freerots_src
FreeRTOS的源码，并未做裁剪

### stm32_src
STM32的部分标准库源码，只存放了中需要用到的标准库文件

### stm32_freertos_main
存放STM32的main.cpp

### qt_src
Qt上位机的代码

## 环境

Qt:6.5.3，需要移植QCA库，或者在strDecryption和strEncryption方法中实现自己的加解密;

STM32F103C8T6;

EEPOM:AT24C256;

指纹识别模块：AS608;

## ...
![image](https://github.com/user-attachments/assets/de6c5c23-1f54-440a-b409-62d8217b85cc)
