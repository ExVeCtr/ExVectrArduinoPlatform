#include "Arduino.h"

#include "ExVectrArduinoPlatform/pin_adc.hpp"


using namespace VCTR::Platform;


HAL_PinADC::HAL_PinADC() {
    pin_ = -1;
    res_ = 10;
}

void HAL_PinADC::init(int32_t pin) {
    pinMode(pin, INPUT);
}

int32_t HAL_PinADC::getPin() {
    return pin_;
}

int32_t HAL_PinADC::getPinValue() {
    return analogRead(pin_);
}

void HAL_PinADC::setPinResolution(uint32_t value) {
    res_ = value;
    analogReadResolution(value);
}

uint32_t HAL_PinADC::getPinResolution() {
    return res_;
}