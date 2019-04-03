/* Authors: byeongkyu, baram */
#include <EduBot.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <image/EduBoy.h>


namespace AppBitBlue
{

#define HM10_SERVICE_UUID                  "0000ffe0-0000-1000-8000-00805f9b34fb"
#define HM10_CHARACTERISTIC_UUID           "0000ffe1-0000-1000-8000-00805f9b34fb"




typedef struct 
{
  uint8_t len;
  uint8_t buffer[20];  
} rx_buffer_t;

static uint32_t rx_len = 16;
static uint32_t rx_in = 0;
static uint32_t rx_out = 0;
static rx_buffer_t rx_buffer[16];



static bool device_connected = false;
static uint8_t ble_mac_addr[6] = {0, };


static BLECharacteristic *mHM10Char = NULL;



class MyBLEServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    device_connected = true;
  }

  void onConnect(BLEServer* pServer, esp_ble_gatts_cb_param_t *param) {
    Serial.println("connect");
  };

  void onDisconnect(BLEServer* pServer) {
    device_connected = false;
  }
};

class HM10Callbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();


    rx_buffer[rx_in].len = value.length();
    for (int i=0; i<value.length(); i++)
    {
      rx_buffer[rx_in].buffer[i] = value[i];
    }
    rx_in++;
    if (rx_in >= rx_len)
    {
      rx_in = 0;
    }

#if 0
    Serial.print("len : ");
    Serial.print(value.length());
    Serial.print(" ");
    for (int i=0; i<value.length(); i++)
    {
      Serial.print(value[i], HEX);
      Serial.print(" ");      
    }
    Serial.println();
#endif      
  }

};

static void drawLcdConnected(bool connected);
static void loopUpdate(bool run);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  

  Serial.println("Start BitBlue");

  BLEDevice::init("OROCA_EduBot");


  BLEAddress ble_addr = BLEDevice::getAddress();  
  memcpy(ble_mac_addr, *ble_addr.getNative(), 6);

  BLEServer *mServer = BLEDevice::createServer();
  mServer->setCallbacks(new MyBLEServerCallbacks());


  // HM10 Service
  BLEService *mHM10Service = mServer->createService(HM10_SERVICE_UUID);

  mHM10Char = mHM10Service->createCharacteristic(
                                         HM10_CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_WRITE_NR |
                                         BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  mHM10Char->setCallbacks(new HM10Callbacks());
  mHM10Char->addDescriptor(new BLE2902());

  mHM10Service->start();
 

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();  
  pAdvertising->addServiceUUID(HM10_SERVICE_UUID);

  
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  

  edubot.begin(115200);  
  edubot.motor.setAcc(2, 2);
}


void loop() {
  // put your main code here, to run repeatedly:
  static uint8_t state = 0;
  static bool pre_connected = device_connected;


  if (device_connected == false && pre_connected == true)
  {
    state = 99;        
  }
  pre_connected = device_connected;

  switch(state)
  {
    case 0:
      drawLcdConnected(false);
      if (device_connected)
      {
        drawLcdConnected(true);
        state = 1;        
      }
      break;

    case 1:
      loopUpdate(true);
      break;

    case 99:
      loopUpdate(false);
      state = 0;
      break;
  }
}

void drawLcdConnected(bool connected)
{
  if (connected == true)
  {
    edubot.lcd.printf(16, (16*0), " -BitBlue-");
    edubot.lcd.printf(16, (16*1), " 접속완료!");
  }
  else
  {
    edubot.lcd.printf(16, (16*0), " -BitBlue-");
    edubot.lcd.printf(16, (16*1), "접속대기 중!");
    edubot.lcd.printf(18, (16*3), "%02X:%02X:%02X:%02X", ble_mac_addr[2], ble_mac_addr[3], ble_mac_addr[4], ble_mac_addr[5]);
  }
  edubot.lcd.display();
  edubot.lcd.clearDisplay();
}

void loopUpdate(bool run)
{
  int speed = 150;

  if (run == false)
  {
    edubot.motor.setSpeed(0, 0);
    return;
  }

  if (rx_in != rx_out)
  {
    uint32_t rx_i;

    rx_i = rx_out;
    rx_out++;
    if (rx_out >= rx_len)
    {
      rx_out = 0;
    }

    if (rx_buffer[rx_i].len == 1)
    {
      if (rx_buffer[rx_i].buffer[0] == 'Y')
      {
        edubot.led.rightBright(0, 100, 0); 
        delay(100);
        edubot.led.rightBright(0, 0, 0); 
      }
      if (rx_buffer[rx_i].buffer[0] == 'A')
      {
        edubot.led.leftBright(0, 100, 0); 
        delay(100);
        edubot.led.leftBright(0, 0, 0); 
      }
    }
    if (rx_buffer[rx_i].len == 16)
    {
      String l_str = "";
      String r_str = "";
      String f_str = "";
      String b_str = "";
      int x;
      int y;

      for (int i=0; i<3; i++)
      {
        l_str += (char)rx_buffer[rx_i].buffer[1+i];
        r_str += (char)rx_buffer[rx_i].buffer[5+i];
        f_str += (char)rx_buffer[rx_i].buffer[9+i];
        b_str += (char)rx_buffer[rx_i].buffer[13+i];
      }
      x = l_str.toInt() - r_str.toInt();
      y = f_str.toInt() - b_str.toInt();

      int left_speed;
      int right_speed;

      left_speed  = y*1 - x*1;
      right_speed = y*1 + x*1;
      edubot.motor.setSpeed(left_speed/2, right_speed/2);      
    }
  }
}

}