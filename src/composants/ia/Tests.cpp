#include "Tests.h"
#include "Brain.h"
#include "Logger.h"

Tests::Tests(Brain * brain) : AbstractIA(brain) {
        this->brain = brain;
}

void Tests::reset(){
        etatCourantInitialise = false;
        brain->getServiceMouvement()->stopper(1.0);
        finiComportementSimple = false;

        dureeEtat = 0;

        wait(0.3);
}

void Tests::init(){
        etatCourant = ETAT_0_ATTENTE;
        reset();
}

bool Tests::isFinished(){
        return etatCourant == ETAT_STOP;
}

void Tests::step(){
        dureeEtat++;

        switch (etatCourant) {
                case ETAT_0_ATTENTE :
                wait(1);
                etatCourant = ETAT_1_AVANCER;
                break;

                case ETAT_1_AVANCER :
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                avancer(0.6, DETECTION_OFF, centimeters(200));
                if(finiComportementSimple){
                        etatCourant = ETAT_STOP;
                        reset();
                }
        }

}

float Tests::centimeters(float cm){
        return (UN_METRE / 100.0) * cm;
}
