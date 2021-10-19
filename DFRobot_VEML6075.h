
/*!
 * @file DFRobot_VEML6075.h
 * @brief DFRobot_VEML6075 class infrastructure
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [xiaowo] (jiehan.guo@dfrobot.com)
 * @maintainer [Fary](feng.yang@dfrobot.com)
 * @version  V1.0
 * @date  2021-10-18
 * @url https://github.com/DFRobot/DFRobot_VEML6075
 */
#ifndef DFROBOT_VEML6075_H
#define DFROBOT_VEML6075_H

#include <Arduino.h>
#include <Wire.h>

#define VEML6075_ID_DEFAULT     0x26
#define VEML6075_ADDR           0x10
  
#define UVI_LOW                 2.0f
#define UVI_MODERATE            5.0f
#define UVI_HIGH                7.0f
#define UVI_VERY_HIGH           10.0f
#define UVI_EXTREME             12.0f
#define Uvi2mwpcm2(UVI)         (UVI * 0.0025f)

#define VEML6075_CONF           0x00
#define VEML6075_CONF_DEFAULT   0x00
#define VEML6075_UVA            0x07
#define VEML6075_UVB            0x09
#define VEML6075_UV_COMP1       0x0a
#define VEML6075_UV_COMP2       0x0b
#define VEML6075_ID             0x0c

/**
 * @enum eVEML6075Power_t
 * @brief set power
 */
typedef enum {
  eVEML6075PowerOn,      /**< power on */
  eVEML6075PowerOff      /**< power off */
} eVEML6075Power_t;

/**
 * @enum eVEML6075ActiveForceMode_t
 * @brief set active force mode
 */
typedef enum {
  eVEML6075ActiveForceModeDisable,    /**< VEML6075 active force mode disable */
  eVEML6075ActiveForceModeEnable,     /**< VEML6075 active force mode enable */
} eVEML6075ActiveForceMode_t;

#define VEML6075_TRIG_ONE_MEASUREMENT   1   /**< write to register VEML6075_REG_CONFIG_UV_TRIG to start one measurement if VEML6075_REG_CONFIG_UV_AF = 1 */

/**
 * @enum eVEML6075Dynamic_t
 * @brief write to register VEML6075_REG_CONFIG_HD to set dynamic
 */
typedef enum {
  eVEML6075DynamicNormal,   /**< normal dynamic setting */
  eVEML6075DynamicHigh      /**< high dynamic setting */
} eVEML6075Dynamic_t;

/**
 * @enum eVEML6075UV_IT_t
 * @brief write to register VEML6075_REG_CONFIG_UV_IT to set integration time, for data process
 */
typedef enum {
  eVEML6075UV_IT_50,       /**< 50ms */
  eVEML6075UV_IT_100,      /**< 100ms */
  eVEML6075UV_IT_200,      /**< 200ms */
  eVEML6075UV_IT_400,      /**< 400ms */
  eVEML6075UV_IT_800       /**< 800ms */
} eVEML6075UV_IT_t;

/**
 * @struct sVEML6075Conf_t
 * @brief reg:UV_CONF, COMMAND CODE: 0x00_L (0x00 DATA BYTE LOW) OR 0x00_H (0x00 DATA BYTE HIGH)
 */
typedef struct {
  uint8_t   SD: 1;
  uint8_t   UV_AF: 1;
  uint8_t   UV_TRIG: 1;
  uint8_t   HD: 1;
  uint8_t   UV_IT: 3;
  uint8_t   reserved1: 1;
  uint8_t   reserved2;
} sVEML6075Conf_t;

class DFRobot_VEML6075
{

public:

  /**
   * @fn DFRobot_VEML6075
   * @brief constructor
   */
  DFRobot_VEML6075() {}

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

protected:

  /**
   * @fn writeReg
   * @brief write the sensor IIC data
   * @param reg register
   * @param pBuf write the store and buffer of the data
   * @param len data length to be written 
   * @return return the actually written length
   */
  virtual void writeReg(uint8_t reg, uint8_t *pBuf, uint16_t len) = 0;

  /**
   * @fn readReg
   * @brief get the sensor IIC data
   * @param reg register
   * @param pBuf write the store and buffer of the data
   * @param len data length to be readed 
   */
  virtual void readReg(uint8_t reg, uint8_t *pBuf, uint16_t len) = 0;

// variables
protected:
  eVEML6075ActiveForceMode_t    _eActiveForceMode;

  eVEML6075UV_IT_t    _eUV_IT;
};

// utils class -----------------------------------------------------------

class DFRobot_VEML6075_IIC : public DFRobot_VEML6075
{
public:
  /**
   * @fn DFRobot_VEML6075_IIC
   * @brief constructor
   * @param pWire  TwoWire
   * @param addr iic addr
   */
  DFRobot_VEML6075_IIC(TwoWire *pWire, uint8_t addr) : DFRobot_VEML6075() { _pWire = pWire; _addr = addr;}

  /**
   * @fn begin
   * @brief initialization function
   * @return bool,returns the initialization status
   * @retval true Initialization succeeded
   * @retval fasle Initialization  failed
   */
  bool begin(){ _pWire->begin();return DFRobot_VEML6075::begin();}
protected:


  /**
   * @fn writeReg
   * @brief write the sensor IIC data
   * @param reg register
   * @param pBuf write the store and buffer of the data
   * @param len data length to be written 
   * @return return the actually written length
   */
  void writeReg(uint8_t reg, uint8_t *pBuf, uint16_t len);

  /**
   * @fn readReg
   * @brief get the sensor IIC data
   * @param reg register
   * @param pBuf write the store and buffer of the data
   * @param len data length to be readed 
   */
  void readReg(uint8_t reg, uint8_t *pBuf, uint16_t len);

  uint8_t   _addr;
  TwoWire   *_pWire;
};

#endif
