#ifndef EXVECTRARDUINOPLATFORM_PINTOUCH_H
#define EXVECTRARDUINOPLATFORM_PINTOUCH_H

#include "stdint.h"

#include "ExVectrHAL/analog_input.hpp"

namespace VCTR
{

    namespace Platform
    {

        /**
         * @brief Arduino implementation of esp32 touch input
         */
        class PinTouch final : public VCTR::HAL::AnalogInput
        {
        private:
            int pin_ = -1;
            

        public:

            /**
             * @brief Initializes the touch input.
             * @param pin The pin to use.
             */
            void init(int32_t pin);

            /**
             * @brief Gets the type of input this is.
             * @return IO_TYPE_t enum.
             */
            HAL::IO_TYPE_t getInputType() const override;

            /**
             * @brief Changes given parameter. 
             * @param param What parameter to change.
             * @param value What to change parameter to.
             * @return True if successfull and parameter is supported.
             */
            bool setInputParam(HAL::IO_PARAM_t param, int32_t value) override;

            /**
             * @returns the number of values available to read at the moment.
            */
            size_t readable() override;

            /**
             * @brief Reads the data and places it into the given data pointer.
             * @param value Pointer to where to place read data.
             * @param size Max number of values to place into value buffer.
             * 
             * @return number of values actually read and placed into data pointer.
            */
            size_t readValue(float* values, size_t size) override;

        };

    }

}

#endif