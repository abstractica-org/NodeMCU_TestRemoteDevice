#include <Arduino.h>
#include "TestRemoteDevice.h"

TestRemoteDevice::TestRemoteDevice() : RemoteDevice(ESP.getChipId(), "TestRemoteDevice", 1), _blinker(2, false, 200, 400, 2000)
{

};

void TestRemoteDevice::update(unsigned long curTimeMS)
{
    RemoteDevice::update(curTimeMS);
    _blinker.update(curTimeMS);
};

uint16_t TestRemoteDevice::onPacketReceived(uint16_t command, uint16_t arg1, uint16_t arg2, uint16_t arg3, uint16_t arg4, uint8_t* pData, uint16_t size)
{
    if(command == 0)
    {
        _blinker.stopBlink();
        return 1;
    }
    else if(command == 1)
    {
        _blinker.startBlink(arg1);
        return 1;
    }
    else
    {
        Serial.print("Unknown command: ");
        Serial.println(command);
        return 0;
    }
};