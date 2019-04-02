#include <EduBot.h>


extern void scratch_setup();
extern void scratch_loop();
extern void linetrace_setup();
extern void linetrace_loop();
extern void stepmotor_setup();
extern void stepmotor_loop();
extern void getacc_setup();
extern void getacc_loop();
extern void getgyro_setup();
extern void getgyro_loop();
extern void getrpy_setup();
extern void getrpy_loop();
extern void tof_setup();
extern void tof_loop();
extern void audio_setup();
extern void audio_loop();
extern void neopixel_setup();
extern void neopixel_loop();
extern void irremote_setup();
extern void irremote_loop();
extern void battery_setup();
extern void battery_loop();
 
void setup() {
  // put your setup code here, to run once:
  edubot.begin(115200);
  
  edubot.menuAdd("스크래치 3.0", scratch_setup, scratch_loop);
  edubot.menuAdd("LineTrace", linetrace_setup, linetrace_loop);
  edubot.menuAdd("StepMotor", stepmotor_setup, stepmotor_loop);
  edubot.menuAdd("GetAcc", getacc_setup, getacc_loop);
  edubot.menuAdd("GetGyro", getgyro_setup, getgyro_loop);
  edubot.menuAdd("GetRPY", getrpy_setup, getrpy_loop);
  edubot.menuAdd("ToF", tof_setup, tof_loop);
  edubot.menuAdd("Audio", audio_setup, audio_loop);  
  edubot.menuAdd("NeoPixel", neopixel_setup, neopixel_loop);  
  edubot.menuAdd("IrRemote", irremote_setup, irremote_loop);  
  edubot.menuAdd("Battery", battery_setup, battery_loop);  
}

void loop() {
  // put your main code here, to run repeatedly:
  edubot.menuUpdate();
}


