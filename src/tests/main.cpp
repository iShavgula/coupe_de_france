#include "mbed.h"

class Compteur {
public:
        Compteur(PinName pin) : _interrupt(pin) {
                _interrupt.rise(this, &Compteur::increment);
        }
        void increment() {
                _count++;
        }
        int read() {
                return _count;
        }
        void reset() {
                _count=0;
        }
private:
        InterruptIn _interrupt;
        volatile int _count;
};


int main(int argc, char const *argv[]) {

        wait(3);

        Compteur counterGauche(PB_13);
        Compteur counterDroite(PB_14);

        PwmOut pwmMotorDroite(D9);
        DigitalOut dirdroite(D2);
        DigitalOut dirdroite2(D4);
        PwmOut pwmMotorGauche(D10);
        DigitalOut dirgauche(D7);
        DigitalOut dirgauche2(D8);


        pwmMotorGauche.period_us(1000);
        pwmMotorDroite.period_us(1000);
        dirgauche=0;
        dirdroite=1;
        dirgauche2=1;
        dirdroite2=0;

        pwmMotorGauche.pulsewidth_us(00);
        pwmMotorDroite.pulsewidth_us(00);

        pwmMotorGauche.pulsewidth_us(800);
        pwmMotorDroite.pulsewidth_us(800);
        int i=0;

        double NB_STEPS = 15080;

        while(1){
                if (i>1) break;
                if (counterGauche.read() >=NB_STEPS || counterDroite.read() >=NB_STEPS) {
                        counterGauche.reset();
                        counterDroite.reset();
                        i++;
                }
        }
        pwmMotorGauche.pulsewidth_us(00);
        pwmMotorDroite.pulsewidth_us(00);
        counterGauche.reset();
        counterDroite.reset();

        dirgauche=0;
        dirgauche2=0;
        dirdroite=0;
        dirdroite2=0;
        pwmMotorGauche.pulsewidth_us(1000);
        pwmMotorDroite.pulsewidth_us(1000);


        return 0;
}
