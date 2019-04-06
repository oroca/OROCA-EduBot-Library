/*
 * EduBot.cpp
 *
 *  Created on: Jul 6, 2018
 *      Author: Baram
 */



#include "EduBot.h"
#include "image/EduBoy.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"






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
  p_menu = &menu; 
  is_init = false;
}

EduBot::~EduBot()
{ 
}

bool EduBot::begin(int baud)
{
  bool ret = false;
  bool ret_log = false;

  if (is_init == true)
  {
    return true;
  }

  driverInit();

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
  lcd.setCursor(28, 64 - 8);
  lcd.print("OROCA EduBot");
  lcd.drawBitmap((128-48)/2, (64-48)/2, &edubot_logo[1*48*48/8], 48, 48, 1);
  lcd.display();
  lcd.clearDisplay();
  
  lcd.setCursor(0, 0);
  lcd.println(EDUBOT_VER_STR);

  ret_log = true;
  ret_log &= printInitLog("Audio Init", audio.begin());
  ret_log &= printInitLog("IR Remote Init", ir_remote.begin());
  ret_log &= printInitLog("IMU Init", imu.begin());
  ret_log &= printInitLog("Motor Init", motor.begin());
  ret_log &= printInitLog("LED Init", led.begin());

  floor_sensor.begin();

  tofBegin();

  if (ret_log == false)
  {
    lcd.display();
    lcd.setCursor(0, 0);
    delay(1000);
  }
  else
  {
    lcd.clearDisplay();
    lcd.setCursor(0, 0);    
  }

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
    

  p_menu->run_count = 0;
  p_menu->count = 0;
  p_menu->cursor = 0;
  p_menu->first_rows = 0;
  p_menu->view_rows = 4;
  p_menu->pre_time = millis();
  p_menu->press_count = 0;
  p_menu->press_state = buttonGetPressed(); 

  // disable brownout detector
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  is_init = true;
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

  if (cur_time-pre_time[1] >= 50)
  {
    pre_time[1] = cur_time;
    motor.update();
  }

  adcInfoUpdate();

  return true;
}

bool EduBot::tofBegin(void)
{
  bool ret;

  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);

  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  delay(10);

  digitalWrite(D7, HIGH);
  delay(10);

  ret = printInitLog("TOF L Init", tof_L.begin());
  if (ret == true)  
  {
    tof_L.setAddress(0x10);
  }
  else
  {
    digitalWrite(D7, LOW);
  }


  digitalWrite(D6, HIGH);
  delay(10);
  
  ret &= printInitLog("TOF R Init", tof_R.begin());
  if (ret == false)  
  {
    digitalWrite(D6, LOW);
  }

  return ret;
}

void EduBot::tofEnd(void)
{
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);  

  tof_L.end();
  tof_R.end();
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

void EduBot::menuAdd(const char *menu_str, void (*setup_func)(void), void (*loop_func)(void))
{
  uint8_t index;

  index = p_menu->count++;

  strcpy(p_menu->node[index].str, menu_str);
  p_menu->node[index].setup_func = setup_func;
  p_menu->node[index].loop_func = loop_func;
}

void EduBot::menuUpdate(void)
{
  if (p_menu->run_count > 0)
  {
    if (p_menu->run_count == 1)
    {
      p_menu->run_count++;
      if (p_menu->node[p_menu->cursor].setup_func != NULL)
      {
        p_menu->node[p_menu->cursor].setup_func();
      }
    }
    else
    {
      if (p_menu->node[p_menu->cursor].loop_func != NULL)
      {
        p_menu->node[p_menu->cursor].loop_func();        
      }
      else
      {
        p_menu->run_count = 0;
        p_menu->pre_time = millis();
        p_menu->press_count = 0;
        p_menu->press_state = buttonGetPressed();         
      }
    }
  }
  else
  {
    menuDraw(p_menu);
  }  
}

bool EduBot::menuDraw(menu_t *p_menu)
{
  uint8_t view_rows;
  uint8_t index;
  uint8_t press_count = 0;
  bool press_done = false;


  if (p_menu->count == 0)
  {
    return false;
  }  

  // 버튼 처리 
  if (p_menu->press_state != buttonGetPressed())
  {
    if (p_menu->press_state == true)
    {
      p_menu->press_count++;
      p_menu->pre_time = millis();
    }
    else
    {
      p_menu->pre_time_pressed = millis();
    }    
    p_menu->press_state = buttonGetPressed();
  }
  if (millis()-p_menu->pre_time > 300)
  {
    press_count = p_menu->press_count;
    press_done = true;    
    p_menu->press_count = 0;
  }
  if (buttonGetPressed())
  {
    if (millis()-p_menu->pre_time_pressed >= 1000)
    {
      p_menu->press_count = 0;

      for (int i=0; i< lcd.width(); i+=2)
      {
        lcd.fillRect(i, 0, 2, lcd.height(), 0);
        lcd.display();
      }
      p_menu->run_count = 1;      
      return true;
    }
  }

  // 커서 처리 
  if (press_done)
  {
    if (press_count == 1)
    {
      p_menu->cursor++;
      p_menu->cursor %= p_menu->count;            
    }
    if (press_count == 2)
    {
      p_menu->cursor--;
      p_menu->cursor = constrain(p_menu->cursor, 0, p_menu->count - 1);
    }
  }

  p_menu->first_rows = (p_menu->cursor/p_menu->view_rows) * p_menu->view_rows;


  view_rows = p_menu->count - p_menu->first_rows;
  view_rows = constrain(view_rows, 0, p_menu->view_rows);

  
  lcd.clearDisplay();

  for (int i=0; i<view_rows; i++)
  {
    index = p_menu->first_rows + i;
    lcd.printf(2, 16*i + 1, "%02d %s", index+1, p_menu->node[index].str);

    if (index == p_menu->cursor)
    {
      lcd.drawRoundRect(0, 16*i, lcd.width(), 16, 2, 1);
    }
  }
  lcd.display();

  return false;
}


EduBot edubot;