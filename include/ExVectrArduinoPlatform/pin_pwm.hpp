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
        class PinPWM final : public VCTR::HAL::PinPWM
        {
        private:
            float value_ = 0;
            static uint32_t res_;
            float freq_ = 200;

        public:
            PinPWM(int32_t pin);

            /**
             * Initialises PWM output.
             */
            void init() override;

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