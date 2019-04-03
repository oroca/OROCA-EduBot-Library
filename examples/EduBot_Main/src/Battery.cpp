#include <EduBot.h>



namespace AppBattery
{

void setup() {
  // put your setup code here, to run once:
  
  edubot.begin(115200);   
}

void loop() {
  // put your main code here, to run repeatedly
  float vol;

  edubot.lcd.clearDisplay();
  edubot.lcd.printf(0, 0, "Battery Voltage");
  vol = edubot.batteryGetVoltage();
  edubot.lcd.printf(0, 16,"%1.1f V", vol/10);
  edubot.lcd.display();
  delay(100);
}

}