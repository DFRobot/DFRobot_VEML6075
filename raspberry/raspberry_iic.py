# -*- coding: utf-8 -*-

import smbus

class RaspberryIIC:

  def __init__(self, i2cBus):
    self.bus = smbus.SMBus(i2cBus)

  def writeReg(self, addr, reg, buf):
    return self.bus.write_i2c_block_data(addr, reg, buf)

  def readReg(self, addr, reg, len):
    return self.bus.read_i2c_block_data(addr, reg, len)
