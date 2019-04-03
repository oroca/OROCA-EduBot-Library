#include <EduBot.h>


namespace AppStepMotor
{

void setup() {
  // put your setup code here, to run once:
  int step_len = 500;
  
  edubot.begin(115200);                                   

  edubot.lcd.clearDisplay();
  edubot.lcd.printf(0, 0, "전진");
  edubot.lcd.display();

  edubot.motor.setStep(step_len, step_len);
  delay(1000);

  edubot.lcd.clearDisplay();
  edubot.lcd.printf(0, 0, "후진");
  edubot.lcd.display();

  edubot.motor.setStep(-step_len, -step_len, 50);
  delay(1000);  

  edubot.lcd.clearDisplay();
  edubot.lcd.printf(0, 0, "우회전");
  edubot.lcd.display();
  edubot.motor.setStep(step_len, 0);
  delay(1000);  

  edubot.lcd.clearDisplay();
  edubot.lcd.printf(0, 0, "좌회전");
  edubot.lcd.display();
  edubot.motor.setStep(-step_len, 0);
  delay(1000);  

  edubot.lcd.clearDisplay();
  edubot.lcd.printf(0, 0, "좌회전");
  edubot.lcd.display();  
  edubot.motor.setStep(0, step_len);
  delay(1000);  

  edubot.lcd.clearDisplay();
  edubot.lcd.printf(0, 0, "우회전");
  edubot.lcd.display();
  edubot.motor.setStep(0, -step_len);
  delay(1000);    
}

void loop() {
  // put your main code here, to run repeatedly: 
}

}