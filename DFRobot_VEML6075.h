#ifndef DFROBOT_VEML6075_H
#define DFROBOT_VEML6075_H

#include <Arduino.h>
#include <Wire.h>

// globals -----------------------------------------------------------------

#define VEML6075_ID_DEFAULT   0x26
#define VEML6075_ADDR         0x10

#define UVI_LOW         2.0f
#define UVI_MODERATE    5.0f
#define UVI_HIGH        7.0f
#define UVI_VERY_HIGH   10.0f
#define UVI_EXTREME     12.0f

#define Uvi2mwpcm2(UVI) (UVI * 2500.0f)

// registers ---------------------------------------------------------------

#define VEML6075_CONF       0x00
#define VEML6075_CONF_DEFAULT   0x00
#define VEML6075_UVA        0x07
#define VEML6075_UVB        0x09
#define VEML6075_UV_COMP1   0x0a
#define VEML6075_UV_COMP2   0x0b
#define VEML6075_ID         0x0c

// utils ------------------------------------------------------------------

typedef enum {
  eVEML6075PowerOn,
  eVEML6075PowerOff
} eVEML6075Power_t;

typedef enum {
  eVEML6075ActiveForceModeDisable,
  eVEML6075ActiveForceModeEnable,
} eVEML6075ActiveForceMode_t;

// write to register VEML6075_REG_CONFIG_UV_TRIG to start one measurement if VEML6075_REG_CONFIG_UV_AF = 1
#define VEML6075_TRIG_ONE_MEASUREMENT   1

// write to register VEML6075_REG_CONFIG_HD to set dynamic
typedef enum {
  eVEML6075DynamicNormal,
  eVEML6075DynamicHigh
} eVEML6075Dynamic_t;

// write to register VEML6075_REG_CONFIG_UV_IT to set integration time, for data process
typedef enum {
  eVEML6075UV_IT_50,
  eVEML6075UV_IT_100,
  eVEML6075UV_IT_200,
  eVEML6075UV_IT_400,
  eVEML6075UV_IT_800
} eVEML6075UV_IT_t;

typedef struct {
  uint8_t   SD: 1;
  uint8_t   UV_AF: 1;
  uint8_t   UV_TRIG: 1;
  uint8_t   HD: 1;
  uint8_t   UV_IT: 3;
  uint8_t   reserved1: 1;
  uint8_t   reserved2;
} sVEML6075Conf_t;

// main class -------------------------------------------------------------

class DFRobot_VEML6075
{
// functions
public:
  DFRobot_VEML6075() {}

  boolean   begin();

  // config functions
  void    setPower(eVEML6075Power_t ePower);
  void    setActiveForceMode(eVEML6075ActiveForceMode_t eMode);
  void    trigOneMeasurement();
  void    setDynamic(eVEML6075Dynamic_t eDynamic);
  void    setIntegrationTime(eVEML6075UV_IT_t eUV_IT);

  eVEML6075Power_t    getPower();
  eVEML6075ActiveForceMode_t    getActiveForceMode();
  eVEML6075Dynamic_t  getDynamic();
  eVEML6075UV_IT_t    getIntegrationTime();

  // data process functions
  uint16_t  readUvaRaw();
  uint16_t  readUvbRaw();
  uint16_t  readUvComp1Raw();
  uint16_t  readUvComp2Raw();
  float     getUva();
  float     getUvb();
  float     getUvi(float Uva, float Uvb);

protected:

  virtual void    writeReg(uint8_t reg, uint8_t *pBuf, uint16_t len) = 0;
  virtual void    readReg(uint8_t reg, uint8_t *pBuf, uint16_t len) = 0;

// variables
protected:
  eVEML6075ActiveForceMode_t    _eActiveForceMode;

  eVEML6075UV_IT_t    _eUV_IT;
};

// utils class -----------------------------------------------------------

class DFRobot_VEML6075_IIC : public DFRobot_VEML6075
{
public:
  DFRobot_VEML6075_IIC(TwoWire *pWire, uint8_t addr) : DFRobot_VEML6075() { _pWire = pWire; _addr = addr; }

protected:
  void    writeReg(uint8_t reg, uint8_t *pBuf, uint16_t len);
  void    readReg(uint8_t reg, uint8_t *pBuf, uint16_t len);

  uint8_t   _addr;
  TwoWire   *_pWire;
};

#endif
