#include "Brain.h"
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

bool Brain::start(int tempsPasse){
        Logger::info("start");
        double tStart = clock();
        int tempsPris;
        while(!serviceIA->isFinished()){
                tempsPris = (double)(clock() - tStart)/CLOCKS_PER_SEC + tempsPasse;
                if(tempsPris >= 91){
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
