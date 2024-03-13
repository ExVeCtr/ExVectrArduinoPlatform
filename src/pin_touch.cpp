#include "ExVectrArduinoPlatform/pin_touch.hpp"

#include "Arduino.h"

using namespace VCTR::Platform;

/**
 * @brief Initializes the touch input.
 * @param pin The pin to use.
 */
void PinTouch::init(int32_t pin)
{
    pin_ = pin;
    pinMode(pin_, INPUT);
    touchRead(pin_); // First read is usually wrong.
}

/**
 * @brief Gets the type of input this is.
 * @return IO_TYPE_t enum.
 */
VCTR::HAL::IO_TYPE_t PinTouch::getInputType() const
{
    return HAL::IO_TYPE_t::OTHER;
}

/**
 * @brief Changes given parameter.
 * @param param What parameter to change.
 * @param value What to change parameter to.
 * @return True if successfull and parameter is supported.
 */
bool PinTouch::setInputParam(VCTR::HAL::IO_PARAM_t param, int32_t value)
{
    return false;
}

/**
 * @returns the number of values available to read at the moment.
 */
size_t PinTouch::readable()
{
    return 1;
}

size_t PinTouch::readValue(float* values, size_t size) 
{

    if (size == 0) {
        return 0;
    }

    values[0] = touchRead(pin_);

    return 1;

}