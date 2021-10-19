/*!
 * @file VEML6075ConfigTest.ino
 * @brief  simple test for VEML6075
 * @n       Print UVA index, UVB index and UV index on the serial monitor
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

DFRobot_VEML6075_IIC VEML6075(&Wire, VEML6075_ADDR);  // create object

void setup()
{
  Serial.begin(115200);
  delay(2000);
  while(!Serial);

  Serial.println();
  while(VEML6075.begin() != true) {
    Serial.println("VEML6075 begin faild");
    delay(2000);
  }
  Serial.println("VEML6075 begin successed");
}

void loop()
{
  uint16_t    UvaRaw = VEML6075.readUvaRaw();         // read UVA raw
  uint16_t    UvbRaw = VEML6075.readUvbRaw();         // read UVB raw
  uint16_t    comp1Raw = VEML6075.readUvComp1Raw();   // read COMP1 raw
  uint16_t    comp2Raw = VEML6075.readUvComp2Raw();   // read COMP2 raw

  float       Uva = VEML6075.getUva();                    // get UVA
  float       Uvb = VEML6075.getUvb();                    // get UVB
  float       Uvi = VEML6075.getUvi(Uva, Uvb);            // get UV index

  Serial.println();
  Serial.println("======== start print ========");
  Serial.print("UVA raw:    ");
  Serial.println(UvaRaw);
  Serial.print("UVB raw:    ");
  Serial.println(UvbRaw);
  Serial.print("COMP1 raw:  ");
  Serial.println(comp1Raw);
  Serial.print("COMP2 raw:  ");
  Serial.println(comp2Raw);
  Serial.print("UVA:        ");
  Serial.println(Uva, 2);
  Serial.print("UVB:        ");
  Serial.println(Uvb, 2);
  Serial.print("UVIndex:    ");
  Serial.print(Uvi, 2);
  if(Uvi < UVI_LOW)
    Serial.println("  UVI low");
  else if(Uvi < UVI_MODERATE)
    Serial.println("  UVI moderate");
  else if(Uvi < UVI_HIGH)
    Serial.println("  UVI high");
  else if(Uvi < UVI_VERY_HIGH)
    Serial.println("  UVI very high");
  else
    Serial.println("  UVI extreme");
  Serial.print("mw/cm^2:    ");
  Serial.println(Uvi2mwpcm2(Uvi), 2);
  Serial.println("======== end print ========");
  delay(1000);
}
