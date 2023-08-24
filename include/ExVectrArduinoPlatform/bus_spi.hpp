#ifndef EXVECTRARDUINOPLATFORM_BUSSPI_H
#define EXVECTRARDUINOPLATFORM_BUSSPI_H

#include "SPI.h"
#include "stdint.h"

#include "ExVectrHAL/pin_gpio.hpp"
#include "ExVectrHAL/io_types.hpp"
#include "ExVectrHAL/digital_io.hpp"

namespace VCTR
{

    namespace Platform
    {

        /**
         * @brief   Implementation of the SPI bus. Uses IO as interface.
         */
        class BusSPIDevice final : public VCTR::HAL::DigitalIO
        {
        private:
            SPIClass &bus_;
            VCTR::HAL::PinGPIO &pin_;
            SPISettings spiSettings_;
            bool pinInvert_ = false;

            size_t speed_ = 100000;
            bool msbFirst_ = false;
            uint8_t spiMode_ = 0;

            ///If we are currently in a transaction.
            bool inTransaction_ = false;

        public:
            BusSPIDevice(SPIClass &bus, VCTR::HAL::PinGPIO &pin, bool invertSelectPin);

            /**
             * @brief Gets the type of bus this is.
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
             * @brief Gets the type of bus this is.
             * @return IO_TYPE_t enum.
             */
            HAL::IO_TYPE_t getOutputType() const override;

            /**
             * @brief Changes given parameter. 
             * @param param What parameter to change.
             * @param value What to change parameter to.
             * @return True if successfull and parameter is supported.
             */
            bool setOutputParam(HAL::IO_PARAM_t param, int32_t value) override;

            /**
             * @returns number of bytes that can be written.
             */
            size_t writable() override;

            /**
             * @brief Writes the data from data pointer.
             * @param data Pointer to data.
             * @param bytes Number of bytes to output.
             * @param endTransfer Set to false if doing mulitple writes. Last write should have endTransfer set to true.
             *
             * @return number of bytes actually written.
             */
            size_t writeData(const void *data, size_t size, bool endTransfer = true) override;

            /**
             * @returns the number of bytes available to read.
             */
            size_t readable() override;

            /**
             * @brief Reads the data and places it into the given data pointer.
             * @param data Pointer to where to place read data.
             * @param bytes Number of bytes to read. Will be limited to this number.
             * @param endTransfer Set to false if doing mulitple reads. Last read should have endTransfer set to true.
             *
             * @return number of bytes actually read and placed into data pointer.
             */
            size_t readData(void *data, size_t size, bool endTransfer = true) override;

            /**
             * @brief writes bytes then reads bytes to IO.
             * @param writeBuf Pointer to data to write.
             * @param readBuf Pointer to data to read to.
             * @param writeSize Number of bytes to write.
             * @param readSize Number of bytes to read.
             * @param endTransfer Frees the IO for other devices. Set to false for higher read write speed. Last call should end the transfer!
             *
             * @return true if writing and reading was successfull.
             */
            bool writeRead(const void *writeBuf, void *readBuf, size_t writeSize, size_t readSize, bool endTransfer = true);
        };

    }

}

#endif