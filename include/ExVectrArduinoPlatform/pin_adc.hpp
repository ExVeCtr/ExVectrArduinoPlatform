#ifndef EXVECTRARDUINOPLATFORM_PINADC_H
#define EXVECTRARDUINOPLATFORM_PINADC_H

#include "stdint.h"

#include "ExVectrHAL/pin_adc.hpp"

namespace VCTR
{

    namespace Platform
    {

        /**
         * @brief Arduino implementation of ADC.
         */
        class PinADC final : public VCTR::HAL::PinADC
        {
        private:
            uint32_t res_ = 10;

        public:
            PinADC(int32_t pin);

            /**
             * Initialises ADC input.
             */
            void init() override;

            /**
             * @returns current pin input.
             */
            int32_t getPinValue() override;

            /**
             * Sets pin resolution.
             * @param value Which resolution the ADC will use.
             */
            void setPinResolution(uint32_t value) override;

            /**
             * @returns current adc resolution.
             */
            uint32_t getPinResolution() override;
        };

    }

}

#endif