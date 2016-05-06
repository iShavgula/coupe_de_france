#include "mbed.h"

#include "RandomIA.h"
#include "TestBras.h"
#include "Match.h"
#include "Brain.h"
#include "Moteur.h"
#include "Sonar.h"
#include "Gyroscope.h"
#include "Bras.h"
#include "ExecTimer.h"

#include <time.h>

#define DROITE 0
#define GAUCHE 1

int main(){
        DigitalIn powerSwitch(PB_2);

        powerSwitch.mode(PullUp);
        wait(1);
        while(1){
                if(powerSwitch.read() == 0){
                        break;
                }
        }

        ExecTimer& timer=ExecTimer::Instance();
        timer.resetStart();
        timer.reset();

        // Coté :
        // Si celui qu'on utilise d'habitude, 0, sinon 1.
        int cote = GAUCHE;


        Brain* brain = new Brain();
        Moteur* moteur = new Moteur(cote);
        Sonar* sonarAvant = new Sonar();
        Sonar* sonarArriere = new Sonar();
        Gyroscope* gyroscope = new Gyroscope();
        Match* ia = new Match(brain);
        /* Initialisations */
        brain->init();
        moteur->init();
        sonarAvant->init(AVANT);
        sonarArriere->init(ARRIERE);
        gyroscope->init();
        //bras->int();

        /* Bindings */
        brain->bindService(moteur);
        brain->bindService(sonarAvant);
        brain->bindService(sonarArriere);
        brain->bindService(gyroscope);
        brain->bindService(ia);
        /* Lancement du brain */

        ia->init();

        bool attente = brain->start();

        PwmOut pwmMoteurParasol(PB_15);
        DigitalOut dirDroiteParasol(D3);
        DigitalOut dirDroite2Parasol(D5);

        pwmMoteurParasol.period_us(1000);
        dirDroiteParasol=1;
        dirDroite2Parasol=0;

        double tempsPris = timer.totalTimePassed();
        int timeToWait = tempsPris >= 91 ? 0 : 91 - tempsPris;
        wait(timeToWait);
        pwmMoteurParasol.pulsewidth_us(400);
        wait(1.2);
        pwmMoteurParasol.pulsewidth_us(0);

        /* Rajouter delete pour les composants  ??? */

        return EXIT_SUCCESS;
}
