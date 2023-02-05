#ifndef EXVECTRARDUINOPLATFORM_BUSSPI_H
#define EXVECTRARDUINOPLATFORM_BUSSPI_H

#include "SPI.h"
#include "stdint.h"

#include "ExVectrHAL/pin_gpio.hpp"
#include "ExVectrHAL/io.hpp"


namespace VCTR
{

namespace Platform
{
    	
    /**
     * @brief   Implementation of the SPI bus. Uses IO as interface.
    */
    class BusSPIDevice final: public VCTR::HAL::IO
    {
    private:

        SPIClass& bus_;
        VCTR::HAL::PinGPIO& pin_;
        SPISettings spiSettings_;
        bool pinInvert_ = false;

        //Command to read data from device. Temporary, not sure if for all systems correct.
        uint8_t readCommand_ = 0x80;

        //Command to write data to device. Temporary, not sure if for all systems correct.
        uint8_t writeCommand_ = 0x00;

    public:

        BusSPIDevice(SPIClass& bus, const SPISettings& spiSettings, VCTR::HAL::PinGPIO& pin, bool invertSelectPin);

        /**
         * @returns number of bytes that can be written. -1 means no limit to data size.
        */
        int32_t writable() override;

        /**
         * @brief Writes the data from data pointer.
         * @param data Pointer to data.
         * @param bytes Number of bytes to output.
         * 
         * @return number of bytes actually written.
        */
        size_t writeData(const void* data, size_t size) override;

        /**
         * @returns the number of bytes available to read. Or 1 or 0 for boolean.
        */
        size_t readable() override;

        /**
         * @brief Reads the data and places it into the given data pointer.
         * @param data Pointer to where to place read data.
         * @param bytes Number of bytes to read. Will be limited to this number.
         * 
         * @return number of bytes actually read and placed into data pointer.
        */
        size_t readData(void* data, size_t size) override;

        /**
         * @brief writes bytes then reads bytes to IO.
         * @param writeBuf Pointer to data to write.
         * @param readBuf Pointer to data to read to.
         * @param writeSize Number of bytes to write.
         * @param readSize Number of bytes to read.
         * 
         * @return true if writing and reading was successfull.
        */
        bool writeRead(const void* writeBuf, void* readBuf, size_t writeSize, size_t readSize) override;

    };

    
}

}

#endif