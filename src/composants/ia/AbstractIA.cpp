#include "AbstractIA.h"
#include "Brain.h"
#include "Sonar.h"
#include "Logger.h"
#include "ExecTimer.h"



AbstractIA::AbstractIA(Brain* brain){
        this->brain = brain;
        heading = NORD;
        initTourner = false;
        sommeDeltaZ = 0;
        compteurMoteurDroite = new Compteur(PB_14);
        compteurMoteurGauche = new Compteur(PB_13);
        finiComportementSimple = false;
        initAvancer = false;
        initReculer = false;
        aDetecteObstacle = false;
}


void AbstractIA::faireDemiTour(float puissance){
        finiComportementSimple = false;
        tournerAngleDroitDroite(puissance);
        tournerAngleDroitDroite(puissance);
}
void AbstractIA::tournerAngleDroitGauche(float puissance){
        finiComportementSimple = false;
        tourner(puissance, -90.0);
        heading = (heading + 3) % 4;
}
void AbstractIA::tournerAngleDroitDroite(float puissance){
        finiComportementSimple = false;
        tourner(puissance, 90.0);
        heading = (heading + 1) % 4;
}

void AbstractIA::tourner(float puissance, float angleInDgr){
        float x, y, z;
        if(!initTourner){

                sommeDeltaZ = 0;
                if(angleInDgr > 0){
                        brain->getServiceMouvement()->tourner(puissance, DROITE);
                }
                else{
                        brain->getServiceMouvement()->tourner(puissance, GAUCHE);
                }
                initTourner = true;
        }

        float angle = fabs(angleInDgr);
        brain->getServiceGyroscope()->read_gyroscope(&x, &y, &z);
        std::ostringstream ss;
        ss << sommeDeltaZ;
        Logger::info("Current angle: " + std::string(ss.str()));


        if(sommeDeltaZ < angle){
                sommeDeltaZ += fabs(z);
        }
        else{
                finiComportementSimple = true;
                sommeDeltaZ = 0;
                initTourner = false;
        }
}

void AbstractIA::avancer(float puissance, bool detection, float pas){
        ExecTimer& timer=ExecTimer::Instance();
        
        bool obstacleDevant =  brain->getServicesSonar()[AVANT]->aDetecteObstacle();

        if(!initAvancer){
                aDetecteObstacle = false;
                finiComportementSimple = false;
                compteurMoteurGauche->reset();
                initAvancer = true;

                timer.reset();

                double prevPowerAdded = 0.02;
                double curPowerSet = 0.2;
                brain->getServiceMouvement()->avancer(curPowerSet);

                while (true) {
                        if (curPowerSet >= MAX_POWER_ALLOWED - 0.01) {
                                break;
                        }

                        wait(0.1);
                        prevPowerAdded *= 1.5;
                        curPowerSet += prevPowerAdded;
                        curPowerSet = curPowerSet < MAX_POWER_ALLOWED ? curPowerSet : MAX_POWER_ALLOWED;
                        brain->getServiceMouvement()->avancer(curPowerSet);
                }
        }
        if(detection){
                Logger::debug("Detection - Avant");
                if(obstacleDevant){
                        Logger::debug("obstacleDevant");
                        aDetecteObstacle = true;
                        brain->getServiceMouvement()->stopper(1.0);
                }else if(aDetecteObstacle){
                        Logger::debug("aDetecteObstacle - Avant");
                        aDetecteObstacle = false;
                        brain->getServiceMouvement()->avancer(MAX_POWER_ALLOWED);
                }
        }

        if(compteurMoteurGauche->read() >= pas || timer.timePassed() > 7){
                Logger::debug("Fin avancer");
                finiComportementSimple = true;
                brain->getServiceMouvement()->stopper(1.0);
                initAvancer = false;
                aDetecteObstacle = false;
        }
}

void AbstractIA::reculer(float puissance, bool detection, float pas){
        ExecTimer& timer=ExecTimer::Instance();
        

        bool obstacleDerriere =  brain->getServicesSonar()[ARRIERE]->aDetecteObstacle();


        if(!initReculer){
                Logger::debug("Init reculer");
                aDetecteObstacle = false;
                finiComportementSimple = false;
                compteurMoteurGauche->reset();
                initReculer = true;

                timer.reset();

                double prevPowerAdded = 0.02;
                double curPowerSet = 0.2;
                brain->getServiceMouvement()->avancer(curPowerSet);

                while (true) {
                        if (curPowerSet >= MAX_POWER_ALLOWED - 0.01) {
                                break;
                        }

                        wait(0.1);
                        prevPowerAdded *= 1.5;
                        curPowerSet += prevPowerAdded;
                        curPowerSet = curPowerSet < MAX_POWER_ALLOWED ? curPowerSet : MAX_POWER_ALLOWED;
                        brain->getServiceMouvement()->reculer(curPowerSet);
                }
        }

        if(detection){
                Logger::debug("Detection - Derriere");

                if(obstacleDerriere){
                        Logger::debug("obstacleDerriere");
                        aDetecteObstacle = true;
                        brain->getServiceMouvement()->stopper(1.0);
                }else if(aDetecteObstacle){
                        Logger::debug("aDetecteObstacle - Derriere");
                        aDetecteObstacle = false;
                        brain->getServiceMouvement()->reculer(MAX_POWER_ALLOWED);
                }
        }

        if(compteurMoteurGauche->read() >= pas || timer.timePassed() > 7){
                Logger::debug("Dernier if - Derriere");
                finiComportementSimple = true;
                brain->getServiceMouvement()->stopper(1.0);
                initReculer = false;
                aDetecteObstacle = false;
        }
}

int AbstractIA::getHeading(){
        return heading;
}

bool AbstractIA::aDetecteObstacleDevant(){
        return brain->getServicesSonar()[0]->aDetecteObstacle();
}


bool AbstractIA::aDetecteObstacleDerriere(){
        return brain->getServicesSonar()[1]->aDetecteObstacle();
}
