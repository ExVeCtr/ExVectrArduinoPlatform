#include "ExVectrArduinoPlatform/bus_spi.hpp"


using namespace VCTR::Platform;


BusSPIDevice::BusSPIDevice(SPIClass& bus, const SPISettings& spiSettings, VCTR::HAL::PinGPIO& pin, bool invertSelectPin): bus_(bus), pin_(pin) {
    spiSettings_ = spiSettings;
    pinInvert_ = invertSelectPin;
}

int32_t BusSPIDevice::writable() {
    return -1;
}

size_t BusSPIDevice::writeData(const void* data, size_t size) {

    //Needed because arduino spi function does not support const void* parameter.      ):
    uint8_t buffer[size];
    memcpy(buffer, data, size);

    pin_.setPinValue(!pinInvert_);

    bus_.beginTransaction(spiSettings_);
    bus_.transfer(buffer, size);
    bus_.endTransaction();
    
    pin_.setPinValue(pinInvert_);

    return size;

}

size_t BusSPIDevice::readable() {
    return 1;
}

size_t BusSPIDevice::readData(void* data, size_t size) {

    pin_.setPinValue(!pinInvert_);

    bus_.beginTransaction(spiSettings_);
    bus_.transfer(data, size);
    bus_.endTransaction();
    
    pin_.setPinValue(pinInvert_);

    return size;

}

bool BusSPIDevice::writeRead(const void* writeBuf, void* readBuf, size_t writeSize, size_t readSize) {

    uint8_t buffer[writeSize];
    memcpy(buffer, writeBuf, writeSize);

    pin_.setPinValue(!pinInvert_);

    bus_.beginTransaction(spiSettings_);
    bus_.transfer(buffer, writeSize);
    bus_.transfer(readBuf, readSize);
    bus_.endTransaction();
    
    pin_.setPinValue(pinInvert_);

    return true;

}
