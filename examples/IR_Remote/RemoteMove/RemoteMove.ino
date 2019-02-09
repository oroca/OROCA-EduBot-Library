#include <EduBot.h>


EduBot edubot;


uint32_t key_left   = 0xF807FF00;
uint32_t key_right  = 0xF609FF00;
uint32_t key_up     = 0xBF40FF00;
uint32_t key_down   = 0xE619FF00;

uint32_t key_led_left  = 0xBB44FF00;
uint32_t key_led_right = 0xBC43FF00;

void setup() {
  // put your setup code here, to run once:
  
  edubot.begin(115200);          
  edubot.tofEnd();                         
}

void loop() {
  // put your main code here, to run repeatedly
  static uint32_t pre_time;
  int32_t speed = 100;


  if (edubot.ir_remote.available() > 0)
  {
    uint32_t key_code;

    key_code = edubot.ir_remote.read();

    Serial.print("Key : 0x");
    Serial.print(key_code, HEX);
    Serial.print(" ");
    Serial.println(edubot.ir_remote.getTime());

    edubot.lcd.printf(0, 0, "KeyCode");
    edubot.lcd.printf(0, 16,"0x%X", key_code);    

    if (key_code == key_up)
    {
      edubot.motor.setSpeed(speed, speed);
      edubot.lcd.printf(0, 32,"전진   ");
    }
    if (key_code == key_down)
    {
      edubot.motor.setSpeed(-speed, -speed);
      edubot.lcd.printf(0, 32,"후진   ");
    }
    if (key_code == key_left)
    {
      edubot.motor.setSpeed(-speed, speed);
      edubot.lcd.printf(0, 32,"좌회전   ");
    }
    if (key_code == key_right)
    {
      edubot.motor.setSpeed(speed, -speed);
      edubot.lcd.printf(0, 32,"우회전   ");
    }    
   
    if (key_code == key_led_left)
    {
      edubot.led.leftBright(0, 100, 0);    
      edubot.lcd.printf(0, 32,"왼쪽 LED  ");  
    }    

    if (key_code == key_led_right)
    {
      edubot.led.rightBright(0, 100, 0);    
      edubot.lcd.printf(0, 32,"오른쪽 LED");      
    }    

    edubot.lcd.display();

    pre_time = millis();    
  }

  if (millis()-pre_time >= 150)
  {
    edubot.motor.setSpeed(0, 0);
    edubot.led.leftBright(0, 0, 0);      
    edubot.led.rightBright(0, 0, 0);       
  }    
}