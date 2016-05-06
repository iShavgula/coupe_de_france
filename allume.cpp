#include "mbed.h"
#include "RangeFinder.h"
#include <cmath>
#define PI2 (2*M_PI)
#define PI (M_PI)

#define I2C_SDA D14
#define I2C_SCL D15

double initHeading;
double heading,x,y,z,xb,yb,zb,xP,yP,zP,alpha,theta,xPP,yPP,zPP,phi,xZ,yZ,zZ,xPZ,yPZ,zPZ,d;
int16_t data[3];

class Counter {
public:
        Counter(PinName pin) : _interrupt(pin) {        // create the InterruptIn on the pin specified to Counter
                _interrupt.rise(this, &Counter::increment); // attach increment function of this counter instance
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


#define PIN_SONAR_FORWARD PC_6
#define PIN_SONAR_BACKWARD PC_8

int TURNLEFT=0;
int TURNRIGHT=1;
int FORWARD=2;
int BACKWARD=3;

int IDLE=4;
int FOLLOW=5;






// 1 >>>>>
DigitalOut myled(LED1);
PwmOut pwmMotorDroite(D9);
DigitalOut dirdroite(D2);
DigitalOut dirdroite2(D4);
PwmOut pwmMotorGauche(D10);
DigitalOut dirgauche(D7);
DigitalOut dirgauche2(D8);

AnalogIn currentSenseDroite(PA_0);
AnalogIn currentSenseGauche(PA_1);
// <<<<<<<<



Counter counterDroite(PB_14);
Counter counterGauche(PB_13);

DigitalIn powerSwitch(PB_2);

PwmOut brasGauche(PA_11);
PwmOut pelle(PA_15);



// Seeed ultrasound range finder
RangeFinder sonarForward(PIN_SONAR_FORWARD, 10, 5800.0, 100000);
RangeFinder sonarBackward(PIN_SONAR_BACKWARD, 10, 5800.0, 100000);

float FORWARD_DISTANCE_DETECTION = 0.005;
float n=0;
float i=0;
int state=IDLE;
int idleStep=0;
int inert=0;


int main() {
        myled = 0;

}
