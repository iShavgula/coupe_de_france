#include "Sonar.h"
#include "RangeFinder.h"
#include "Logger.h"

#include <string>
#include <sstream>


void Sonar::init(){
    init(AVANT);
}

/* TODO: vérifier / ajuster les valeurs en dur ici */
void Sonar::init(int position){
        if(position == AVANT){
                this->rangeFinder = new RangeFinder(PC_6, 10, 5800.0, 100000);
        }
        else if(position == ARRIERE){
                this->rangeFinder = new RangeFinder(PC_8, 10, 5800.0, 100000);
        }
}

bool Sonar::aDetecteObstacle(){
        std::ostringstream ss;

    // -1.0 -> rien n'a été détécté par le sonar
    for(int i = 0; i < 5; ++i){
            double d = distanceObstacle();


            if(d > 0.001 && d < 0.10){
                    ss << d;
                    Logger::info(" Detection: " + std::string(ss.str()));

                    return true;
            }
    }
    return false;
}

double Sonar::distanceObstacle(){
    return this->rangeFinder->read_m();
}
