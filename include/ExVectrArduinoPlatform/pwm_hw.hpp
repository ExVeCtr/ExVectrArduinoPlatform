#ifndef EXVECTRARDUINOPLATFORM_PWMHW_H
#define EXVECTRARDUINOPLATFORM_PWMHW_H

#include "stdint.h"
#include "stddef.h"

#include "ExVectrHAL/pin_pwm.hpp"

namespace VCTR
{

    namespace Platform
    {

        /**
         * @brief PWM implementation for ESP32 using hardware.
         */
        class PinPWM_HW final : public VCTR::HAL::PinPWM
        {
        private:
            static bool channelUsed_[16];
            static uint16_t channelRes_[16];
            static bool systemInitialised_;

            int32_t pin_ = -1;

            size_t channel_ = 0;

        public:

            PinPWM_HW();
        
            ~PinPWM_HW();

            /**
             * Initialises PWM output. Automatically allocates ESP32 channels.
             * @param pin Which pin to control.
             */
            void init(int32_t pin) override;

            /**
             * @returns Which pin this controls.
             */
            int32_t getPin() override;

            /**
             * @brief Sets the channel to which this pin is connected to.
             * @note Connecting two PinPWM_HW instances to the same channel will make each pin change dutycycle and frequency of other pins connected to this channel.
             * @param channel
             */
            void setChannel(size_t channel);

            /**
             * @brief Gets the pwm channel to which this PWM pin is connected to.
             * @return channel number this pin is connected to.
             */
            size_t getChannel();

            /**
             * Sets pin value. From 0 to 1.
             * @param value Which value to set pin to.
             */
            void setPinValue(float value) override;

            /**
             * @returns current pin value. 0 to 1.
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