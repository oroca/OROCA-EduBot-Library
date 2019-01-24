#include <EduBot.h>


EduBot edubot;


void setup() {
  // put your setup code here, to run once:
  int step_len = 500;
  
  edubot.begin(115200);                                   

  edubot.motor.setStep(step_len, step_len);
  delay(3000);
  edubot.motor.setStep(-step_len, -step_len, 50);
  delay(3000);  
  edubot.motor.setStep(-step_len, step_len);
  delay(3000);  
  edubot.motor.setStep(step_len, -step_len);
  delay(3000);    
}

void loop() {
  // put your main code here, to run repeatedly: 
}