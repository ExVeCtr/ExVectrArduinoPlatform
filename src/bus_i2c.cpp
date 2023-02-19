#include "ExVectrArduinoPlatform/bus_i2c.hpp"


using namespace VCTR::Platform;


BusI2CDevice::BusI2CDevice(TwoWire& bus, uint32_t address): bus_(bus) {
    address_ = address;
}

int32_t BusI2CDevice::writable() {
    return -1;
}

size_t BusI2CDevice::writeData(const void* data, size_t size, bool endTransfer) {
    bus_.beginTransmission(static_cast<uint8_t>(address_));
    size_t ret = bus_.write((uint8_t*)data, size);
    if (bus_.endTransmission(endTransfer)) {
        return ret;
    } else {
        return 0;
    }
}

size_t BusI2CDevice::readable() {
    return 1;
}

size_t BusI2CDevice::readData(void* data, size_t size, bool endTransfer) {
    if (bus_.requestFrom(static_cast<uint8_t>(address_), size, endTransfer) != size) return 0;
    uint32_t i;
    for (i = 0; bus_.available() > 0 && i < size; i++) ((uint8_t*)data)[i] = bus_.read(); 
    return bus_.available() ? 0 : i; //If more to read then requested something is wrong. In that case return 0 to indicate error.
}
