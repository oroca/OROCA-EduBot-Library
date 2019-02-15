
#include "ble.h"

#ifdef EDUBOT_DRIVER_BLE

static bool g_deviceConnected;
static bool g_oldDeviceConnected;
static uint32_t g_disconnected_time;


BLE::BLE()
{
  g_oldDeviceConnected = false;
  g_deviceConnected = false;
  g_disconnected_time = millis();
}

void BLE::begin(const char* device_name)
{
  // Create the BLE Device
  BLEDevice::init(device_name);
  // Create the BLE Server
  pServer_ = BLEDevice::createServer();
  pServer_->setCallbacks(new BLEServerCallback());

  this->advertiseServer();
}

void BLE::setServiceAndAdvertise(const char *service_uuid, BLEServiceCharConfig *char_list)
{
  // Create the BLE Service
  BLEService *pService = pServer_->createService(service_uuid);
  
  // Create a BLE Characteristic
  uint32_t cnt = 0;
  BLECharacteristic *pCharacteristic;
  BLEServiceCharConfig *pCharConfig = &char_list[cnt];

  while(pCharConfig->uuid != NULL)
  {
    pCharacteristic = pService->createCharacteristic(
        pCharConfig->uuid,
        pCharConfig->properties);
  
    pCharacteristic->setCallbacks(pCharConfig->callback);      
    pCharacteristic->addDescriptor(new BLE2902());

    pCharConfig = &char_list[++cnt];
  }

  if(cnt > 0)
  {
    // Start the service
    pService->start();
  
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(service_uuid);    
  }  
}

void BLE::advertiseServer(void)
{
  if(pServer_ == NULL)
    return;
  pServer_->startAdvertising();
}

void BLE::maintain(uint32_t interval_ms)
{
  if (g_deviceConnected)
  {
    g_disconnected_time = millis();
  }
  // disconnecting
  if (!g_deviceConnected && g_oldDeviceConnected)
  {
    if (millis() - g_disconnected_time > interval_ms) // give the bluetooth stack the chance to get things ready
    {
      g_disconnected_time = millis();
      this->advertiseServer();
      g_oldDeviceConnected = g_deviceConnected;
    }
  }
  // connecting
  if (g_deviceConnected && !g_oldDeviceConnected)
  {
    // do stuff here on connecting
    g_oldDeviceConnected = g_deviceConnected;
  }
}

void BLE::BLEServerCallback::onConnect(BLEServer* pServer)
{
  g_deviceConnected = true;
}

void BLE::BLEServerCallback::onDisconnect(BLEServer* pServer)
{
  g_deviceConnected = false;
}


#endif