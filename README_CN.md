# DFRobot_VEML6075
- [English Version](./README.md)

VEML6075能感知UVA和UVB光线并融合光电二极管、放大器和模拟/数字电路使用CMOS工艺的单芯片。当紫外线传感器是应用时，它能够检测UVA和UVB强度提供一个信号强度的测量方法，同时支持UVI测量.<br>
VEML6075提供卓越的温度补偿在变化的情况下保持输出稳定的能力温度。VEML6075的功能很容易通过I2C的简单命令格式(兼容SMBus)接口协议。VEML6075工作电压范围从1.7 V到3.6 V。VEML6075采用无铅包装4引脚OPLGA封装，提供了最好的市场证明可靠性。<br>


![](./resources/images/SEN0303.png)


## 产品链接(https://www.dfrobot.com.cn/goods-2007.html)

    SKU：SEN0303

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性)
* [历史](#历史)
* [创作者](#创作者)
 
## 概述

1. 从VEML6075获取UVA, UVB和UVI数据
2. 这些数据是通过串口打印出来的
3. 使用API去配置传感器模块

## 库安装

这里提供两种使用本库的方法：
1. 打开Arduino IDE,在状态栏中的Tools--->Manager Libraries 搜索"DFRobot_VEML6075"并安装本库.
2. 首先下载库文件,将其粘贴到\Arduino\libraries目录中,然后打开examples文件夹并在该文件夹中运行演示.


## 方法

```C++

  /**
   * @fn begin
   * @brief 初始化函数
   * @return bool类型，返回初始化结果
   * @retval true 初始化成功
   * @retval fasle 初始化失败
   */
  boolean begin();

  /**
   * @fn setPower
   * @brief set power
   * @param ePower
   * @n       eVEML6075PowerOn    power on
   * @n       eVEML6075PowerOff   power off
   */
  void setPower(eVEML6075Power_t ePower);

  /**
   * @fn setActiveForceMode
   * @brief 设置active force 模式
   * @param eMode
   * @n       eVEML6075ActiveForceModeDisable    关闭 active force 模式
   * @n       eVEML6075ActiveForceModeEnable     使能 active force 模式
   */
  void setActiveForceMode(eVEML6075ActiveForceMode_t eMode);

  /**
   * @fn trigOneMeasurement
   * @brief 尝试一次测试
   */
  void trigOneMeasurement();

  /**
   * @fn setDynamic
   * @brief 设置动态环境
   * @param eDynamic
   * @n       eVEML6075DynamicNormal    正常动态环境
   * @n       eVEML6075DynamicHigh      高动态环境
   */
  void setDynamic(eVEML6075Dynamic_t eDynamic);

  /**
   * @fn setIntegrationTime
   * @brief 设置积分时间
   * @param eUV_IT
   * @n       eVEML6075UV_IT_50    50ms
   * @n       eVEML6075UV_IT_100   100ms
   * @n       eVEML6075UV_IT_200   200ms
   * @n       eVEML6075UV_IT_400   400ms
   * @n       eVEML6075UV_IT_800   800ms
   */
  void setIntegrationTime(eVEML6075UV_IT_t eUV_IT);

  /**
   * @fn getPower
   * @brief get Power
   * @return  工作状态
   * @retval    eVEML6075PowerOn    开启工作
   * @retval    eVEML6075PowerOff   停止工作
   */
  eVEML6075Power_t getPower();

  /**
   * @fn getActiveForceMode
   * @brief 获取传感器的active force 模式信息
   * @return  Mode
   * @retval    eVEML6075ActiveForceModeDisable    VEML6075 active force 模式未开启
   * @retval    eVEML6075ActiveForceModeEnable     VEML6075 active force 模式开启
   */
  eVEML6075ActiveForceMode_t getActiveForceMode();

  /**
   * @fn getDynamic
   * @brief 获取传感器的Dynamic设置信息
   * @return  Mode
   * @retval    eVEML6075DynamicNormal    设置的正常动态环境
   * @retval    eVEML6075DynamicHigh      设置的高动态环境
   */
  eVEML6075Dynamic_t getDynamic();

  /**
   * @fn getIntegrationTime
   * @brief 获取传感器的积分时间
   * @return  IntegrationTime
   * @retval    eVEML6075UV_IT_50    50ms
   * @retval    eVEML6075UV_IT_100   100ms
   * @retval    eVEML6075UV_IT_200   200ms
   * @retval    eVEML6075UV_IT_400   400ms
   * @retval    eVEML6075UV_IT_800   800ms
   */
  eVEML6075UV_IT_t getIntegrationTime();


  /**
   * @fn readUvaRaw
   * @brief 读取传感器在UVA波段收集原始数据
   * @return  UVA 原始数据
   */
  uint16_t readUvaRaw();

  /**
   * @fn readUvbRaw
   * @brief 读取传感器在UVB波段收集原始数据
   * @return  UVB 原始数据
   */
  uint16_t readUvbRaw();

  /**
   * @fn readUvComp1Raw
   * @brief 读取传感器在UvComp1中收集原始数据
   * @return  UvComp1 原始数据
   */
  uint16_t readUvComp1Raw();

  /**
   * @fn readUvComp2Raw
   * @brief 读取传感器在UvComp2中收集原始数据
   * @return  UvComp2 原始数据
   */
  uint16_t readUvComp2Raw();

  /**
   * @fn getUva
   * @brief 根据采集的数据计算出紫外线的UVA波段数据
   * @return  UVA 数据
   */
  float getUva();

  /**
   * @fn getUvb
   * @brief 根据采集的数据计算出紫外线的UVB波段数据
   * @return  UVB 数据
   */
  float getUvb();

  /**
   * @fn getUvb
   * @brief 根据采集到的数据计算出紫外线波段数据
   * @return  UVI 数据
   */
  float getUvi(float Uva, float Uvb);
```

## 兼容性

| 主板          | 通过 | 未通过 | 未测试 | 备注 |
| ------------- | :--: | :----: | :----: | ---- |
| Arduino uno   |  √   |        |        |      |
| Mega2560      |  √   |        |        |      |
| Leonardo      |  √   |        |        |      |
| ESP32         |  √   |        |        |      |
| micro:bit     |      |    √   |        |      |
| FireBeetle M0 |  √   |        |        |      |


## 历史

- 2021/10/18 - 1.0.1 版本
- 2018/12/18 - 1.0.0 版本

## 创作者

Written by yangfeng(feng.yang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))
