#ifndef TestRemoteDevice_h
#define TestRemoteDevice_h

#include <Arduino.h>
#include <RemoteDevice.h>
#include <LEDBlinker.h>


class TestRemoteDevice : public RemoteDevice
{
public:
    TestRemoteDevice();
    void update(unsigned long curTimeMS);
    virtual uint16_t onPacketReceived(uint16_t command, uint16_t arg1, uint16_t arg2, uint16_t arg3, uint16_t arg4, uint8_t* pData, uint16_t size);
private:
    LEDBlinker _blinker;
};

#endif