#ifndef  _DRIVER_BLE_BLE_H
#define  _DRIVER_BLE_BLE_H

#include "../def.h"

#ifdef EDUBOT_DRIVER_BLE

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLEBeacon.h>
#include <BLE2902.h>

typedef struct BLEServiceCharConfig{
  const char* uuid;
  uint32_t properties;
  BLECharacteristicCallbacks *callback;
}BLEServiceCharConfig;

class BLE
{
  public:
    BLE();

    void begin(const char* device_name);
    void setServiceAndAdvertise(const char *service_uuid, BLEServiceCharConfig *char_list);
    void advertiseServer(void);
    void maintain(uint32_t interval_ms);

    class BLEServerCallback : public BLEServerCallbacks
    {
      void onConnect(BLEServer* pServer);
      void onDisconnect(BLEServer* pServer);
    };

  private:
    BLEServer *pServer_;
};


#endif

#endif  /* _DRIVER_BLE_BLE_H */