#ifndef EXVECTRARDUINOPLATFORM_PINGPIO_H
#define EXVECTRARDUINOPLATFORM_PINGPIO_H

#include "stdint.h"

#include "ExVectrHAL/pin_gpio.hpp"


namespace VCTR
{

namespace Platform
{

    /**
     * @brief Arduino implementation of GPIO.
    */
    class PinGPIO final : public VCTR::HAL::PinGPIO
    {
    private:

        int pin_ = -1;
        HAL::GPIO_IOMODE_t ioMode_ = HAL::GPIO_IOMODE_t::IOMODE_NONE;
        HAL::GPIO_PULL_t pinPull_ = HAL::GPIO_PULL_t::PULL_NONE;

        bool currentValue_ = false;

    public:

        PinGPIO();

        /**
         * Initialises GPIO.
         * @param pin Which pin to control.
         */
        void init(int32_t pin, HAL::GPIO_IOMODE_t mode) override;

        /**
         * @returns Which pin this controls.
         */
        int32_t getPin() override;

        /**
         * Sets pin value.
         * @param value Which value to set pin to.
         */
        void setPinValue(bool value) override;

        /**
         * @returns current pin value.
         */
        bool getPinValue() override;

        /**
         * Sets pin to given mode. Input/output.
         * @param mode Which mode to set pin to.
         */
        void setPinMode(HAL::GPIO_IOMODE_t mode) override;

        /**
         * @returns current pin mode.
         */
        HAL::GPIO_IOMODE_t getPinMode() override;

        /**
         * Sets pin to use given pullup or pulldown resistor or to remove.
         * 1 is pullup, 0 none, -1 pulldown.
         * @param pull Which pull mode to set pin to.
         */
        void setPinPull(HAL::GPIO_PULL_t pull) override;

        /**
         * 1 is pullup, 0 none, -1 pulldown.
         * @returns current pin pullmode.
         */
        HAL::GPIO_PULL_t getPinPull() override;

    };

    
}

}

#endif