#include <EduBot.h>



namespace AppLineTrace
{

static int step_speed = 90;

void setup() {
  // put your setup code here, to run once:
  
  edubot.begin(115200);                                     
}

void loop() {
  // put your main code here, to run repeatedly
  int x = 0;
  int y = 0;
  int sen[4];
  static uint8_t mode = 0;
  static int line_pos = 0;


  edubot.lcd.clearDisplay();


  sen[0] = edubot.floor_sensor.getRightOut();
  sen[1] = edubot.floor_sensor.getRightIn();
  sen[2] = edubot.floor_sensor.getLeftIn();
  sen[3] = edubot.floor_sensor.getLeftOut();

  
  if (mode == 0)
  {
    edubot.lcd.printf(0, 16*0, "%d", sen[0]);
    edubot.lcd.printf(0, 16*1, "%d", sen[1]);
    edubot.lcd.printf(0, 16*2, "%d", sen[2]);
    edubot.lcd.printf(0, 16*3, "%d", sen[3]);
  }
  else if (mode == 1) 
  {
    for (int i=0; i<4; i++)
    {
      sen[i] = map(sen[i], 0, 255, 1, 60);
      edubot.lcd.fillRect(11 + 32*i, 64-sen[i], 10, sen[i], WHITE);      
    }    

    line_pos = (sen[2]-sen[1])/1;
    
    edubot.lcd.fillRect(64- 5 + line_pos, 4, 10, 4, WHITE);


    int left_speed;
    int right_speed;

    left_speed = step_speed - line_pos*2;
    right_speed = step_speed + line_pos*2;

    if ( sen[1] < 2 && sen[2] < 2)
    {
      left_speed = 0;
      right_speed = 0;
    }

    edubot.led.leftBright(0, sen[2], 0);
    edubot.led.rightBright(0, sen[1], 0);

    if (edubot.tof_L.distance_mm < 60 || edubot.tof_R.distance_mm < 80)
    {
      left_speed = 0;
      right_speed = 0;      
    }
    edubot.motor.setSpeed(left_speed, right_speed);
    
  }
  else
  {
    edubot.motor.setSpeed(0, 0);
    edubot.lcd.printf(0, 0 , "L %d mm", edubot.tof_L.distance_mm);
    edubot.lcd.printf(0, 16, "R %d mm", edubot.tof_R.distance_mm);
  }
  edubot.lcd.display();
  
  delay(1);  

  if (edubot.buttonGetPressed() == true)
  {
    while(edubot.buttonGetPressed() == true);

    mode++;
    mode %= 3;
  }  
}

}