#include <EduBot.h>


namespace AppScratch      { extern void setup(); extern void loop(); }
namespace AppLineTrace    { extern void setup(); extern void loop(); }
namespace AppStepMotor    { extern void setup(); extern void loop(); }
namespace AppGetAcc       { extern void setup(); extern void loop(); }
namespace AppGetGyro      { extern void setup(); extern void loop(); }
namespace AppGetRpy       { extern void setup(); extern void loop(); }
namespace AppTof          { extern void setup(); extern void loop(); }
namespace AppAudio        { extern void setup(); extern void loop(); }
namespace AppNeoPixel     { extern void setup(); extern void loop(); }
namespace AppIrRemote     { extern void setup(); extern void loop(); }
namespace AppBattery      { extern void setup(); extern void loop(); }
namespace AppBitBlue      { extern void setup(); extern void loop(); }

 
void setup() {
  // put your setup code here, to run once:
  edubot.begin(115200);
  
  edubot.menuAdd("스크래치 3.0", AppScratch::setup,     AppScratch::loop);
  edubot.menuAdd("BitBlue",     AppBitBlue::setup,     AppBitBlue::loop);
  edubot.menuAdd("LineTrace",   AppLineTrace::setup,   AppLineTrace::loop);
  edubot.menuAdd("StepMotor",   AppStepMotor::setup,   AppStepMotor::loop);
  edubot.menuAdd("GetAcc",      AppGetAcc::setup,      AppGetAcc::loop);
  edubot.menuAdd("GetGyro",     AppGetGyro::setup,     AppGetGyro::loop);
  edubot.menuAdd("GetRPY",      AppGetRpy::setup,      AppGetRpy::loop);
  edubot.menuAdd("ToF",         AppTof::setup,         AppTof::loop);
  edubot.menuAdd("Audio",       AppAudio::setup,       AppAudio::loop);  
  edubot.menuAdd("NeoPixel",    AppNeoPixel::setup,    AppNeoPixel::loop);  
  edubot.menuAdd("IrRemote",    AppIrRemote::setup,    AppIrRemote::loop);  
  edubot.menuAdd("Battery",     AppBattery::setup,     AppBattery::loop);  
}

void loop() {
  // put your main code here, to run repeatedly:
  edubot.menuUpdate();
}


