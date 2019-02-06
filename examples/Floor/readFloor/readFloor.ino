#include <EduBot.h>


EduBot edubot;



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
      edubot.lcd.fillRect(32*i, 64-sen[i], 10, sen[i], WHITE);      
    }    
    edubot.lcd.fillRect(64- 5 + (sen[1]-sen[2])/1, 4, 10, 4, WHITE);
  }
  else
  {
    edubot.lcd.printf(0, 0 , "L %d mm", edubot.tof_L.distance_mm);
    edubot.lcd.printf(0, 16, "R %d mm", edubot.tof_R.distance_mm);
  }
  edubot.lcd.display();
  
  delay(50);  

  if (edubot.buttonGetPressed() == true)
  {
    while(edubot.buttonGetPressed() == true);

    mode++;
    mode %= 2;
  }
  Serial.print(edubot.tof_L.distance_mm);
  Serial.print(" ");
  Serial.println(edubot.tof_R.distance_mm);
}
