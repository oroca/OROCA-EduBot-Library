#include <EduBot.h>
#include "logo.h"




void setup() {
  // put your setup code here, to run once:
  
  edubot.begin(115200);                                   
}

void loop() {
  // put your main code here, to run repeatedly
  static int cnt = 0;
  uint32_t pre_time;
  static int i = 0;
  int x = 0;
  int y = 0;


  pre_time = micros();
  edubot.lcd.clearDisplay();

  edubot.lcd.drawBitmap(0, 8, &logo[i*48*48/8], 48, 48, 1);
  i++;
  i %= 4;

  edubot.lcd.printf(48+5, 16-6, "OROCA");
  edubot.lcd.printf(48+5, 32-6, "EduBot");
  edubot.lcd.printf(48+5, 48-6, "바람");
  
  edubot.lcd.display();
  Serial.println(micros()-pre_time);
  delay(50);
}

