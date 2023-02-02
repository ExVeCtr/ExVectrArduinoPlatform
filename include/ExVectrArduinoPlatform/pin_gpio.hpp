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
    class HAL_PinGPIO final : public VCTR::Interface::HAL_PinGPIO
    {
    private:

        int pin_ = -1;
        GPIO_IOMODE_t ioMode_ = GPIO_IOMODE_t::IOMODE_NONE;
        GPIO_PULL_t pinPull_ = GPIO_PULL_t::PULL_NONE;

        bool currentValue_ = false;

    public:

        HAL_PinGPIO();

        /**
         * Initialises GPIO.
         * @param pin Which pin to control.
         */
        void init(int32_t pin, GPIO_IOMODE_t mode) override;

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
        void setPinMode(GPIO_IOMODE_t mode) override;

        /**
         * @returns current pin mode.
         */
        GPIO_IOMODE_t getPinMode() override;

        /**
         * Sets pin to use given pullup or pulldown resistor or to remove.
         * 1 is pullup, 0 none, -1 pulldown.
         * @param pull Which pull mode to set pin to.
         */
        void setPinPull(GPIO_PULL_t pull) override;

        /**
         * 1 is pullup, 0 none, -1 pulldown.
         * @returns current pin pullmode.
         */
        GPIO_PULL_t getPinPull() override;

    };

    
}

}

#endif