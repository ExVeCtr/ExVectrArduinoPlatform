#include "ExVectrCore/print.hpp"
#include "ExVectrCore/time_definitions.hpp"
#include "ExVectrArduinoPlatform/pwm_sw.hpp"

namespace VCTR
{

    namespace Platform
    {

        int64_t PWM_SW::update()
        {

            int64_t interval = Core::NANOSECONDS / frequency_;

            if (currentVal_)
            {

                if (Core::NOW() - lastSwitch_ >= interval * dutycycle_)
                {
                    outputSwitch(false);
                    currentVal_ = false;
                    // lastSwitch_ = Core::NOW() - Core::NOW() % interval;
                }

                return Core::NOW() - Core::NOW() % interval + interval;
            }
            else
            {

                if (Core::NOW() - lastSwitch_ >= interval)
                {
                    outputSwitch(true);
                    currentVal_ = true;
                    lastSwitch_ = Core::NOW() - Core::NOW() % interval;
                }

                return Core::NOW() - Core::NOW() % interval + interval * dutycycle_;
            }
        }

        void PWM_SW::setDutycycle(float value)
        {
            dutycycle_ = value;
        }

        float PWM_SW::getDutycycle()
        {
            return dutycycle_;
        }

        void PWM_SW::setPinFrequency(float value)
        {
            frequency_ = value;
        }

        float PWM_SW::getPinFrequency()
        {
            return frequency_;
        }

        /// ############ Below are implementations for PWM_SW_Thread ##################

        const char *PWM_SW_Thread::taskName()
        {
            return "PWM_SW_Thread";
        }

        /**
         * Will be called by scheduler ASAP if isInitialised() returns false.
         */
        void PWM_SW_Thread::taskInit()
        {
        }

        /**
         * To be implemented by application tasks. Will be called by run().
         */
        void PWM_SW_Thread::taskThread()
        {
            int64_t next = update();

            setRelease(next);
            setDeadline(next);
        }

    }

}