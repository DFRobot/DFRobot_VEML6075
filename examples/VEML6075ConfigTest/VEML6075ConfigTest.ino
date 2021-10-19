/*!
 * @file VEML6075ConfigTest.ino
 * @brief MCU receive cmd from serial monitor to test VEML6075 config
 * @n     input '1' to set power
 * @n     input '2' to test dynamic
 * @n     input '3' to set active force mode
 * @n     input '4' to test integration time
 * @n     input '5' to trigger one measurement in active force mode
 * @n     input '6' to start auto measurement
 * @n     input '7' to set config to default
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @maintainer [Fary](feng.yang@dfrobot.com)
 * @version  V1.0
 * @date  2021-10-18
 * @url https://github.com/DFRobot/DFRobot_VEML6075
 */
#include <Wire.h>
#include <DFRobot_VEML6075.h>

#define VEML6075_ADDR   0x10

DFRobot_VEML6075_IIC    VEML6075(&Wire, VEML6075_ADDR);  // create object

void setup()
{
  Serial.begin(115200);
  while(!Serial);

  Serial.println();
  while(VEML6075.begin() != true) {
    Serial.println("VEML6075 begin faild");
    delay(2000);
  }
  Serial.println("VEML6075 begin successed");
  Serial.println();
  Serial.println("reference test cmds in function loop to test cmd");
}

uint8_t processOneCmd()  // process one cmd from serial
{
  uint8_t   cmd = 0;
  if(Serial.available()) {
    cmd = Serial.read();
    delay(2);
    while(Serial.available()) {
      Serial.read();
      delay(2);
    }
    Serial.println();
  }
  return cmd;
}

void processData()  // process and print data
{
  float Uva = VEML6075.getUva();                    // get UVA
  float Uvb = VEML6075.getUvb();                    // get UVB
  float Uvi = VEML6075.getUvi(Uva, Uvb);            // get UV index

  Serial.println();
  Serial.println("======== start print ========");
  Serial.print("UVA:     ");
  Serial.println(Uva, 2);
  Serial.print("UVB:     ");
  Serial.println(Uvb, 2);
  Serial.print("UVIndex: ");
  Serial.println(Uvi, 2);
  Serial.println("======== end print ========");
}

void loop()
{
  uint8_t   cmd;

  switch(processOneCmd()) {

  // set power
  case '1': {
    if(VEML6075.getPower() == eVEML6075PowerOn) {
      Serial.println("test power, change to off");
      VEML6075.setPower(eVEML6075PowerOff);
    } else {
      Serial.println("test power, change to on");
      VEML6075.setPower(eVEML6075PowerOn);
    }
  } break;

  // set dynamic
  case '2': {
    if(VEML6075.getDynamic() == eVEML6075DynamicNormal) {
      Serial.println("test dynamic, change to high");
      VEML6075.setDynamic(eVEML6075DynamicHigh);
    } else {
      Serial.println("test dynamic, change to normal");
      VEML6075.setDynamic(eVEML6075DynamicNormal);
    }
  } break;

  // set active force mode
  case '3': {
    if(VEML6075.getActiveForceMode() == eVEML6075ActiveForceModeDisable) {
      Serial.println("test set active force mode, change to enable, input '5' to start one measurement");
      VEML6075.setActiveForceMode(eVEML6075ActiveForceModeEnable);
    } else {
      Serial.println("test set active force mode, change to disable");
      VEML6075.setActiveForceMode(eVEML6075ActiveForceModeDisable);
    }
  } break;

  // set integration time
  case '4': {
    Serial.println("input '1'/'2'/'3'/'4'/'5' set integration time to 50ms/100ms/200ms/400ms/800ms");
    cmd = 0;
    while(cmd == 0)  // wait for one cmd
      cmd = processOneCmd();
    switch(cmd) {
    case '1': VEML6075.setIntegrationTime(eVEML6075UV_IT_50); break;
    case '2': VEML6075.setIntegrationTime(eVEML6075UV_IT_100); break;
    case '3': VEML6075.setIntegrationTime(eVEML6075UV_IT_200); break;
    case '4': VEML6075.setIntegrationTime(eVEML6075UV_IT_400); break;
    case '5': VEML6075.setIntegrationTime(eVEML6075UV_IT_800); break;
    default: Serial.println("unknow integration time"); break;          // unknow cmd
    }
    Serial.println("set integration time done");
  } break;

  // test trigger one measurement
  case '5': {
    Serial.println("trigger one measurement");
    if(VEML6075.getActiveForceMode() == eVEML6075ActiveForceModeEnable) {
      VEML6075.trigOneMeasurement();
      delay(128);  // delay until measurement stable
      processData();
    }
    else
      Serial.println("faild, not in active force mode");
  } break;

  // test auto measurement, any input to stop
  case '6': {
    Serial.println("test auto measurement, any input to stop");
    Serial.println();
    unsigned long lastMillis = 0;
    while(processOneCmd() == 0) {
      if((millis() - lastMillis) > 1000) {
        lastMillis = millis();
        processData();
      }
    }
    Serial.println("stop auto measurement");
  } break;

  // set config to default
  case '7': {
    Serial.println("set config to default");
    VEML6075.begin();
  } break;
  }
}
