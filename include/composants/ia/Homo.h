#ifndef HOMO_H_GUARD
#define HOMO_H_GUARD

#include "ServiceMouvement.h"
#include "ServiceIA.h"
#include "AbstractIA.h"

#define ETAT_0_ATTENTE 0
#define ETAT_1_AVANCER 1
#define ETAT_2_GAUCHE_90 2
#define ETAT_3_RECULER 3
#define ETAT_4_POUSSER_PORTE 4

#define ETAT_STOP 199999;

#define UN_METRE (15080)

#define DETECTION_ON true
#define DETECTION_OFF false

#define DISTANCE_A (0.05 * UN_METRE)
#define DISTANCE_B (0.7 * UN_METRE)

class Homo : public AbstractIA {

        private :
        int etatCourant;
        bool etatCourantInitialise;
        int dureeEtat;
        void reset();
        long centimeters(float cm);

        public  :
        void init();
        void step();
        bool isFinished();

        Homo(Brain* brain);


};

#endif
