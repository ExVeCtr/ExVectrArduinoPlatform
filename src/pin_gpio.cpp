#include "Arduino.h"

#include "ExVectrArduinoPlatform/pin_gpio.hpp"


using namespace VCTR::Platform;


PinGPIO::PinGPIO() {
    pin_ = -1;
}

void PinGPIO::init(int32_t pin, GPIO_IOMODE_t mode) {

    pin_ = pin;

    ioMode_ = mode;
    pinPull_ = GPIO_PULL_t::PULL_NONE;

    pinMode(pin_, ioMode_ == GPIO_IOMODE_t::IOMODE_OUTPUT ? OUTPUT : INPUT);

    if (ioMode_ == GPIO_IOMODE_t::IOMODE_OUTPUT) digitalWrite(pin_, LOW);

}

int32_t PinGPIO::getPin() {
    return pin_;
}

void PinGPIO::setPinValue(bool value) {
    if (ioMode_ != GPIO_IOMODE_t::IOMODE_OUTPUT) return;
    if (currentValue_ != value) {
        currentValue_ = value;
        digitalWrite(pin_, value);
    }
}

bool PinGPIO::getPinValue() {
    if (ioMode_ == GPIO_IOMODE_t::IOMODE_OUTPUT) {
        return currentValue_;
    } else {
        return digitalRead(pin_);
    }
}

void PinGPIO::setPinMode(GPIO_IOMODE_t mode) {
    ioMode_ = mode;
    pinMode(pin_, ioMode_ == GPIO_IOMODE_t::IOMODE_OUTPUT ? OUTPUT : INPUT);
}

VCTR::GPIO_IOMODE_t PinGPIO::getPinMode() {
    return ioMode_;
}

void PinGPIO::setPinPull(GPIO_PULL_t pull) {
    if (ioMode_ != GPIO_IOMODE_t::IOMODE_INPUT) return;

    #ifdef INPUT_PULLUP
        if (pull == GPIO_PULL_t::PULL_UP) {
            pinPull_ = pull;
            pinMode(pin_, INPUT_PULLUP);
        }
    #endif

    #ifdef INPUT_PULLDOWN
        if (pull == GPIO_PULL_t::PULL_DOWN) {
            pinPull_ = pull;
            pinMode(pin_, INPUT_PULLDOWN);
        }
    #endif

}

VCTR::GPIO_PULL_t PinGPIO::getPinPull() {
    return pinPull_;
}

