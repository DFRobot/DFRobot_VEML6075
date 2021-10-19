# -*- coding: utf-8 -*-
'''!
  @file raspberry_iic.py
  @brief define RaspberryIIC class infrastructure, the implementation of basic methods
  @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license     The MIT License (MIT)
  @author [xiaowo] (jiehan.guo@dfrobot.com)
  @maintainer [Fary](feng.yang@dfrobot.com)
  @version  V1.0
  @date  2021-10-18
  @url https://github.com/DFRobot/DFRobot_VEML6075
'''
import smbus

class RaspberryIIC:

  def __init__(self, i2cBus):
    self.bus = smbus.SMBus(i2cBus)

  def write_reg(self, addr, reg, buf):
    '''!
      @brief write the sensor IIC data
      @param addr iic addr
      @param reg register
      @param buf write the store and buffer of the data
      @return return the actually written length
    '''
    return self.bus.write_i2c_block_data(addr, reg, buf)

  def read_reg(self, addr, reg, len):
    '''!
      @brief get the sensor IIC data
      @param addr iic addr
      @param reg register
      @param len data length to be readed 
      @return return the actually readed length
    '''
    return self.bus.read_i2c_block_data(addr, reg, len)
