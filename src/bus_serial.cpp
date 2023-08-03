#include <cstring>
#include "Arduino.h"

#include "ExVectrCore/print.hpp"

#include "ExVectrArduinoPlatform/bus_serial.hpp"

using namespace VCTR::Platform;

VCTR::HAL::IO_TYPE_t BusSerial::getInputType() const
{
    return HAL::IO_TYPE_t::BUS_UART;
}

bool BusSerial::setInputParam(HAL::IO_PARAM_t param, int32_t value)
{
    switch (param)
    {
    case HAL::IO_PARAM_t::SPEED:
        bus_.begin(value);
        return true;
        break;

    default:
        Core::printE("Serial bus had incorrect input param type change. Param type: %d, Value:%d.\n", param, value);
        break;
    }
    return false;
}

VCTR::HAL::IO_TYPE_t BusSerial::getOutputType() const
{
    return HAL::IO_TYPE_t::BUS_UART;
}

bool BusSerial::setOutputParam(HAL::IO_PARAM_t param, int32_t value)
{
    switch (param)
    {
    case HAL::IO_PARAM_t::SPEED:
        bus_.begin(value);
        return true;
        break;

    default:
        Core::printE("Serial bus had incorrect input param type change. Param type: %d, Value:%d.\n", param, value);
        break;
    }
    return false;
}

BusSerial::BusSerial(HardwareSerial &bus) : bus_(bus)
{}

int32_t BusSerial::writable()
{
    return bus_.availableForWrite();
}

size_t BusSerial::writeData(const void *data, size_t size, bool endTransfer)
{

    return bus_.write((const uint8_t *)data, size);
}

size_t BusSerial::readable()
{
    return 1;
}

size_t BusSerial::readData(void *data, size_t size, bool endTransfer)
{

    return bus_.readBytes((uint8_t *)data, size);;
}

bool BusSerial::writeRead(const void *writeBuf, void *readBuf, size_t writeSize, size_t readSize, bool endTransfer)
{   

    auto writeRet = bus_.write((const uint8_t *)writeBuf, writeSize);
    auto readRet =bus_.readBytes((uint8_t *)readBuf, readSize);

    return writeRet == writeSize && readRet == readSize;
    
}
