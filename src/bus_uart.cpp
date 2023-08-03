#include <cstring>
#include "Arduino.h"

#include "ExVectrCore/print.hpp"

#include "ExVectrArduinoPlatform/bus_uart.hpp"

using namespace VCTR::Platform;

VCTR::HAL::IO_TYPE_t BusUART::getInputType() const
{
    return HAL::IO_TYPE_t::BUS_UART;
}

bool BusUART::setInputParam(HAL::IO_PARAM_t param, int32_t value)
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

VCTR::HAL::IO_TYPE_t BusUART::getOutputType() const
{
    return HAL::IO_TYPE_t::BUS_UART;
}

bool BusUART::setOutputParam(HAL::IO_PARAM_t param, int32_t value)
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

BusUART::BusUART(HardwareSerial &bus) : bus_(bus)
{}

int32_t BusUART::writable()
{
    return bus_.availableForWrite();
}

size_t BusUART::writeData(const void *data, size_t size, bool endTransfer)
{

    return bus_.write((const uint8_t *)data, size);
}

size_t BusUART::readable()
{
    return 1;
}

size_t BusUART::readData(void *data, size_t size, bool endTransfer)
{

    return bus_.readBytes((uint8_t *)data, size);;
}

bool BusUART::writeRead(const void *writeBuf, void *readBuf, size_t writeSize, size_t readSize, bool endTransfer)
{   

    auto writeRet = bus_.write((const uint8_t *)writeBuf, writeSize);
    auto readRet =bus_.readBytes((uint8_t *)readBuf, readSize);

    return writeRet == writeSize && readRet == readSize;
    
}
