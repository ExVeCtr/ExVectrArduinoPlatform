#ifndef PATHTOHEADERFILE_HEADERNAME_H 
#define PATHTOHEADERFILE_HEADERNAME_H

#include "stdint.h"

namespace VCTR
{

    /**
     * @brief Remember to add documentation to all functions. This one returns the current system time in seconds.
     * @note Will overflow after ~292.47 years. If a deployed system runs longer then that and crashes, then give my great great grandchildren a call.
     *  
     * @returns time since system start in seconds.
     */
    extern float yourSpecialFunctionDefined();

    /**
     * A super duper class than has no actual use other than containing a super duper function to test.
    */
    class SomeSuperDuperClass {
        public:

        /**
         * @brief A super duper function to greet the user.
         * @param systemTime The current system time in seconds since start.
         * 
         * @returns a cool string to greet the user.
        */
        const char* aSuperDuperFunction(float systemTime);

    };

}

#endif