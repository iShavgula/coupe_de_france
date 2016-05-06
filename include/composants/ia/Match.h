#ifndef MATCH_H_GUARD
#define MATCH_H_GUARD

#include "ServiceMouvement.h"
#include "ServiceIA.h"
#include "AbstractIA.h"

#define ETAT_0_CHATEAU -1
#define ETAT_1_CHATEAU -2
#define ETAT_0_ATTENTE 0
#define ETAT_1_AVANCER 1
#define ETAT_2_GAUCHE_90 2
#define ETAT_3_RECULER 3
#define ETAT_4_POUSSER_PORTE 4
#define ETAT_5_AVANCER 5
#define ETAT_6_DROITE_90 6
#define ETAT_7_AVANCER 7
#define ETAT_8_GAUCHE_90 8
#define ETAT_9_POUSSER_PORTE 9
#define ETAT_10_AVANCER 10

#define ETAT_200_GAUCHE_90 19
#define ETAT_20_AVANCER 20
#define ETAT_22_RECULER 22
#define ETAT_23_GAUCHE_90 23
#define ETAT_24_POUSSER_PORTE 24
#define ETAT_25_AVANCER_UN_PEU 25
#define ETAT_26_DROITE_90 26
#define ETAT_27_RECULER 27
#define ETAT_28_GAUCHE_90 28
#define ETAT_29_GAUCHE_90 29
#define ETAT_211_AVANCER 31
#define ETAT_212_AVANCER_UN_PEU 32
#define ETAT_213_GAUCHE_90 33
#define ETAT_214_AVANCER 34
#define ETAT_215_GAUCHE_45 35
#define ETAT_216_AVANCER_UN_PEU 36
#define ETAT_217_GAUCHE_45 37
#define ETAT_218_AVANCER_UN_PEU 38
#define ETAT_210_GAUCHE_90 39
#define ETAT_STOP 199999;

#define UN_METRE (15080)

#define DETECTION_ON true
#define DETECTION_OFF false

#define DISTANCE_A (0.05 * UN_METRE)
#define DISTANCE_B (0.7 * UN_METRE)

class Match : public AbstractIA {

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

        Match(Brain* brain);


};

#endif
