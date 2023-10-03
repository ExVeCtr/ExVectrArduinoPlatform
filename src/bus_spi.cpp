#include <cstring>
#include "Arduino.h"

#include "ExVectrCore/print.hpp"

#include "ExVectrArduinoPlatform/bus_spi.hpp"

using namespace VCTR::Platform;

VCTR::HAL::IO_TYPE_t BusSPIDevice::getInputType() const
{
    return HAL::IO_TYPE_t::BUS_SPI;
}

bool BusSPIDevice::setInputParam(HAL::IO_PARAM_t param, int32_t value)
{
    switch (param)
    {
    case HAL::IO_PARAM_t::SPEED:
        speed_ = value;
        return true;
        break;

    case HAL::IO_PARAM_t::MSB_FIRST :
        msbFirst_ = value;
        return true;
        break;

    case HAL::IO_PARAM_t::SPI_MODE :

        if (value == 0)
            spiMode_ = SPI_MODE0;
        else if (value == 1)
            spiMode_ = SPI_MODE1;
        else if (value == 2)
            spiMode_ = SPI_MODE2;
        else if (value == 3)
            spiMode_ = SPI_MODE3;
        else
        {
            Core::printE("SPI Busdevice had incorrect input param value for SPI mode. Param value:%d.\n", value);
        }

        return true;
        break;

    default:
        Core::printE("SPI Busdevice had incorrect input param type change. Param type: %d, Value:%d.\n", param, value);
        break;
    }
    return false;
}

VCTR::HAL::IO_TYPE_t BusSPIDevice::getOutputType() const
{
    return HAL::IO_TYPE_t::BUS_SPI;
}

bool BusSPIDevice::setOutputParam(HAL::IO_PARAM_t param, int32_t value)
{
    switch (param)
    {
    case HAL::IO_PARAM_t::SPEED:
        speed_ = value;
        return true;
        break;

    case HAL::IO_PARAM_t::MSB_FIRST :
        msbFirst_ = value;
        return true;
        break;

    case HAL::IO_PARAM_t::SPI_MODE :

        if (value == 0)
            spiMode_ = SPI_MODE0;
        else if (value == 1)
            spiMode_ = SPI_MODE1;
        else if (value == 2)
            spiMode_ = SPI_MODE2;
        else if (value == 3)
            spiMode_ = SPI_MODE3;
        else
        {
            Core::printE("SPI Busdevice had incorrect input param value for SPI mode. Param value:%d.\n", value);
        }

        return true;
        break;

    default:
        Core::printE("SPI Busdevice had incorrect input param type change. Param type: %d, Value:%d.\n", param, value);
        break;
    }
    return false;
}

BusSPIDevice::BusSPIDevice(SPIClass &bus, VCTR::HAL::PinGPIO &pin, bool invertSelectPin) : bus_(bus), pin_(pin)
{
    // spiSettings_ = spiSettings;
    pinInvert_ = invertSelectPin;
}

size_t BusSPIDevice::writable()
{
    return 1;
}

size_t BusSPIDevice::writeData(const void *data, size_t size, bool endTransfer)
{

    // Needed because arduino spi function does not support const void* parameter.      ):
    uint8_t buffer[size];
    memcpy(buffer, data, size);

    if (!inTransaction_)
        pin_.setPinValue(!pinInvert_);

    spiSettings_ = SPISettings{speed_, uint8_t(msbFirst_ ? MSBFIRST : LSBFIRST), spiMode_};
    if (!inTransaction_)
        bus_.beginTransaction(spiSettings_);

    bus_.transfer(buffer, size);

    if (endTransfer)
    {
        bus_.endTransaction();
        pin_.setPinValue(pinInvert_);

        inTransaction_ = false;
    }
    else
    {
        inTransaction_ = true;
    }

    return size;
}

size_t BusSPIDevice::readable()
{
    return 1;
}

size_t BusSPIDevice::readData(void *data, size_t size, bool endTransfer)
{

    if (!inTransaction_)
        pin_.setPinValue(!pinInvert_);

    spiSettings_ = SPISettings{speed_, uint8_t(msbFirst_ ? MSBFIRST : LSBFIRST), spiMode_};
    if (!inTransaction_)
        bus_.beginTransaction(spiSettings_);

    bus_.transfer(data, size);

    if (endTransfer)
    {
        bus_.endTransaction();
        pin_.setPinValue(pinInvert_);

        inTransaction_ = false;
    }
    else
    {
        inTransaction_ = true;
    }

    return size;
}

bool BusSPIDevice::writeRead(const void *writeBuf, void *readBuf, size_t writeSize, size_t readSize, bool endTransfer)
{   

    size_t bufLen = writeSize;
    if (readSize > writeSize)
        bufLen = readSize;
    uint8_t buffer[bufLen];
    memcpy(buffer, writeBuf, bufLen);

    if (!inTransaction_)
        pin_.setPinValue(!pinInvert_);

    spiSettings_ = SPISettings{speed_, uint8_t(msbFirst_ ? MSBFIRST : LSBFIRST), spiMode_};
    if (!inTransaction_)
        bus_.beginTransaction(spiSettings_);

    bus_.transfer(buffer, bufLen);

    if (endTransfer)
    {
        bus_.endTransaction();
        pin_.setPinValue(pinInvert_);

        inTransaction_ = false;
    }
    else
    {
        inTransaction_ = true;
    }

    memcpy(readBuf, buffer, readSize);

    return true;
    
}
