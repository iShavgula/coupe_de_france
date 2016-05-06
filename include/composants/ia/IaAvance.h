#ifndef IA_AVANCE_GUARD_H
#define IA_AVANCE_GUARD_H

#include "ServiceMouvement.h"
#include "ServiceIA.h"
#include "AbstractIA.h"

#define UN_METRE (15080)

#define ETAT_0_ATTENTE 0
#define ETAT_1_AVANCER 1
#define ETAT_STOP 1L << 5

class IaAvance : public AbstractIA {

        private :
        int etatCourant;
        bool etatCourantInitialise;
        int dureeEtat;
        void reset();

        public  :
        void init();
        void step();
        bool isFinished();

        IaAvance(Brain* brain);
};

#endif
