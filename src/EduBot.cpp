/*
 * EduBot.cpp
 *
 *  Created on: Jul 6, 2018
 *      Author: Baram
 */



#include "EduBot.h"




void taskUpdate( void *pvParameters );

void taskUpdate(void *pvParameters) 
{
  EduBot *p_class =  (EduBot *)pvParameters;
  
  for (;;)
  {
    p_class->update();
    vTaskDelay(2);
  }
}

EduBot::EduBot(void)
{
}

EduBot::~EduBot()
{ 
}

bool EduBot::begin(int baud)
{
  bool ret = true;

  Serial.begin(baud);
  Serial.println();
  Serial.println();
  Serial.println("[ OROCA EduBot ]");

  pinMode(27, OUTPUT);
  pinMode(12, OUTPUT);
  
  digitalWrite(27, HIGH);
  digitalWrite(12, HIGH);

  // for Internal LED
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  // for Unser Button
  pinMode(0, INPUT_PULLUP);

  adcInfoInit();
  adcInfoEnable(VBAT);
  
  ret = lcd.begin();

  lcd.println(EDUBOT_VER_STR);

  ret = printInitLog("Audio Init", audio.begin());
  ret = printInitLog("IR Remote Init", ir_remote.begin());
  ret = printInitLog("IMU Init", imu.begin());
  ret = printInitLog("Motor Init", motor.begin());
  ret = printInitLog("LED Init", led.begin());

  floor_sensor.begin();
  
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);


  digitalWrite(D6, LOW);
  digitalWrite(D7, HIGH);
  delay(10);

  ret = printInitLog("TOF L Init", tof_L.begin());
  if (ret == true)  
  {
    tof_L.setAddress(0x10);
  }
  

  digitalWrite(D6, HIGH);
  digitalWrite(D7, HIGH);
  delay(10);
  
  ret = printInitLog("TOF R Init", tof_R.begin());
  if (ret == true)
  {
    //tof_L.setAddress(0x02);
  }

  lcd.display();
  delay(1000);

  for (int i=0; i<8; i++)
  {
    pre_time[i] = millis();
  }

  xTaskCreatePinnedToCore(
    taskUpdate
    ,  "update"
    ,  4*1024   // Stack size
    ,  (void *)this
    ,  1        // Priority
    ,  NULL 
    ,  1);
    

  //ble.begin("OROCA EduBot");  

  return true;
}

bool EduBot::printInitLog(const char *str_msg, bool ret)
{
  if (ret == true)
  {
    Serial.print("[OK] ");
    if (lcd.isInit())
    {
      lcd.print("[OK] ");
    }
  }
  else
  {
    Serial.print("[NG] ");
    if (lcd.isInit())
    {
      lcd.print("[NG] ");
    }
  }
  
  Serial.println(str_msg);
  if (lcd.isInit())
  {
    lcd.println(str_msg);
  }

  return ret;
}

bool EduBot::update(void)
{
  uint32_t cur_time;

  cur_time = millis();

  if (cur_time-pre_time[0] >= 10)
  {
    pre_time[0] = cur_time;

    if (imu.isInit())
    {
      imu.update();
    }
    tof_L.update();
    tof_R.update();    
  }

  adcInfoUpdate();

  return true;
}

void EduBot::ledOn(void)
{
  digitalWrite(13, LOW);
}

void EduBot::ledOff(void)
{
  digitalWrite(13, HIGH);
}

void EduBot::ledToggle(void)
{
  digitalWrite(13, !digitalRead(13));
}

bool EduBot::buttonGetPressed(void)
{
  if (digitalRead(0) == 0)
  {
    return true;
  }
  else
  {
    return false;
  }  
}

uint8_t EduBot::batteryGetVoltage(void)
{
  uint16_t value;

  value = adcInfoReadRaw(VBAT);

  value = 72 * value / 4095;  // 3.6V * x / 4095

  return value;
}