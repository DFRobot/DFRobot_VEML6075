# VEML6075

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

## DFRobot_VEML6075 Library for Arduino

  - [Summary](#summary)
  - [Feature](#feature)
  - [Installation](#installation)
  - [Methods](#methods)
  - [Compatibility](#compatibility)
  - [Credits](#credits)

## Summary

<pre>
Get UVA, UVB and UVI with data from VEML6075.
These data are printed out through the serial port.
Use API to config module.
</pre>

## Feature

<pre>
* Connect modules through IIC.
* Test config through Serial.
* Get all raw data from module, convert raw data into UV index.
</pre>

## Installation

For Arduino
<pre>
Download this library and unzip it to Arduino librarys folder.
</pre>

For Raspberry
<pre>
Download this library and unzip it to a privileged path.
</pre>

## Methods

```cpp

/**
 * @brief Class define of VEML6075 that connect through IIC.
 *
 * @param pWire class TwoWire pointer
 * @param addr Module's IIC addr.
 */
class DFRobot_VEML6075_IIC(TwoWire* pWire, uint8_t addr);

/**
 * @brief Begin.
 *
 * @return Result of begin.
 *  @retval true Begin successed.
 *  @retval false Begin faild.
 */
boolean begin();

// power status define
typedef enum {
  eVEML6075PowerOn,
  eVEML6075PowerOff
} eVEML6075Power_t;

/**
 * @brief Set power on or off.
 *
 * @param ePower The status you want to set.
 */
void setPower(eVEML6075Power_t ePower);

/**
 * @brief Get power status.
 *
 * @return Status of power.
 */
eVEML6075Power_t getPower();

// Active force mode define
typedef enum {
  eVEML6075ActiveForceModeDisable,
  eVEML6075ActiveForceModeEnable,
} eVEML6075ActiveForceMode_t;

/**
 * @brief Set active force mode enable or disable.
 *
 * @param eMode The status you want to set.
 */
void setActiveForceMode(eVEML6075ActiveForceMode_t eMode);

/**
 * @brief Get active force mode status.
 *
 * @return Status of active force mode.
 */
eVEML6075ActiveForceMode_t getActiveForceMode();

/**
 * @brief Trigger one measurement if active force mode is enable.
 */
void trigOneMeasurement();

// Dynamic status define
typedef enum {
  eVEML6075DynamicNormal,
  eVEML6075DynamicHigh
} eVEML6075Dynamic_t;

/**
 * @brief Set dynamic status.
 *
 * @param eDynamic The status you want to set.
 */
void setDynamic(eVEML6075Dynamic_t eDynamic);

/**
 * @brief Get dynamic status.
 *
 * @return Status of dynamic.
 */
eVEML6075Dynamic_t getDynamic();

// Integration time define
typedef enum {
  eVEML6075UV_IT_50,
  eVEML6075UV_IT_100,
  eVEML6075UV_IT_200,
  eVEML6075UV_IT_400,
  eVEML6075UV_IT_800
} eVEML6075UV_IT_t;

/**
 * @brief Set integration time status.
 *
 * @param eUV_IT The status you want to set.
 */
void setIntegrationTime(eVEML6075UV_IT_t eUV_IT);

/**
 * @brief Get dynamic status.
 *
 * @return Status of integration time.
 */
eVEML6075UV_IT_t getIntegrationTime();

/**
 * @brief Get UVA raw data.
 *
 * @return Raw data of UVA.
 */
uint16_t readUvaRaw();

/**
 * @brief Get UVB raw data.
 *
 * @return Raw data of UVB.
 */
uint16_t readUvbRaw();

/**
 * @brief Get UV compare1 raw data.
 *
 * @return Raw data of UV compare1.
 */
uint16_t readUvComp1Raw();

/**
 * @brief Get UV compare2 raw data.
 *
 * @return Raw data of UV compare2.
 */
uint16_t readUvComp2Raw();

/**
 * @brief Get UVA.
 *
 * @return UVA.
 */
float getUva();

/**
 * @brief Get UVB.
 *
 * @return UVB.
 */
float getUvb();

/**
 * @brief Get UV index.
 *
 * @return UV index.
 */
float getUvi(float Uva, float Uvb);

```

Python methods is similar to cpp

```py

class DFRobot_VEML6075:

  def __init__(self, i2cBus, addr):

  def begin(self):

  POWER_ON = 0x00
  POWER_OFF = 0x01

  def setPower(self, power):

  def getPower(self):

  ACTIVE_FORCE_ENABLE = 0x02
  ACTIVE_FORCE_DISABLE = 0x00

  def setActiveForceMode(self, isEnable):

  def getActiveForceMode(self):

  def trigOneMeasurement(self):

  DYNAMIC_NORMAL = 0x00
  DYNAMIC_HIGH = 0x08

  def setDynamic(self, dynamic):

  def getDynamic(self):

  UV_IT_50 = 0x00
  UV_IT_100 = 0x10
  UV_IT_200 = 0x20
  UV_IT_400 = 0x30
  UV_IT_800 = 0x40

  def setIntegrationTime(self, t):

  def getIntegrationTime(self):

  def readUvaRaw(self):

  def readUvbRaw(self):

  def readUvComp1Raw(self):
  
  def readUvComp2Raw(self):

  def getUva(self):

  def getUvb(self):

  def getUvi(self, Uva, Uvb):

  def Uvi2mwpcm2(self, Uvi):

```

## Compatibility

MCU                | Work Well | Not Work Well | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
FireBeetle-ESP32  |      √       |             |            | 
FireBeetle-ESP8266  |      √       |             |            | 
FireBeetle-328P |      √       |             |            | 

MCU                | Work Well | Not Work Well | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
3b  |      √       |             |            | 

## Credits

* author [xiaowo jiehan.guo@dfrobot.com]
