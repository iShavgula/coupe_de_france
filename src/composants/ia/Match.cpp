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
        // if (Timer.instance.totalTimePassed() >= 90) {
        //         etatCourant = ETAT_STOP;
        //         reset();
        //         return;
        // }

        dureeEtat++;

        switch (etatCourant) {

                case ETAT_0_CHATEAU :
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                avancer(0.8, DETECTION_OFF, centimeters(72));
                if(finiComportementSimple){
                        etatCourant = ETAT_1_CHATEAU;
                        reset();
                }
                break;
                case ETAT_1_CHATEAU :
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                reculer(0.8, DETECTION_OFF, centimeters(78));
                if(finiComportementSimple){
                        etatCourant = ETAT_1_AVANCER;
                        reset();
                }
                break;

                case ETAT_0_ATTENTE :
                wait(0.1);
                etatCourant = ETAT_1_AVANCER;
                break;

                case ETAT_1_AVANCER :
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                avancer(0.8, DETECTION_OFF, centimeters(18));
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
                reculer(0.8, DETECTION_OFF, centimeters(70));
                if(finiComportementSimple){
                        etatCourant = ETAT_4_POUSSER_PORTE;
                        reset();
                }
                break;
                case ETAT_4_POUSSER_PORTE :
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                reculer(0.8, DETECTION_OFF, centimeters(15));
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
                avancer(0.8, DETECTION_OFF, centimeters(18));
                if(finiComportementSimple){
                        etatCourant = ETAT_6_DROITE_90;
                        reset();
                }
                break;
                case ETAT_6_DROITE_90 :
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                tournerAngleDroitDroite(0.7);
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
                avancer(0.8, DETECTION_OFF, centimeters(24));
                if(finiComportementSimple){
                        etatCourant = ETAT_8_GAUCHE_90;
                        reset();
                }
                break;
                case ETAT_8_GAUCHE_90 :
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                tournerAngleDroitGauche(0.7);
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
                reculer(0.8, DETECTION_OFF, centimeters(23));
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
                avancer(0.8, DETECTION_OFF, centimeters(82));
                if(finiComportementSimple){
                        etatCourant = ETAT_200_GAUCHE_90;
                        reset();
                }
                break;
                case ETAT_200_GAUCHE_90:
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                tourner(0.8, 70);
                if(finiComportementSimple){
                    etatCourant = ETAT_20_AVANCER;
                    reset();
                }
                break;
                case ETAT_20_AVANCER:
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                avancer(0.8,DETECTION_OFF,centimeters(70));
                if(finiComportementSimple){
                    etatCourant = ETAT_28_GAUCHE_90;
                    reset();
                }
                break;
                case ETAT_28_GAUCHE_90:
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                tourner(0.8, -65);
                if(finiComportementSimple){
                    etatCourant = ETAT_25_AVANCER_UN_PEU;
                    reset();
                }
                break;
                case ETAT_25_AVANCER_UN_PEU:
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                avancer(0.8,DETECTION_OFF, centimeters(16));
                if(finiComportementSimple){
                    etatCourant = ETAT_29_GAUCHE_90;
                    reset();
                }
                break;
                case ETAT_29_GAUCHE_90:
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                tournerAngleDroitGauche(0.9);
                if(finiComportementSimple){
                    etatCourant = ETAT_211_AVANCER;
                    reset();
                }
                break;
                case ETAT_211_AVANCER:
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                avancer(0.8,DETECTION_OFF, centimeters(75));
                if(finiComportementSimple){
                    etatCourant = ETAT_210_GAUCHE_90;
                    reset();
                }
                break;
                case ETAT_210_GAUCHE_90:
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                reculer(0.8,DETECTION_OFF, centimeters(75));
                if(finiComportementSimple){
                    etatCourant = ETAT_26_DROITE_90;
                    reset();
                }
                break;
                case ETAT_26_DROITE_90:
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                tournerAngleDroitDroite(0.9);
                if(finiComportementSimple){
                    etatCourant = ETAT_212_AVANCER_UN_PEU;
                    reset();
                }
                break;
                case  ETAT_212_AVANCER_UN_PEU:
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                avancer(0.8,DETECTION_OFF,centimeters(20));
                if(finiComportementSimple){
                    etatCourant = ETAT_213_GAUCHE_90;
                    reset();
                }
                break;
                case ETAT_213_GAUCHE_90:
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                tournerAngleDroitGauche(0.9);
                if(finiComportementSimple){
                    etatCourant = ETAT_214_AVANCER;
                    reset();
                }
                break;
                case ETAT_214_AVANCER:
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                avancer(0.8,DETECTION_OFF,centimeters(62));
                if(finiComportementSimple){
                    etatCourant = ETAT_215_GAUCHE_45;
                    reset();
                }
                break;
                case ETAT_215_GAUCHE_45:
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                tourner(0.8,-25); //45 à gauche en fait
                if(finiComportementSimple) {
                    etatCourant = ETAT_216_AVANCER_UN_PEU;
                    reset();
                }
                break;
                case ETAT_216_AVANCER_UN_PEU:
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                avancer(0.8,DETECTION_OFF,centimeters(40));
                if(finiComportementSimple) {
                    etatCourant = ETAT_STOP;
                    reset();
                }
                break;
                case ETAT_217_GAUCHE_45:
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                tourner(0.8,-30); //45 à gauche en fait
                if(finiComportementSimple){
                    etatCourant = ETAT_218_AVANCER_UN_PEU;
                    reset();
                }
                break;
                case ETAT_218_AVANCER_UN_PEU:
                if(!etatCourantInitialise){
                        etatCourantInitialise = true;
                }
                avancer(0.8, DETECTION_OFF,centimeters(2));
                if(finiComportementSimple){
                    etatCourant = ETAT_STOP;
                    reset();
                }
                break;
        }

}

float Match::centimeters(float cm){
        return (UN_METRE / 100.0) * cm;
}
