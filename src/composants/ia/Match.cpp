#include "Match.h"
#include "Brain.h"
#include "Logger.h"

Match::Match(Brain * brain) : AbstractIA(brain) {
        this->brain = brain;
}

void Match::reset(){
        etatCourantInitialise = false;
        brain->getServiceMouvement()->stopper(1.0);
        finiComportementSimple = false;

        dureeEtat = 0;

        wait(0.3);
}

void Match::init(){
        etatCourant = ETAT_0_CHATEAU;
        reset();
}

bool Match::isFinished(){
        return etatCourant == ETAT_STOP;
}

void Match::step(){
        dureeEtat++;

        switch (etatCourant) {

                case ETAT_0_CHATEAU :
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                avancer(0.8, DETECTION_OFF, centimeters(65));
                if(finiComportementSimple){
                        etatCourant = ETAT_1_CHATEAU;
                        reset();
                }
                break;
                case ETAT_1_CHATEAU :
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                reculer(1.0, DETECTION_OFF, centimeters(69));
                if(finiComportementSimple){
                        etatCourant = ETAT_1_AVANCER;
                        reset();
                }
                break;

                case ETAT_0_ATTENTE :
                wait(1);
                etatCourant = ETAT_1_AVANCER;
                break;

                case ETAT_1_AVANCER :
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                avancer(1.0, DETECTION_ON, centimeters(15));
                if(finiComportementSimple){
                        etatCourant = ETAT_2_GAUCHE_90;
                        reset();
                }
                break;
                case ETAT_2_GAUCHE_90 :
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                tournerAngleDroitGauche(0.7);
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
                        etatCourant = ETAT_5_AVANCER;
                        reset();
                }
                /*have a kit kat*/
                break;
                /*yo*/
                case ETAT_5_AVANCER :
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                avancer(1.0, DETECTION_ON, centimeters(15));
                if(finiComportementSimple){
                        etatCourant = ETAT_6_DROITE_90;
                        reset();
                }
                break;
                case ETAT_6_DROITE_90 :
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                tournerAngleDroitDroite(0.8);
                if(finiComportementSimple){
                        etatCourant = ETAT_7_AVANCER;
                        reset();
                }
                break;

                case ETAT_7_AVANCER :
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                /* TODO DETECTION_OFF ?! */
                avancer(1.0, DETECTION_ON, centimeters(15));
                if(finiComportementSimple){
                        etatCourant = ETAT_8_GAUCHE_90;
                        reset();
                }
                break;
                case ETAT_8_GAUCHE_90 :
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                tournerAngleDroitGauche(0.8);
                if(finiComportementSimple){
                        etatCourant = ETAT_9_POUSSER_PORTE;
                        reset();
                }
                break;
                case ETAT_9_POUSSER_PORTE :
                if(!etatCourantInitialise){
                        Logger::debug("Commence ETAT 9");
                        etatCourantInitialise = true;
                }
                Logger::debug("Avant reculer ETAT 9");
                reculer(1.0, DETECTION_OFF, centimeters(15));
                Logger::debug("Après reculer ETAT 9");
                if(finiComportementSimple){
                        Logger::debug("Fin ETAT 9");
                        etatCourant = ETAT_10_AVANCER;
                        reset();
                }
                break;
                case ETAT_10_AVANCER :
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                avancer(1.0, DETECTION_ON, centimeters(75));
                if(finiComportementSimple){
                        etatCourant = ETAT_STOP;
                        reset();
                }

        }

}

float Match::centimeters(float cm){
        return (UN_METRE / 100.0) * cm;
}
