#ifndef EXVECTRARDUINOPLATFORM_BUSI2C_H
#define EXVECTRARDUINOPLATFORM_BUSI2C_H

#include "stdint.h"
#include "Wire.h"

#include "ExVectrHAL/io.hpp"


namespace VCTR
{

namespace Platform
{
    	
    /**
     * @brief   Implementation of the I2C bus. Uses IOAddress as interface.
    */
    class BusI2CDevice final: public VCTR::HAL::IO
    {
    private:

        TwoWire& bus_;
        uint32_t address_ = 0;

    public:
        
        BusI2CDevice(TwoWire& bus, uint32_t address);

        /**
         * @returns number of bytes that can be written. -1 means no limit to data size.
        */
        int32_t writable() override;

        /**
         * @brief Writes the data from data pointer.
         * @param data Pointer to data.
         * @param bytes Number of bytes to output.
         * @param endTransfer Set to false if doing mulitple writes. Last write should have endTransfer set to true.
         * 
         * @return number of bytes actually written.
        */
        size_t writeData(const void* data, size_t size, bool endTransfer = true) override;

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
        size_t readData(void* data, size_t size, bool endTransfer = true) override;

    };

    
}

}

#endif