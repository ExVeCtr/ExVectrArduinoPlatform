#include "cstring"

#include "ExVectrArduinoPlatform/bus_spi.hpp"


using namespace VCTR::Platform;


BusSPIDevice::BusSPIDevice(SPIClass& bus, const SPISettings& spiSettings, VCTR::HAL::PinGPIO& pin, bool invertSelectPin): bus_(bus), pin_(pin) {
    spiSettings_ = spiSettings;
    pinInvert_ = invertSelectPin;
}

int32_t BusSPIDevice::writable() {
    return -1;
}

size_t BusSPIDevice::writeData(const void* data, size_t size, bool endTransfer) {

    //Needed because arduino spi function does not support const void* parameter.      ):
    uint8_t buffer[size];
    memcpy(buffer, data, size);

    pin_.setPinValue(!pinInvert_);

    bus_.beginTransaction(spiSettings_);
    bus_.transfer(buffer, size);
    
    if (endTransfer) {
        bus_.endTransaction();
        pin_.setPinValue(pinInvert_);
    }

    return size;

}

size_t BusSPIDevice::readable() {
    return 1;
}

size_t BusSPIDevice::readData(void* data, size_t size, bool endTransfer) {

    pin_.setPinValue(!pinInvert_);

    bus_.beginTransaction(spiSettings_);
    bus_.transfer(data, size);
    
    if (endTransfer) {
        bus_.endTransaction();
        pin_.setPinValue(pinInvert_);
    }

    return size;

}

bool BusSPIDevice::writeRead(const void* writeBuf, void* readBuf, size_t writeSize, size_t readSize, bool endTransfer) {

    size_t smallest = writeSize;
    size_t largest = readSize;
    if (smallest < readSize) {
        smallest = readSize;
        largest = writeSize;
    }

    memcpy(readBuf, writeBuf, smallest); //Need to do this due to the limited spi api from ESP32 arduino.

    size_t rest = largest - smallest;

    pin_.setPinValue(!pinInvert_);

    bus_.beginTransaction(spiSettings_);
    bus_.transfer(readBuf, smallest);

    if (writeSize > readSize) {
        uint8_t buffer[rest];
        memcpy(buffer, writeBuf + smallest, writeSize);
        bus_.transfer(buffer, rest);
    } else if (readSize > writeSize) {
        bus_.transfer(readBuf + smallest, rest);
    }
    
    if (endTransfer) {
        bus_.endTransaction();
        pin_.setPinValue(pinInvert_);
    }

    return true;

}
