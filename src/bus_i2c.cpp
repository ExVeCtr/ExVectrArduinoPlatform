#include "Arduino.h"

#include "ExVectrCore/print.hpp"

#include "ExVectrArduinoPlatform/bus_i2c.hpp"

using namespace VCTR::Platform;

VCTR::HAL::IO_TYPE_t BusI2CDevice::getInputType() const
{
    return HAL::IO_TYPE_t::BUS_I2C;
}

bool BusI2CDevice::setInputParam(HAL::IO_PARAM_t param, int32_t value)
{
    switch (param)
    {
    case HAL::IO_PARAM_t::SPEED :
        speed_ = value;
        bus_.setClock(speed_);
        return true;
        break;
    
    default:
        Core::printE("I2C Busdevice had incorrect input param type change. Param type: %d, Value:%d.\n", param, value);
        break;
    }
    return false;
}

VCTR::HAL::IO_TYPE_t BusI2CDevice::getOutputType() const
{
    return HAL::IO_TYPE_t::BUS_I2C;
}

bool BusI2CDevice::setOutputParam(HAL::IO_PARAM_t param, int32_t value)
{
    switch (param)
    {
    case HAL::IO_PARAM_t::SPEED :
        speed_ = value;
        bus_.setClock(speed_);
        return true;
        break;
    
    default:
        Core::printE("I2C Busdevice had incorrect output param type change. Param type: %d, Value:%d.\n", param, value);
        break;
    }
    return false;
}

BusI2CDevice::BusI2CDevice(TwoWire &bus, uint32_t address) : bus_(bus)
{
    address_ = address;
}

int32_t BusI2CDevice::writable()
{
    return -1;
}

size_t BusI2CDevice::writeData(const void *data, size_t size, bool endTransfer)
{   

    if (!inTransaction_)
        bus_.beginTransmission(static_cast<uint8_t>(address_));

    size_t ret = bus_.write((uint8_t *)data, size);

    if (bus_.endTransmission(endTransfer) != 0) //Failure
    {   
        bus_.endTransmission(true); //Try to force transmittion end.
        inTransaction_ = false;
        return 0;
    }

    inTransaction_ = !endTransfer;

    return ret;

}

size_t BusI2CDevice::readable()
{
    return 1;
}

size_t BusI2CDevice::readData(void *data, size_t size, bool endTransfer)
{   

    inTransaction_ = !endTransfer;

    if (bus_.requestFrom(static_cast<uint8_t>(address_), size, endTransfer) != size)
        return 0;
    uint32_t i;
    for (i = 0; bus_.available() > 0 && i < size; i++)
        ((uint8_t *)data)[i] = bus_.read();
    return bus_.available() ? 0 : i; // If more to read then requested something is wrong. In that case return 0 to indicate error.
}
