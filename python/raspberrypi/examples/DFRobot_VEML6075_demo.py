# -*- coding: utf-8 -*-
'''!
  @file DFRobot_VEML6075_demo.py
  @brief normal test for VEML6075
  @n     UVA index, UVB index and UV index will print on terminal 
  @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license     The MIT License (MIT)
  @maintainer [Fary](feng.yang@dfrobot.com)
  @version  V1.0
  @date  2021-10-18
  @url https://github.com/DFRobot/DFRobot_VEML6075
'''

import time
import sys
sys.path.append("..")

from DFRobot_VEML6075 import DFRobot_VEML6075

if __name__ == '__main__':

  VEML6075 = DFRobot_VEML6075(1, 0x10)  # use i2c bus 1, module address is 0x10

  while VEML6075.begin() != True:
    print("VEML6075 begin faild")
    time.sleep(2)
  print("VEML6075 begin succeed")

  while True:
    Uva = VEML6075.get_uva()           # get UVA
    Uvb = VEML6075.get_uvb()           # get UVB
    Uvi = VEML6075.get_uvi(Uva, Uvb)   # get UVI
    print("")
    print("======== start print ========")
    print("UVA:     %.2f" %(Uva))
    print("UVB:     %.2f" %(Uvb))
    print("UVI:     %.2f" %(Uvi))
    print("mw/cm^2: %.2f" %(VEML6075.uvi2mwpcm2(Uvi)))
    print("======== end print =========")
    time.sleep(1)
