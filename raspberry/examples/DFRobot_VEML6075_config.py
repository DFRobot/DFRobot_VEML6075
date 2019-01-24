# -*- coding: utf-8 -*-

'''
 *  file DFRobot_VEML6075_demo.py
 *  config test for VEML6075
 *  UVA index, UVB index and UV index will print on terminal 
 *
 *  Copyright    [DFRobot](http://www.dfrobot.com), 2018
 *  Copyright    GNU Lesser General Public License
 *  version  V1.0
 *  date  2018-12-18
'''

import time
import sys
sys.path.append("..")

from DFRobot_VEML6075 import DFRobot_VEML6075

isActiveForceModeEnable = True

if __name__ == '__main__':

  VEML6075 = DFRobot_VEML6075(1, 0x10)  # use i2c bus 1, module address is 0x10

  while VEML6075.begin() != True:
    print("VEML6075 begin faild")
    time.sleep(2)
  print("VEML6075 begin succeed")
  # set active force mode
  if isActiveForceModeEnable:
    VEML6075.setActiveForceMode(VEML6075.ACTIVE_FORCE_ENABLE)
  else:
    VEML6075.setActiveForceMode(VEML6075.ACTIVE_FORCE_DISABLE)

  # set dynamic normal
  VEML6075.setDynamic(VEML6075.DYNAMIC_NORMAL)
  # set integration time to 100ms
  VEML6075.setIntegrationTime(VEML6075.UV_IT_100)
  # set pwoer on
  VEML6075.setPower(VEML6075.POWER_ON)

  while True:
    if isActiveForceModeEnable:
      VEML6075.trigOneMeasurement()
      time.sleep(0.128)
    Uva = VEML6075.getUva()  # get UVA
    Uvb = VEML6075.getUvb()  # get UVB
    Uvi = VEML6075.getUvi(Uva, Uvb)  # get UVI
    print("")
    print("======== start print ========")
    print("UVA:     %.2f" %(Uva))
    print("UVB:     %.2f" %(Uvb))
    print("UVA:     %.2f" %(Uvi))
    print("mw/cm^2: %.2f" %(VEML6075.Uvi2mwpcm2(Uvi)))
    print("======== end print =========")
    time.sleep(1)
