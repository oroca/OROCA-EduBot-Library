#include <EduBot.h>



namespace AppGetGyro
{

void setup() {
  // put your setup code here, to run once:
  edubot.begin(115200);                                   
}

void loop() {
  // put your main code here, to run repeatedly:
  static uint32_t pre_time; 


  if (millis()-pre_time >= 50)
  {
    pre_time = millis();

    edubot.lcd.clearDisplay();
    edubot.lcd.printf(16*0, 16*0, "gX : %f",edubot.imu.getGyroX());
    edubot.lcd.printf(16*0, 16*1, "gY : %f",edubot.imu.getGyroY());
    edubot.lcd.printf(16*0, 16*2, "gZ : %f",edubot.imu.getGyroZ());
    edubot.lcd.display();

    Serial.print("gX : ");
    Serial.print(edubot.imu.getGyroX());
    Serial.print("\tgY : ");
    Serial.print(edubot.imu.getGyroY());

    Serial.print("\tgZ : ");
    Serial.print(edubot.imu.getGyroZ());
    Serial.println();    
  }   
}

}