#include "Arduino.h"

#include "ExVectrArduinoPlatform/pin_adc.hpp"

using namespace VCTR::Platform;

PinADC::PinADC()
{
    res_ = 10;
}

void PinADC::init(int32_t pin)
{   
    pin_ = pin;
    pinMode(pin_, INPUT);
}

int32_t PinADC::getPinValue()
{
    return analogRead(pin_);
}

void PinADC::setPinResolution(uint32_t value)
{
    res_ = value;
    analogReadResolution(value);
}

uint32_t PinADC::getPinResolution()
{
    return res_;
}