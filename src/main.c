#include <Arduino.h>
#include "BDCdrv.h"

void setup() 
{

    CLKPR &= (~(1<<CLKPS0)) & (~(1<<CLKPS1)) & (~(1<<CLKPS2)) & (~(1<<CLKPS3)); // CLOCK PRESCALER = 1

//    BT_init();
//    BT_connect();
    bdc_init();
//    servo_init();
//    headLightsON();
//    reverseLightsON();
//    delay();
//    reverseLightsOFF();

}

void loop() 
{

    for (int i = 0; i <= 150; i++)
    {
        bdcTurnRight(i);
        delay(3);
    }

    for (int i = 150; i >= 0; i--)
    {
        bdcTurnRight(i);
        delay(3);
    }

    for (int i = 0; i <= 150; i++)
    {
        bdcTurnLeft(i);
        delay(3);
    }

    for (int i = 150; i >= 0; i--)
    {
        bdcTurnLeft(i);
        delay(3);
    }
    
}