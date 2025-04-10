#ifndef EXVECTRARDUINOPLATFORM_MEMORYEEPROM_HPP
#define EXVECTRARDUINOPLATFORM_MEMORYEEPROM_HPP

#include "Arduino.h"
#include "EEPROM.h"



#include "ExVectrData/memory_interface.hpp"


namespace VCTR
{

    namespace Data
    {

        /**
         * @brief   An implementation of the EEPROM memory interface. This memory is used to store data in the EEPROM of the Arduino.
         */
        class Memory_ArduinoEEPROM : public Memory_Interface
        {
        private:

            EEPROMClass* eepromPtr_; ///< Pointer to the EEPROM class. This is used to access the EEPROM memory.

            size_t size_; ///< Size of the EEPROM memory. This is used to check if the memory is out of bounds.

        public:

            Memory_ArduinoEEPROM(EEPROMClass& eepromPtr, size_t size) : eepromPtr_(&eepromPtr), size_(size) {
                // Constructor to initialize the EEPROM memory.
            }

            /**
             * @brief Reads data from the memory.
             * @param bufferPtr Pointer to the buffer where the data will be written to.
             * @param numBytes Number of bytes to be read.
             * @param index Index from where the data will be read from the memory
             * @param bufferIndex Index to where the data will be written in the buffer.
             * @return Number of bytes read from the memory and placed into the buffer.
             */
            size_t readMem(uint8_t* bufferPtr, size_t numBytes, size_t index, size_t bufferIndex = 0) override {
                if (index + numBytes > size_) numBytes = size_ - index; // Out of bounds.
                if (bufferIndex + numBytes > size_) numBytes = size_ - bufferIndex; // Out of bounds.
                
                for (size_t i = 0; i < numBytes; i++) {
                    bufferPtr[bufferIndex + i] = eepromPtr_->read(index + i); // Read the data from the EEPROM to the buffer.
                }

                return numBytes;
            }
            
            /**
             * @brief Writes data to the memory.
             * @param bufferPtr Pointer to the buffer where the data will be read from.
             * @param numBytes Number of bytes to be written.
             * @param index Index to where the data will be written to the memory.
             * @param bufferIndex Index from where the data will be read in the buffer.
             * @return Number of bytes written to the memory from the buffer.
             */
            size_t writeMem(uint8_t const* bufferPtr, size_t numBytes, size_t index, size_t bufferIndex = 0) override {
                if (index + numBytes > size_) numBytes = size_ - index; // Out of bounds.
                if (bufferIndex + numBytes > size_) numBytes = size_ - bufferIndex; // Out of bounds.
                
                for (size_t i = 0; i < numBytes; i++) {
                    eepromPtr_->write(index + i, bufferPtr[bufferIndex + i]); // Write the data from the buffer to the EEPROM.
                }

                return numBytes;
            }

            /**
             * @brief Transfers data from given memory to this memory.
             * @param memory Memory to receive data from.
             * @param numBytes Number of bytes to be transferred.
             * @param toIndex Index to where the data will be written to this memory.
             * @param fromIndex Index from where the data will be read in the given memory.
             * @return Number of bytes written to this memory from the given memory.
             */
            size_t transferFrom(Memory_Interface& memory, size_t numBytes = SIZE_MAX, size_t toIndex = 0, size_t fromIndex = 0) override {
                if (toIndex + numBytes > size_) numBytes = size_ - toIndex; // Out of bounds.
                if (fromIndex + numBytes > memory.size()) numBytes = memory.size() - fromIndex; // Out of bounds.
                
                uint8_t bufferMem[numBytes];
                size_t bytesRead = memory.readMem(bufferMem, numBytes, fromIndex, 0); // Read the data from the given memory to this memory.

                uint8_t bufferEEPROM[numBytes];
                readMem(bufferEEPROM, numBytes, toIndex, 0); // Read the data from the EEPROM to the buffer.
                
                //We only write changes to the EEPROM.
                for (size_t i = 0; i < numBytes; i++) {
                    if (bufferMem[i] != bufferEEPROM[i]) {
                        eepromPtr_->write(toIndex + i, bufferMem[i]); // Write the data from the buffer to the EEPROM.
                    }
                }

                return bytesRead;
            }

            /**
             * @returns the length of the memory in bytes.
             */
            size_t size() override {
                return size_; // Return the size of the memory.
            }
            

        };

    }

}
















#endif