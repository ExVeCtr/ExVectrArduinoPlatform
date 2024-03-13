#include "Arduino.h"

#include "ExVectrCore/print.hpp"
#include "ExVectrArduinoPlatform/pwm_hw.hpp"

namespace VCTR
{

    namespace Platform
    {

        bool PinPWM_HW::channelUsed_[16];
        bool PinPWM_HW::systemInitialised_ = false;
        uint16_t PinPWM_HW::channelRes_[16];

        PinPWM_HW::PinPWM_HW()
        {}

        PinPWM_HW::~PinPWM_HW()
        {
            if (!systemInitialised_)
                return;
        }

        void PinPWM_HW::init(int32_t pin)
        {

            pin_ = pin;
            pinMode(pin_, OUTPUT);

            if (!systemInitialised_) // Initialise PWM HW if not done yet. Set used channel array elements to false.
            {
                systemInitialised_ = true;
                for (size_t i = 0; i < 16; i++)
                {
                    channelUsed_[i] = false;
                    channelRes_[i] = 8;
                }
            }

            // Next search for next available channel.
            size_t channel_ = 0;
            bool found = false;
            for (size_t i = 0; i < 16; i++)
            {
                if (!channelUsed_[i])
                {
                    channel_ = i;
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                channel_ = 15;
                Core::printW("PinPWM_HW: Was unable to find an unused channel at init() for pin: %d. Using channel: %d.\n", pin_, channel_);
            }

            if (found)
            { // Setup this channel.
                ledcSetup(channel_, 500, 8);
                ledcWrite(channel_, 0);
            }

            ledcAttachPin(pin_, channel_);

        }

        int32_t PinPWM_HW::getPin()
        {
            return pin_;
        }

        void PinPWM_HW::setChannel(size_t channel)
        {
            ledcAttachPin(pin_, channel);
        }

        size_t PinPWM_HW::getChannel()
        {
            return channel_;
        }

        void PinPWM_HW::setPinValue(float value)
        {
            ledcWrite(channel_, value * getPinResolution());
        }

        float PinPWM_HW::getPinValue()
        {
            return ledcRead(channel_);
        }

        void PinPWM_HW::setPinFrequency(float value)
        {
            ledcChangeFrequency(channel_, value, 8);
        }

        float PinPWM_HW::getPinFrequency()
        {
            return ledcReadFreq(channel_);
        }

        void PinPWM_HW::setPinResolution(uint32_t value)
        {
            channelRes_[channel_] = value;
            ledcChangeFrequency(channel_, getPinFrequency(), value);
        }

        uint32_t PinPWM_HW::getPinResolution()
        {
            return 1<<channelRes_[channel_];
        }

    }

}