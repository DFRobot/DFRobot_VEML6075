# -*- coding: utf-8 -*-
'''!
  @file DFRobot_VEML6075.py
  @brief define DFRobot_VEML6075 class infrastructure, the implementation of basic methods
  @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license     The MIT License (MIT)
  @maintainer [Fary](feng.yang@dfrobot.com)
  @version  V1.0
  @date  2021-10-18
  @url https://github.com/DFRobot/DFRobot_VEML6075
'''
from raspberry_iic import RaspberryIIC

class DFRobot_VEML6075:
  '''!
    @brief DFRobot_VEML6075
  '''
  ID_DEFAULT = 0x26

  CONF = 0x00
  CONF_DEFAULT = 0x00
  UVA = 0x07
  UVB = 0x09
  UV_COMP1 = 0x0a
  UV_COMP2 = 0x0b
  ID = 0x0c

  UVA_RESPONSIVITY_100MS = 0.001111
  UVB_RESPONSIVITY_100MS = 0.00125

  uva_responsivity_list = [
    UVA_RESPONSIVITY_100MS / 0.5016286645,
    UVA_RESPONSIVITY_100MS,               
    UVA_RESPONSIVITY_100MS / 2.039087948, 
    UVA_RESPONSIVITY_100MS / 3.781758958, 
    UVA_RESPONSIVITY_100MS / 7.371335505  
  ]

  Uvb_responsivity_list = [
    UVB_RESPONSIVITY_100MS / 0.5016286645,
    UVB_RESPONSIVITY_100MS,               
    UVB_RESPONSIVITY_100MS / 2.039087948, 
    UVB_RESPONSIVITY_100MS / 3.781758958, 
    UVB_RESPONSIVITY_100MS / 7.371335505  
  ]

  UV_IT_50 = 0x00
  UV_IT_100 = 0x10
  UV_IT_200 = 0x20
  UV_IT_400 = 0x30
  UV_IT_800 = 0x40

  POWER_ON = 0x00
  POWER_OFF = 0x01

  ACTIVE_FORCE_ENABLE = 0x02
  ACTIVE_FORCE_DISABLE = 0x00

  DYNAMIC_NORMAL = 0x00
  DYNAMIC_HIGH = 0x08

  def __init__(self, i2cBus, addr):
    '''!
      @brief   _init_
      @param i2cBus Select _bus
      @param addr Module address
    '''
    self._bus = RaspberryIIC(i2cBus)
    self._addr = addr
    self._is_active_force_mode = False
    self._UV_IT = self.UV_IT_100 >> 4

  def begin(self):
    '''!
      @brief initialization function
      @return bool,returns the initialization status
      @retval True Initialization succeeded
      @retval False Initialization  failed
    '''
    _id = self._read_reg(self.ID, 2)
    if _id[0] == self.ID_DEFAULT:
      self._write_reg(self.CONF, [self.CONF_DEFAULT & 0xff, self.CONF_DEFAULT >> 8])
      self.set_active_force_mode(self.ACTIVE_FORCE_DISABLE)
      self.set_power(self.POWER_ON)
      self.set_integration_time(self.UV_IT_100)
      return True
    return False

  def _write_reg(self, reg, val):
    '''!
      @brief write the sensor IIC data
      @param reg register
      @param val write the store and buffer of the data
      @return return the actually written length
    '''
    return self._bus.write_reg(self._addr, reg, val)

  def _read_reg(self, reg, len):
    '''!
      @brief get the sensor IIC data
      @param reg register
      @param len data length to be readed 
      @return return the actually readed length
    '''
    return self._bus.read_reg(self._addr, reg, len)

  def _write_reg_bits(self, reg, field, val):
    '''!
      @brief Sets bits of a register
      @param reg register
      @param field field
      @param val Value to be set
    '''
    buf = self._read_reg(reg, 2)
    buf[0] &= field
    buf[0] |= val
    self._write_reg(reg, buf)

  def set_power(self, power):
    '''!
      @brief Set power
      @param power Power status to set
    '''
    self._write_reg_bits(self.CONF, 0xfe, power)

  def uvi2mwpcm2(self, Uvi):
    '''!
      @brief Data conversion
      @return mW/cm2
    '''
    return (Uvi * 0.0025)

  def get_power(self):
    '''!
      @brief get power status
      @return  Power status
      @retval    1    power on
      @retval    0   power off
    '''
    buf = self._read_reg(self.CONF, 2)
    return buf[0] & 0x01

  def set_active_force_mode(self, isEnable):
    '''!
      @brief set active force mode
      @param isEnable 
      @n       ACTIVE_FORCE_ENABLE    VEML6075 active force mode enable
      @n       ACTIVE_FORCE_DISABLE   VEML6075 active force mode disable
    '''
    self._write_reg_bits(self.CONF, 0xfd, isEnable)
    if isEnable == self.ACTIVE_FORCE_ENABLE:
      self._is_active_force_mode = True

  def get_active_force_mode(self):
    '''!
      @brief get active force mode
      @return  mode 
      @retval    ACTIVE_FORCE_ENABLE    VEML6075 active force mode enable
      @retval    ACTIVE_FORCE_DISABLE   VEML6075 active force mode disable
    '''
    buf = self._read_reg(self.CONF, 2)
    return buf[0] & 0x02

  def trig_one_measurement(self):
    '''!
      @brief  Trigger a measurement
    '''
    if self._is_active_force_mode:
      self._write_reg_bits(self.CONF, 0xfb, 0x04)

  def set_dynamic(self, dynamic):
    '''!
      @brief set Dynamic
      @param dynamic
      @n       DYNAMIC_NORMAL    normal dynamic setting
      @n       DYNAMIC_HIGH      high dynamic setting
    '''
    self._write_reg_bits(self.CONF, 0xf7, dynamic)

  def get_dynamic(self):
    '''!
      @brief get Dynamic
      @return  dynamic
      @n       DYNAMIC_NORMAL    normal dynamic setting
      @n       DYNAMIC_HIGH      high dynamic setting
    '''
    buf = self._read_reg(self.CONF, 2)
    return buf[0] & 0x08

  def set_integration_time(self, t):
    '''!
      @brief set integration time
      @param   t
      @n       UV_IT_50     50ms
      @n       UV_IT_100    100ms
      @n       UV_IT_200    200ms
      @n       UV_IT_400    400ms
      @n       UV_IT_800    800ms
    '''
    self._write_reg_bits(self.CONF, 0x8f, t)
    self._UV_IT = t >> 4

  def get_integration_time(self):
    '''!
      @brief get integration time
      @return  integration time
      @retval    UV_IT_50     50ms
      @retval    UV_IT_100    100ms
      @retval    UV_IT_200    200ms
      @retval    UV_IT_400    400ms
      @retval    UV_IT_800    800ms
    '''
    buf = self._read_reg(self.CONF, 2)
    return buf[0] & 0x8f

  def read_uva_raw(self):
    '''!
      @brief The reading sensor collects raw data in the UVA band
      @return  UVA Raw
    '''
    buf = self._read_reg(self.UVA, 2)
    return buf[0] | (buf[1] << 8)

  def read_uvb_raw(self):
    '''!
      @brief The reading sensor collects raw data in the UVB band
      @return  UVB Raw
    '''
    buf = self._read_reg(self.UVB, 2)
    return buf[0] | (buf[1] << 8)

  def read_UVcomp1_raw(self):
    '''!
      @brief The reading sensor collects raw data in the UvComp1
      @return  UvComp1 Raw
    '''
    buf = self._read_reg(self.UV_COMP1, 2)
    return buf[0] | (buf[1] << 8)
  
  def read_UVcomp2_raw(self):
    '''!
      @brief The reading sensor collects raw data in the UvComp2
      @return  UvComp2 Raw
    '''
    buf = self._read_reg(self.UV_COMP2, 2)
    return buf[0] | (buf[1] << 8)

  def get_uva(self):
    '''!
      @brief The UVA band data of ultraviolet ray are calculated according to the data collected
      @return  UVA data
    '''
    return (self.read_uva_raw() - ((2.22 * 1.0 * self.read_UVcomp1_raw()) / 1.0) - ((1.33 * 1.0 * self.read_UVcomp2_raw()) / 1.0))

  def get_uvb(self):
    '''!
      @brief The UVB band data of ultraviolet ray are calculated according to the data collected
      @return  UVB data
    '''
    return (self.read_uvb_raw() - ((2.95 * 1.0 * self.read_UVcomp1_raw()) / 1.0) - ((1.74 * 1.0 * self.read_UVcomp2_raw()) / 1.0))

  def get_uvi(self, Uva, Uvb):
    '''!
      @brief The UVI band data of ultraviolet ray are calculated according to the data collected
      @return  UVI data
    '''
    Uva = ((Uva * (1.0 / 1.0)) * self.uva_responsivity_list[self._UV_IT])
    Uvb = ((Uvb * (1.0 / 1.0)) * self.uva_responsivity_list[self._UV_IT])
    return (Uva + Uvb) / 2
