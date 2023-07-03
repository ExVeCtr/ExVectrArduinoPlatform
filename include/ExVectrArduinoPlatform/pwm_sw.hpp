#ifndef EXVECTRARDUINOPLATFORM_PWMSW_H
#define EXVECTRARDUINOPLATFORM_PWMSW_H

#include "stdint.h"
#include "stddef.h"

#include "ExVectrCore/task_types.hpp"
#include "ExVectrCore/scheduler2.hpp"
#include "ExVectrHAL/pin_pwm.hpp"

namespace VCTR
{

    namespace Platform
    {

        /**
         * @brief Software implementation of PWM. Timing is worse than hardware but has advantage of switching more than just pin output.
         * @note Must be further implemented by inhereting classes to implement what to turn on/off (outputSwitch() to be implemented). Does not use scheduler. Make a thread that calls update() automatically to use scheduler.
         */
        class PWM_SW
        {
        private:

            float frequency_ = 0;
            float dutycycle_ = 0;
            bool currentVal_ = false;
            int64_t lastSwitch_ = 0;

        public:
            
            /**
             * @brief Updates the output.
             * @return the time for the next update.
             */
            int64_t update();

            /**
             * @brief Virtual class to implement actual changing of what to be pulse-width-modulated.
             * @note Should be fast.
             * @param value Value output should be.
             */
            virtual void outputSwitch(bool value) = 0;

            /**
             * @brief Dutycycle from 0 to 1.
             * @param value 
             */
            void setDutycycle(float value);

            /**
             * @brief Gets the current dutycycle.
             * @return dutycycle from 0 to 1.
             */
            float getDutycycle();

            /**
             * Sets pwm frequency.
             * @param value Which frequency [Hz] to set PWM to.
             */
            void setPinFrequency(float value);

            /**
             * @returns current PWM Frequency.
             */
            float getPinFrequency();

        };

        

        class PWM_SW_Thread: public PWM_SW, public Core::Scheduler::Task
        {
            
            int64_t nextUpdate = 0;

        public:
            
            /**
             * @returns a char array for the name of the task.
             */
            const char *taskName();

            /**
             * Will be called by scheduler ASAP if isInitialised() returns false.
             */
            void taskInit();

            /**
             * To be implemented by application tasks. Will be called by run().
             */
            void taskThread();

        };

    }

}

#endif