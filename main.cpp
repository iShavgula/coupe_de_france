#include "mbed.h"
#include "RangeFinder.h"
#include <cmath>
#define PI2 (2*M_PI)
#define PI (M_PI)

#define I2C_SDA D14
#define I2C_SCL D15


/**
 * PINS : pwm out D9
 * digital out D2 et D4
 * sensor : PA_1
 */



#define PIN_SONAR_FORWARD PC_6
#define PIN_SONAR_BACKWARD PC_8







// 1 >>>>>
DigitalOut myled(LED1);
PwmOut pwmMotorDroite(PB_15);
DigitalOut dirdroite(D3);
DigitalOut dirdroite2(D5);

AnalogIn currentSenseGauche(PA_3);
// <<<<<<<<



int main() {
        myled = 1;
        wait(0.5);
        myled = 0;
        pwmMotorDroite.period_us(1000);
        dirdroite=1;
        dirdroite2=0;
        pwmMotorDroite.pulsewidth_us(1000);
        wait(1);
        myled = 1;
        wait(3);
        pwmMotorDroite.pulsewidth_us(0);


}
