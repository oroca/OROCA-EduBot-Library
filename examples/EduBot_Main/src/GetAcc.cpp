#include <EduBot.h>




void getacc_setup() {
  // put your setup code here, to run once: 
  edubot.begin(115200);                                   
}

void getacc_loop() {
  // put your main code here, to run repeatedly:
  static uint32_t pre_time; 

  
  if (millis()-pre_time >= 50)
  {
    pre_time = millis();

    edubot.lcd.clearDisplay();
    edubot.lcd.printf(16*0, 16*0, "aX : %f",edubot.imu.getAccX());
    edubot.lcd.printf(16*0, 16*1, "aY : %f",edubot.imu.getAccY());
    edubot.lcd.printf(16*0, 16*2, "aZ : %f",edubot.imu.getAccZ());
    edubot.lcd.display();
    
    Serial.print("aX : ");
    Serial.print(edubot.imu.getAccX());
    Serial.print("\taY : ");
    Serial.print(edubot.imu.getAccY());

    Serial.print("\taZ : ");
    Serial.print(edubot.imu.getAccZ());
    Serial.println();    
  }   
}