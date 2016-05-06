#include "Brain.h"
#include "ExecTimer.h"

#include <string>
#include <sstream>

void Brain::init(){
        this->tempsPasse = 0;

        std::srand(std::time(0));

        pasCourant = 0;

}

void Brain::init(int tempsPasse){

        this->tempsPasse = tempsPasse;
        std::srand(std::time(0));

        pasCourant = 0;

}

bool Brain::start(){
        Logger::info("start");
        ExecTimer& timer=ExecTimer::Instance();
        while(!serviceIA->isFinished()){
                if(timer.totalTimePassed() >= 90){
                        return false;
                }
                serviceIA->step();
                pasCourant++;
        }
        return true;


}

void Brain::bindService(ServiceMouvement* serviceMouvement){
        this->serviceMouvement = serviceMouvement;
}

void Brain::bindService(ServiceSonar* serviceSonar){
        servicesSonar.push_back(serviceSonar);
}

void Brain::bindService(ServiceGyroscope * serviceGyroscope) {
        this->serviceGyroscope = serviceGyroscope;
}

void Brain::bindService(ServiceIA * serviceIA) {
        this->serviceIA = serviceIA;
}


ServiceMouvement* Brain::getServiceMouvement() {
        return this->serviceMouvement;
}

ServiceSonar* Brain::getServiceSonar() {
        return this->servicesSonar[0];
}

ServiceGyroscope* Brain::getServiceGyroscope() {
        return this->serviceGyroscope;
}

ServiceIA* Brain::getServiceIA() {
        return this->serviceIA;
}

void Brain::bindService(ServiceBras * serviceBras) {
        this->serviceBras = serviceBras;
}

ServiceBras* Brain::getServiceBras() {
        return serviceBras;
}

int Brain::getPasCourant() {
        return pasCourant;
}

std::vector<ServiceSonar*> Brain::getServicesSonar(){
        return servicesSonar;
}
