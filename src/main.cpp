#include "mbed.h"

#include "RandomIA.h"
#include "TestBras.h"
#include "Tests.h"
#include "Brain.h"
#include "Moteur.h"
#include "Sonar.h"
#include "Gyroscope.h"
#include "Bras.h"

#include <time.h>


int main(){


        DigitalIn powerSwitch(PB_2);

        powerSwitch.mode(PullUp);
        wait(1);
        while(1){
                if(powerSwitch.read() == 0){
                        break;
                }
        }

        clock_t tStart = clock();



        // Coté :
        // Si celui qu'on utilise d'habitude, 0, sinon 1.
        int cote = 1;


        Brain* brain = new Brain();
        Moteur* moteur = new Moteur(cote);
        Sonar* sonarAvant = new Sonar();
        Sonar* sonarArriere = new Sonar();
        Gyroscope* gyroscope = new Gyroscope();
        Tests* ia = new Tests(brain);
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

        bool attente = brain->start((clock() - tStart) / CLOCKS_PER_SEC);

        PwmOut pwmMoteurParasol(PB_15);
        DigitalOut dirDroiteParasol(D3);
        DigitalOut dirDroite2Parasol(D5);

        pwmMoteurParasol.period_us(1000);
        dirDroiteParasol=1;
        dirDroite2Parasol=0;

        double tempsPris = (double)(clock() - tStart)/CLOCKS_PER_SEC;
        if(attente){
                wait(91 - tempsPris);
        }
        pwmMoteurParasol.pulsewidth_us(400);
        wait(1.2);
        pwmMoteurParasol.pulsewidth_us(0);

        /* Rajouter delete pour les composants  ??? */

        return EXIT_SUCCESS;
}
