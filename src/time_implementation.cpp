#include "Arduino.h"

#include "ExVectrCore/time_definitions.hpp"
#include "ExVectrCore/clock_source.hpp"
#include "ExVectrCore/time_base.hpp" 


class PlatformClock : public VCTR::Core::Clock_Source {
public:

    const VCTR::Core::Timestamped<int64_t>& getCounter() const override {

        static int32_t g_lastMicroseconds = 0;
        static int64_t g_currentTime = 0;
        static bool lock = false; //Needed due to interrupts to make "thread safe" and protect data.
        static VCTR::Core::Timestamped<int64_t> timeStamped;

        int32_t time = micros();

        if (lock) { //Function is currently being used by another process, get new time but dont update values. This could lead to problems if the function is somehow always locked and micros() overflows during that time. Very unlikely lol...
            timeStamped.data = timeStamped.timestamp = g_currentTime + int64_t(time - g_lastMicroseconds)*VCTR::Core::MICROSECONDS;
            return timeStamped;
        }

        lock = true; //Block other processes.
        if (time != g_lastMicroseconds) {
            g_currentTime += int64_t(time - g_lastMicroseconds)*VCTR::Core::MICROSECONDS;
            g_lastMicroseconds = time;
        }
        lock = false; //Release for other processes.

        timeStamped.data = timeStamped.timestamp = g_currentTime;

        return timeStamped;

    }

};


const VCTR::Core::Clock_Source& VCTR::Core::getPlatformClock() {

    static PlatformClock clockSource;

    return clockSource;

}


