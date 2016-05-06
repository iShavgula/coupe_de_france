#include "IaAvance.h"
#include "Brain.h"

IaAvance::IaAvance(Brain * brain) : AbstractIA(brain){
        this->brain = brain;
}

void IaAvance::reset(){
        etatCourantInitialise = false;
        brain->getServiceMouvement()->stopper(1.0);
        finiComportementSimple = false;

        dureeEtat = 0;

        wait(0.3);

}

void IaAvance::init(){
        etatCourant = ETAT_0_ATTENTE;
        reset();
}

bool IaAvance::isFinished(){
        return (etatCourant == ETAT_STOP);
}

void IaAvance::step(){
        dureeEtat++;

        switch (etatCourant) {
                case ETAT_0_ATTENTE :
                wait(3);
                etatCourant = ETAT_1_AVANCER;
                break;

                case ETAT_1_AVANCER :
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                avancer(1.0, true, UN_METRE * 10);

                break;
        }
}
