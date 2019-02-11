#include <EduBot.h>


EduBot edubot;


void setup() {
  // put your setup code here, to run once:
  int step_len = 500;
  
  edubot.begin(115200);                                   
}

void loop() {
  // put your main code here, to run repeatedly:
  static uint32_t pre_time; 

  int x;
  int y;
  int magnitudeSquared;
  int16_t turnSpeed;
  float move_angle;

  x = (int)(edubot.imu.getPitch() * 10);
  y = (int)(edubot.imu.getRoll()  * 10);
  magnitudeSquared = x*x + y*y;


  move_angle = 30 * 30;
  
  if (magnitudeSquared > (int)(move_angle))
  {
    turnSpeed = y / 4;
  }
  else
  {
    turnSpeed = 0;
  }
    
  if (millis()-pre_time >= 100)
  {
    pre_time = millis();
    edubot.lcd.clearDisplay();

    edubot.lcd.printf(0, 16*0, "X : %d", x);
    edubot.lcd.printf(0, 16*1, "Y : %d", y);
    edubot.lcd.printf(0, 16*2, "M : %d", magnitudeSquared);
    edubot.lcd.printf(0, 16*3, "S : %d", turnSpeed);

    edubot.lcd.display();
  }   

  edubot.motor.setSpeed(-turnSpeed, turnSpeed);
}
