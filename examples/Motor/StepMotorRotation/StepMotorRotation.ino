#include <EduBot.h>

void setup() {
  // put your setup code here, to run once:
  edubot.begin(115200);

  edubot.motor.setRotation(40.0);  
  delay(1000);
  edubot.motor.setDistance(100, 100);
  delay(1000);
  edubot.motor.setRotation(120.0);
  delay(1000);
  edubot.motor.setDistance(100, 100);
  delay(1000);
  edubot.motor.setRotation(120.0);
  delay(1000);
  edubot.motor.setDistance(100, 100);
  delay(1000);
  edubot.motor.setRotation(90.0);
}

void loop() {
  // put your main code here, to run repeatedly:

}