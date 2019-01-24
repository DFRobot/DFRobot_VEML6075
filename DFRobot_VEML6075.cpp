#include <DFRobot_VEML6075.h>

#define UVA_A_COEF    2.22f
#define UVA_B_COEF    1.33f
#define UVA_C_COEF    2.95f
#define UVA_D_COEF    1.74f

#define UV_ALPHA      1.0
#define UV_BETA       1.0
#define UV_GAMMA      1.0
#define UV_DELTA      1.0

#define UVA_RESPONSIVITY_100MS    0.001111
#define UVB_RESPONSIVITY_100MS    0.00125

const float UvaResponsivityList[5] = {
  UVA_RESPONSIVITY_100MS / 0.5016286645, // 50ms
  UVA_RESPONSIVITY_100MS,                // 100ms
  UVA_RESPONSIVITY_100MS / 2.039087948,  // 200ms
  UVA_RESPONSIVITY_100MS / 3.781758958,  // 400ms
  UVA_RESPONSIVITY_100MS / 7.371335505   // 800ms
};

const float UvbResponsivityList[5] = {
  UVB_RESPONSIVITY_100MS / 0.5016286645, // 50ms
  UVB_RESPONSIVITY_100MS,                // 100ms
  UVB_RESPONSIVITY_100MS / 2.039087948,  // 200ms
  UVB_RESPONSIVITY_100MS / 3.781758958,  // 400ms
  UVB_RESPONSIVITY_100MS / 7.371335505   // 800ms
};

boolean DFRobot_VEML6075::begin()
{
  uint16_t   tmp = 0;
  readReg(VEML6075_ID, (uint8_t*) &tmp, sizeof(tmp));
  if(tmp == VEML6075_ID_DEFAULT) {
    tmp = VEML6075_CONF_DEFAULT;
    writeReg(VEML6075_CONF, (uint8_t*) &tmp, sizeof(tmp));
    setPower(eVEML6075PowerOn);
    setActiveForceMode(eVEML6075ActiveForceModeDisable);
    setIntegrationTime(eVEML6075UV_IT_100);
    return true;
  }
  return false;
}

#define writeRegBits(reg, buf, bits, value) \
  readReg((reg), (uint8_t*) &buf, sizeof(buf)); \
  (bits) = (value); \
  writeReg((reg), (uint8_t*) &buf, sizeof(buf))

// main class config functions --------------------------------------------------------------------------

void DFRobot_VEML6075::setPower(eVEML6075Power_t ePower)
{
  sVEML6075Conf_t   sConf;
  writeRegBits(VEML6075_CONF, sConf, sConf.SD, ePower);
}

void DFRobot_VEML6075::setActiveForceMode(eVEML6075ActiveForceMode_t eMode)
{
  sVEML6075Conf_t   sConf;
  writeRegBits(VEML6075_CONF, sConf, sConf.UV_AF, eMode);
  _eActiveForceMode = eMode;
}

void DFRobot_VEML6075::setDynamic(eVEML6075Dynamic_t eDynamic)
{
  sVEML6075Conf_t   sConf;
  writeRegBits(VEML6075_CONF, sConf, sConf.HD, eDynamic);
}

void DFRobot_VEML6075::setIntegrationTime(eVEML6075UV_IT_t eUV_IT)
{
  sVEML6075Conf_t   sConf;
  writeRegBits(VEML6075_CONF, sConf, sConf.UV_IT, eUV_IT);
  _eUV_IT = eUV_IT;
}

void DFRobot_VEML6075::trigOneMeasurement()
{
  if(_eActiveForceMode == eVEML6075ActiveForceModeEnable) {
    sVEML6075Conf_t   sConf;
    writeRegBits(VEML6075_CONF, sConf, sConf.UV_TRIG, VEML6075_TRIG_ONE_MEASUREMENT);
  }
}

eVEML6075ActiveForceMode_t DFRobot_VEML6075::getActiveForceMode()
{
  sVEML6075Conf_t   sConf;
  readReg(VEML6075_CONF, (uint8_t*) &sConf, sizeof(sConf));
  return (eVEML6075ActiveForceMode_t) sConf.UV_AF;
}

eVEML6075Dynamic_t DFRobot_VEML6075::getDynamic()
{
  sVEML6075Conf_t   sConf;
  readReg(VEML6075_CONF, (uint8_t*) &sConf, sizeof(sConf));
  return (eVEML6075Dynamic_t) sConf.HD;
}

eVEML6075Power_t DFRobot_VEML6075::getPower()
{
  sVEML6075Conf_t   sConf;
  readReg(VEML6075_CONF, (uint8_t*) &sConf, sizeof(sConf));
  return (eVEML6075Power_t) sConf.SD;
}

eVEML6075UV_IT_t DFRobot_VEML6075::getIntegrationTime()
{
  sVEML6075Conf_t   sConf;
  readReg(VEML6075_CONF, (uint8_t*) &sConf, sizeof(sConf));
  return (eVEML6075UV_IT_t) sConf.UV_IT;
}

// main class process functions ------------------------------------------------------------------------------------

uint16_t DFRobot_VEML6075::readUvComp1Raw()
{
  uint16_t    tmp;
  readReg(VEML6075_UV_COMP1, (uint8_t*) &tmp, sizeof(tmp));
  return tmp;
}

uint16_t DFRobot_VEML6075::readUvComp2Raw()
{
  uint16_t    tmp;
  readReg(VEML6075_UV_COMP2, (uint8_t*) &tmp, sizeof(tmp));
  return tmp;
}

uint16_t DFRobot_VEML6075::readUvaRaw()
{
  uint16_t    tmp;
  readReg(VEML6075_UVA, (uint8_t*) &tmp, sizeof(tmp));
  return tmp;
}

uint16_t DFRobot_VEML6075::readUvbRaw()
{
  uint16_t    tmp;
  readReg(VEML6075_UVB, (uint8_t*) &tmp, sizeof(tmp));
  return tmp;
}

float DFRobot_VEML6075::getUva()
{
  return ((float) readUvaRaw() - ((UVA_A_COEF * UV_ALPHA * (float) readUvComp1Raw()) / UV_GAMMA)
                               - ((UVA_B_COEF * UV_ALPHA * (float) readUvComp2Raw()) / UV_DELTA));
}

float DFRobot_VEML6075::getUvb()
{
  return ((float) readUvbRaw() - ((UVA_C_COEF * UV_BETA * (float) readUvComp1Raw()) / UV_GAMMA)
                               - ((UVA_D_COEF * UV_BETA * (float) readUvComp2Raw()) / UV_DELTA));
}

float DFRobot_VEML6075::getUvi(float Uva, float Uvb)
{
  Uva = (Uva * (1.0f / UV_ALPHA) * UvaResponsivityList[(uint8_t) _eUV_IT]);
  Uvb = (Uvb * (1.0f / UV_BETA) * UvbResponsivityList[(uint8_t) _eUV_IT]);
  return (Uva + Uvb) / 2.0f;
}

// for DFRobot_VEML6075_IIC ---------------------------------------------------------------------------------------------

void DFRobot_VEML6075_IIC::writeReg(uint8_t reg, uint8_t *pBuf, uint16_t len)
{
  _pWire->begin();
  _pWire->beginTransmission(_addr);
  _pWire->write(reg);
  for(uint16_t i = 0; i < len; i ++)
    _pWire->write(pBuf[i]);
  _pWire->endTransmission();
}

void DFRobot_VEML6075_IIC::readReg(uint8_t reg, uint8_t *pBuf, uint16_t len)
{
  _pWire->begin();
  _pWire->beginTransmission(_addr);
  _pWire->write(reg);
  if(_pWire->endTransmission(false) != 0)
    return;
  _pWire->requestFrom(_addr, (uint8_t) len);
  for(uint16_t i = 0; i < len; i ++)
    pBuf[i] = _pWire->read();
  _pWire->endTransmission();
}
