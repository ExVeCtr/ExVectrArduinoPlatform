#include "Arduino.h"

#include "ExVectrCore.hpp"

#include "ExVectrCore/print.hpp"
#include "ExVectrCore/topic_subscribers.hpp"
#include "ExVectrCore/task_types.hpp"
#include "ExVectrCore/scheduler2.hpp"


void printOutE(const char* const &item) {

    Serial.print("!!!ERROR: ");
    Serial.print(item);

};

void printOutW(const char* const &item) {

    Serial.print("!WARNING: ");
    Serial.print(item);

};

void printOutD(const char* const &item) {

    Serial.print("Debug: ");
    Serial.print(item);

};

void printOutM(const char* const &item) {

    Serial.print(item);

};


/**
 * Does platform specific stuff like setting up the print output.
*/
class PlatformArduino : public VCTR::Core::Task_Periodic {
public:

    VCTR::Core::StaticCallback_Subscriber<const char*> printSubE;
    VCTR::Core::StaticCallback_Subscriber<const char*> printSubW;
    VCTR::Core::StaticCallback_Subscriber<const char*> printSubM;
    VCTR::Core::StaticCallback_Subscriber<const char*> printSubD;

    PlatformArduino() : VCTR::Core::Task_Periodic("Platform Arduino Task", 1*VCTR::Core::SECONDS, 0) {

        VCTR::Core::getSystemScheduler().addTask(*this);
        setPriority(10);

    }


    void taskInit() override {

        Serial.begin(115200);

#ifndef EXVECTR_ARDUINO_NO_SERIAL_CONSOLE
        // Console text on USB Serial. Define EXVECTR_ARDUINO_NO_SERIAL_CONSOLE (build flag) when Serial carries a
        // binary protocol: the print topics then have no platform subscriber and the application routes them.
        printSubM.subscribe(VCTR::Core::getMessageTopic());
        printSubM.setCallbackFunction(printOutM);
        printSubD.subscribe(VCTR::Core::getDebugTopic());
        printSubD.setCallbackFunction(printOutD);
        printSubW.subscribe(VCTR::Core::getWarningTopic());
        printSubW.setCallbackFunction(printOutW);
        printSubE.subscribe(VCTR::Core::getErrorTopic());
        printSubE.setCallbackFunction(printOutE);
#endif

        setRelease(VCTR::Core::END_OF_TIME);

    }


    void taskThread() override {

        setRelease(VCTR::Core::END_OF_TIME);

    }

};


void VCTR::Core::initialise() {

    VCTR::Core::printM("Beginning platform initialisation...\n");

    //Create platform task.
    static PlatformArduino platformArduino;

    //Initialise
    platformArduino.taskInit();

    VCTR::Core::printM("Platform initialised!\n");

}
