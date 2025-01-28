#include <Arduino.h>
#include "TestRemoteDevice.h"

TestRemoteDevice::TestRemoteDevice() : RemoteDevice(ESP.getChipId(), "TestRemoteDevice", 1), _blinker(2, false, 200, 400, 2000)
{
    _curTime = 0;
    _BlinkerEndTime = 0;
    _stopSend = true;
};

void TestRemoteDevice::update(unsigned long curTimeMS)
{
    _curTime = curTimeMS;
    RemoteDevice::update(curTimeMS);
    _blinker.update(curTimeMS);
    if(!_stopSend)
    {
        _stopSend = sendPacketToServer(CMD_BLINK_STOPPED, 1, 2, 3, 4);
    }
    if(_blinker.isBlinking() && _curTime > _BlinkerEndTime)
    {
        _blinker.stopBlink();
        _stopSend = sendPacketToServer(CMD_BLINK_STOPPED, 1, 2, 3, 4);
    }
};

uint16_t TestRemoteDevice::onPacketReceived(uint16_t command, uint16_t arg1, uint16_t arg2, uint16_t arg3, uint16_t arg4, uint8_t* pData, uint16_t size)
{
    if(command == CMD_START_BLINK)
    {
        _blinker.startBlink(arg1);
        _BlinkerEndTime = _curTime + arg2*1000;
        return 0;
    }
    else
    {
        Serial.print("Unknown command: ");
        Serial.println(command);
        return 0;
    }
};