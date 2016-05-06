#ifndef MATCH_H_GUARD
#define MATCH_H_GUARD

#include "ServiceMouvement.h"
#include "ServiceIA.h"
#include "AbstractIA.h"


#define ETAT_0_ATTENTE 0
#define ETAT_1_AVANCER 1


#define ETAT_STOP 199999;

#define UN_METRE (15080)

#define DETECTION_ON true
#define DETECTION_OFF false

#define DISTANCE_A (0.05 * UN_METRE)
#define DISTANCE_B (0.7 * UN_METRE)

class Tests : public AbstractIA {

        private :
        int etatCourant;
        bool etatCourantInitialise;
        int dureeEtat;
        void reset();
        float centimeters(float cm);

        public  :
        void init();
        void step();
        bool isFinished();

        Tests(Brain* brain);


};

#endif
