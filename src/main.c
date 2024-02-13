#include <avr/io.h>
#include <avr/interrupt.h>
#include "Arduino.h" // TO BE REMOVED, USING FOR DELAY COMMANDS WHILE DEVELOPING SOFTWARE

#include "BDCdrv.h"
#include "SERVOdrv.h"

uint8_t _loop = 1;

void setup() 
{

    CLKPR &= (~(1<<CLKPS0)) & (~(1<<CLKPS1)) & (~(1<<CLKPS2)) & (~(1<<CLKPS3)); // CLOCK PRESCALER = 1

//    BT_init();
//    BT_connect();
//    bdc_init();
    servo_init();
//    headLightsON();
//    reverseLightsON();
//    reverseLightsOFF();

}

void loop()
{
    OCR2B = 15;
    delay(2000);
    OCR2B = 10;
    delay(2000);
}
