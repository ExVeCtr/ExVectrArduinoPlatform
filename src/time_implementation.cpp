#include "Arduino.h"

#include "ExVectrCore/time_base.hpp" 
#include "ExVectrCore/time_definitions.hpp"


int64_t VCTR::timeBase() {

    static int32_t g_lastMicroseconds = 0;
    static int64_t g_currentTime = 0;
    static bool lock = false; //Needed due to interrupts to make "thread safe" and protect data.

    int32_t time = micros();

    if (lock) { //Function is currently being used by another process, get new time but dont update values. This could lead to problems if the function is somehow always locked and micros() overflows during that time. Very unlikely lol...
        return g_currentTime + int64_t(time - g_lastMicroseconds)*VCTR::MICROSECONDS;
    }

    lock = true; //Block other processes.
    if (time != g_lastMicroseconds) {
        g_currentTime += int64_t(time - g_lastMicroseconds)*VCTR::MICROSECONDS;
        g_lastMicroseconds = time;
    }
    lock = false; //Release for other processes.

    return g_currentTime;

}


