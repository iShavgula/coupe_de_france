#include "Homo.h"
#include "Brain.h"
#include "Logger.h"

Homo::Homo(Brain * brain) : AbstractIA(brain) {
        this->brain = brain;
}

void Homo::reset(){
        etatCourantInitialise = false;
        brain->getServiceMouvement()->stopper(1.0);
        finiComportementSimple = false;

        dureeEtat = 0;

        wait(0.3);
}

void Homo::init(){
        etatCourant = ETAT_0_ATTENTE;
        reset();
}

bool Homo::isFinished(){
        return etatCourant == ETAT_STOP;
}

void Homo::step(){
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
                avancer(1.0, DETECTION_ON, DISTANCE_A);
                if(finiComportementSimple){
                        etatCourant = ETAT_2_GAUCHE_90;
                        reset();
                }
                break;
                case ETAT_2_GAUCHE_90 :
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                tournerAngleDroitGauche(0.8);
                if(finiComportementSimple){
                        etatCourant = ETAT_3_RECULER;
                        reset();
                }
                break;

                case ETAT_3_RECULER :
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                reculer(1.0, DETECTION_ON, DISTANCE_B - centimeters(15));
                if(finiComportementSimple){
                        etatCourant = ETAT_4_POUSSER_PORTE;
                        reset();
                }
                break;
                case ETAT_4_POUSSER_PORTE :
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                reculer(1.0, DETECTION_OFF, centimeters(15));
                if(finiComportementSimple){
                        etatCourant = ETAT_STOP;
                        reset();
                }
                break;


        }

}

long Homo::centimeters(float cm){
        return (UN_METRE / 100) * cm;
}
