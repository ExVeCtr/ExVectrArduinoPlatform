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

    PlatformArduino() : VCTR::Core::Task_Periodic("Platform Arduino Task", 1*VCTR::Core::SECONDS, 0) {

        VCTR::Core::getSystemScheduler().addTask(*this);
        setPriority(1000);

    }


    void taskInit() override {

        Serial.begin(115200);

        printSubM.subscribe(VCTR::Core::getMessageTopic());
        printSubM.setCallbackFunction(printOutM);
        printSubW.subscribe(VCTR::Core::getWarningTopic());
        printSubW.setCallbackFunction(printOutW);
        printSubE.subscribe(VCTR::Core::getErrorTopic());
        printSubE.setCallbackFunction(printOutE);

    }


    void taskThread() override {



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
