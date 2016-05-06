#include "AbstractIA.h"
#include "Brain.h"
#include "Sonar.h"
#include "Logger.h"
#include "ExecTimer.h"

#include <time.h>
#include <cmath>

AbstractIA::AbstractIA(Brain* brain){
        this->brain = brain;
        heading = NORD;
        puissance_interne = PUISSANCE_MIN;
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

void AbstractIA::accelerer(float puissance_desiree){
  temps_courant = clock();
  double delta = (double)(temps_courant - temps_precedent) / CLOCKS_PER_SEC ;

  puissance_interne = PUISSANCE_MIN + ((-1 + std::pow((float)2,(float)(5/TEMPS_ACCELERATION)*((float)delta)))/100);

  std::ostringstream ss1;
  ss1 << puissance_interne;
  Logger::info("scaling: " + std::string(ss1.str()));

  if(puissance_interne >= puissance_desiree){
    puissance_interne = puissance_desiree;
    int cpt = compteurMoteurGauche->read();
    std::ostringstream ss2;
    ss2 << cpt;
    Logger::info("FIN SCALING: " + std::string(ss2.str()));
  }
}

void AbstractIA::avancer(float puissance_desiree, bool detection, float pas){

        ExecTimer& timer=ExecTimer::Instance();

        bool obstacleDevant =  brain->getServicesSonar()[AVANT]->aDetecteObstacle();

        if(!initAvancer){
                aDetecteObstacle = false;
                finiComportementSimple = false;
                compteurMoteurGauche->reset();
                initAvancer = true;
                puissance_interne = PUISSANCE_MIN;
                brain->getServiceMouvement()->avancer(puissance_interne);

                temps_precedent = clock();
                timer.reset();
        }


        if(puissance_interne < puissance_desiree){

          accelerer(puissance_desiree);
          brain->getServiceMouvement()->avancer(puissance_interne);
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
                        brain->getServiceMouvement()->avancer(puissance_interne);
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

void AbstractIA::reculer(float puissance_desiree, bool detection, float pas){
        ExecTimer& timer=ExecTimer::Instance();



        bool obstacleDerriere =  brain->getServicesSonar()[ARRIERE]->aDetecteObstacle();


        if(!initReculer){
                Logger::debug("Init reculer");
                aDetecteObstacle = false;
                finiComportementSimple = false;
                compteurMoteurGauche->reset();
                initReculer = true;
                puissance_interne = PUISSANCE_MIN;
                brain->getServiceMouvement()->reculer(puissance_interne);
                temps_precedent = clock();
                            timer.reset();
        }

        if(puissance_interne < puissance_desiree){

          accelerer(puissance_desiree);

          brain->getServiceMouvement()->avancer(puissance_interne);

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
                        brain->getServiceMouvement()->reculer(puissance_interne);

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
