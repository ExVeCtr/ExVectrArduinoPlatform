#include "Arduino.h"

#include "ExVectrArduinoPlatform/pin_pwm.hpp"


using namespace VCTR::Platform;


uint32_t HAL_PinPWM::res_ = 8;


HAL_PinPWM::HAL_PinPWM() {
    pin_ = -1;
    value_ = 0;
}

void HAL_PinPWM::init(int32_t pin) {
    pin_ = pin;
    pinMode(pin_, OUTPUT);
    analogWrite(pin_, 0);
}

int32_t HAL_PinPWM::getPin() {
    return pin_;
}

void HAL_PinPWM::setPinValue(float value) {
    value_ = value;

    if (value_ > 1.0) value_ = 1.0f;
    else if (value_ < 0.0) value_ = 0.0f;

    analogWrite(pin_, value_*(1<<getPinResolution()));
}

float HAL_PinPWM::getPinValue() {
    return value_;
}

void HAL_PinPWM::setPinFrequency(float value) {
    freq_ = value;
    analogWriteFrequency(pin_, freq_);
}

float HAL_PinPWM::getPinFrequency() {
    return freq_;
}

void HAL_PinPWM::setPinResolution(uint32_t value) {
    res_ = value;
    analogWriteResolution(res_);
}

uint32_t HAL_PinPWM::getPinResolution() {
    return res_;
}