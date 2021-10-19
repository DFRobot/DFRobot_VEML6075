# DFRobot_VEML6075

- [中文版](./README_CN.md)

  The VEML6075 senses UVA and UVB light and incorporates
photodiode, amplifiers, and analog / digital circuits into a
single chip using a CMOS process. When the UV sensor is
applied, it is able to detect UVA and UVB intensity to provide
a measure of the signal strength as well as allow for UVI
measurement. </br>

  The VEML6075 provides excellent temperature compensation
capability for keeping the output stable under changing
temperature. VEML6075’s functionality is easily operated via
the simple command format of I2C (SMBus compatible)
interface protocol. VEML6075’s operating voltage ranges
from 1.7 V to 3.6 V. VEML6075 is packaged in a lead (Pb)-free
4 pin OPLGA package which offers the best market-proven
reliability. <br>

![](./resources/images/SEN0303.png)

## Product Link(https://www.dfrobot.com/product-1906.html)

    SKU：SEN0303

## Table of Contents
* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

1. Get UVA, UVB and UVI with data from VEML6075.<br>
2. These data are printed out through the serial port.<br>
3. Use API to config module.<br>

## Installation

There are two ways to use the library:
1. Open the Arduino IDE, search for "DFRobot_VEML6075" in Tools --> Manager Libraries on the status bar, and install the library.
2. First download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in that folder.


## Methods

```C++

  /**
   * @fn begin
   * @brief initialization function
   * @return bool,returns the initialization status
   * @retval true Initialization succeeded
   * @retval fasle Initialization  failed
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
   * @brief set active force mode
   * @param eMode
   * @n       eVEML6075ActiveForceModeDisable    VEML6075 active force mode disable
   * @n       eVEML6075ActiveForceModeEnable     VEML6075 active force mode enable
   */
  void setActiveForceMode(eVEML6075ActiveForceMode_t eMode);

  /**
   * @fn trigOneMeasurement
   * @brief Trigger a measurement
   */
  void trigOneMeasurement();

  /**
   * @fn setDynamic
   * @brief set Dynamic
   * @param eDynamic
   * @n       eVEML6075DynamicNormal    normal dynamic setting
   * @n       eVEML6075DynamicHigh      high dynamic setting
   */
  void setDynamic(eVEML6075Dynamic_t eDynamic);

  /**
   * @fn setIntegrationTime
   * @brief set integration time
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
   * @brief getPower
   * @return  Power status
   * @retval    eVEML6075PowerOn    power on
   * @retval    eVEML6075PowerOff   power off
   */
  eVEML6075Power_t getPower();

  /**
   * @fn getActiveForceMode
   * @brief get active force mode
   * @return  Mode
   * @retval    eVEML6075ActiveForceModeDisable    VEML6075 active force mode disable
   * @retval    eVEML6075ActiveForceModeEnable     VEML6075 active force mode enable
   */
  eVEML6075ActiveForceMode_t getActiveForceMode();

  /**
   * @fn getDynamic
   * @brief get Dynamic
   * @return  Mode
   * @retval    eVEML6075DynamicNormal    normal dynamic setting
   * @retval    eVEML6075DynamicHigh      high dynamic setting
   */
  eVEML6075Dynamic_t getDynamic();

  /**
   * @fn getIntegrationTime
   * @brief get integration time
   * @return  integration time
   * @retval    eVEML6075UV_IT_50    50ms
   * @retval    eVEML6075UV_IT_100   100ms
   * @retval    eVEML6075UV_IT_200   200ms
   * @retval    eVEML6075UV_IT_400   400ms
   * @retval    eVEML6075UV_IT_800   800ms
   */
  eVEML6075UV_IT_t getIntegrationTime();


  /**
   * @fn readUvaRaw
   * @brief The reading sensor collects raw data in the UVA band
   * @return  UVA Raw
   */
  uint16_t readUvaRaw();

  /**
   * @fn readUvbRaw
   * @brief The reading sensor collects raw data in the UVB band
   * @return  UVB Raw
   */
  uint16_t readUvbRaw();

  /**
   * @fn readUvComp1Raw
   * @brief The reading sensor collects raw data in the UvComp1
   * @return  UvComp1 Raw
   */
  uint16_t readUvComp1Raw();

  /**
   * @fn readUvComp2Raw
   * @brief The reading sensor collects raw data in the UvComp2
   * @return  UvComp2 Raw
   */
  uint16_t readUvComp2Raw();

  /**
   * @fn getUva
   * @brief The UVA band data of ultraviolet ray are calculated according to the data collected
   * @return  UVA data
   */
  float getUva();

  /**
   * @fn getUvb
   * @brief The UVB band data of ultraviolet ray are calculated according to the data collected
   * @return  UVB data
   */
  float getUvb();

  /**
   * @fn getUvb
   * @brief The UVI band data of ultraviolet ray are calculated according to the data collected
   * @return  UVI data
   */
  float getUvi(float Uva, float Uvb);
```

## Compatibility

| Board         | Work Well | Work Wrong | Untested | Remarks |
| ------------- | :-------: | :--------: | :------: | ------- |
| Arduino uno   |     √     |            |          |         |
| Mega2560      |     √     |            |          |         |
| Leonardo      |     √     |            |          |         |
| ESP32         |     √     |            |          |         |
| micro:bit     |           |      √     |          |         |
| FireBeetle M0 |     √     |            |          |         |

## History

- 2021/10/18 - Version 1.0.1 released.
- 2018/12/18 - Version 1.0.0 released.


## Credits

Written by Fary(feng.yang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))

