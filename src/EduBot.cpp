/*
 * EduBot.cpp
 *
 *  Created on: Jul 6, 2018
 *      Author: Baram
 */



#include "EduBot.h"





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

  ret = printInitLog("Audio Init", audio.begin());
  ret = printInitLog("IR Remote Init", ir_remote.begin());
  ret = printInitLog("IMU Init", imu.begin());
  ret = printInitLog("Audio Init", audio.begin());
  ret = printInitLog("Motor Init", motor.begin());
  ret = printInitLog("LCD Init", lcd.begin());

  return true;
}

bool EduBot::printInitLog(const char *str_msg, bool ret)
{
  if (ret == true)
  {
    Serial.print("[OK] ");
  }
  else
  {
    Serial.print("[NG] ");
  }
  
  Serial.println(str_msg);

  return ret;
}

bool EduBot::update(void)
{
  imu.update();

  return true;
}
