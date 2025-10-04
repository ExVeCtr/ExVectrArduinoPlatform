#ifndef EXVECTRARDUINOPLATFORM_INTERRUPTEVENT_HPP
#define EXVECTRARDUINOPLATFORM_INTERRUPTEVENT_HPP

#include "stdint.h"

#include "ExVectrHAL/interrupt_event.hpp"

#include "Arduino.h"


namespace VCTR
{

    namespace Platform
    {   

        HAL::InterruptEvent * interruptEvent = nullptr;

        void pinInterruptHandler() {

            if (interruptEvent != nullptr) {
                interruptEvent->trigger();
            }

        }

        /**
         * @brief Implements an interrupt event for a GPIO pin. ONLY SUPPORTS A SINGLE PIN AT A TIME!
         */
        template <typename CALLBACKTYPE>
        class Interrupt_GPIO : public HAL::InterruptEvent
        {
        protected:
           
            void (CALLBACKTYPE::*callbackFunc_)(void) = nullptr;
            CALLBACKTYPE *object_ = nullptr;

            int pin_ = -1;

        public:

            Interrupt_GPIO(int32_t pin) {
                pin_ = pin;
            }

            void setCallback(void (CALLBACKTYPE::*callbackFunc)(void), CALLBACKTYPE &object) {
                callbackFunc_ = callbackFunc;
                object_ = &object;
                interruptEvent = this;
                pinMode(pin_, INPUT_PULLUP);
                attachInterrupt(digitalPinToInterrupt(pin_), pinInterruptHandler, RISING);
            }

            void trigger() {

                if (callbackFunc_ != nullptr && object_ != nullptr) {
                    (object_->*callbackFunc_)();
                }

            }

        };

    }

}

#endif