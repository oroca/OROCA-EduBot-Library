#include <EduBot.h>



void tof_setup() {
  // put your setup code here, to run once:
  
  edubot.begin(115200);       
}


void tof_loop() {
  // put your main code here, to run repeatedly

  edubot.lcd.clearDisplay();

  
  edubot.lcd.printf(0, 0 , "L %d mm", edubot.tof_L.distance_mm);
  edubot.lcd.printf(0, 16, "R %d mm", edubot.tof_R.distance_mm);

  edubot.lcd.display();
  
  delay(50);  

  Serial.print(edubot.tof_L.distance_mm);
  Serial.print(" ");
  Serial.println(edubot.tof_R.distance_mm);
}
