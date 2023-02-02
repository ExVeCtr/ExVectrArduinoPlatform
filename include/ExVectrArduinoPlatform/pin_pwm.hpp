#ifndef EXVECTRARDUINOPLATFORM_PINPWM_H
#define EXVECTRARDUINOPLATFORM_PINPWM_H

#include "stdint.h"

#include "ExVectrHAL/pin_pwm.hpp"


namespace VCTR
{

namespace Platform
{

    /**
     * @brief Arduino implementation of PWM output.
     * @note All pins use the same resolution!
    */
    class HAL_PinPWM final : public VCTR::Interface::HAL_PinPWM
    {
    private:

        int pin_ = -1;
        float value_ = 0;
        static uint32_t res_;
        float freq_ = 200;

    public:

        HAL_PinPWM();

        /**
         * Initialises PWM output.
         * @param pin Which pin to control.
         */
        void init(int32_t pin) override;

        /**
         * @returns Which pin this controls.
         */
        int32_t getPin() override;

        /**
         * Sets pin value. Duty cycle from 0 to 1.
         * @param value Which value to set pin to.
         */
        void setPinValue(float value) override;

        /**
         * @returns current pin value. Duty cycle from 0 to 1.
         */
        float getPinValue() override;

        /**
         * Sets pwm frequency.
         * @param value Which frequency [Hz] to set PWM to.
         */
        void setPinFrequency(float value) override;

        /**
         * @returns current PWM Frequency.
         */
        float getPinFrequency() override;

        /**
         * Sets pwm resolution.
         * @param value Which resolution [bits] to set PWM to.
         */
        void setPinResolution(uint32_t value) override;

        /**
         * @returns current PWM resolution.
         */
        uint32_t getPinResolution() override;

    };

    
}

}

#endif