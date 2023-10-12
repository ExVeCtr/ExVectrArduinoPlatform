#include "Arduino.h"

#include "ExVectrArduinoPlatform/pin_pwm.hpp"

using namespace VCTR::Platform;

uint32_t PinPWM::res_ = 8;

PinPWM::PinPWM(int32_t pin) : HAL::PinPWM(pin)
{
    value_ = 0;
}

void PinPWM::init()
{
    pinMode(pin_, OUTPUT);
    analogWrite(pin_, 0);
}

void PinPWM::setPinValue(float value)
{
    value_ = value;

    if (value_ > 1.0)
        value_ = 1.0f;
    else if (value_ < 0.0)
        value_ = 0.0f;

    analogWrite(pin_, value_ * (1 << getPinResolution()));
}

float PinPWM::getPinValue()
{
    return value_;
}

void PinPWM::setPinFrequency(float value)
{
    freq_ = value;
    analogWriteFrequency(pin_, freq_);
}

float PinPWM::getPinFrequency()
{
    return freq_;
}

void PinPWM::setPinResolution(uint32_t value)
{
    res_ = value;
    analogWriteResolution(res_);
}

uint32_t PinPWM::getPinResolution()
{
    return res_;
}