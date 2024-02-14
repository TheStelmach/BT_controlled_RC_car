//#include <avr/io.h>
//#include <avr/interrupt.h>
#include <Arduino.h> // TO BE REMOVED, USING FOR DELAY COMMANDS WHILE DEVELOPING SOFTWARE

#include "BDCdrv.h"
#include "SERVOdrv.h"


void setup() 
{
    Serial.begin(9600);

//    BT_init();
//    BT_connect();
//    bdc_init();
    servo_init();
//    headLightsON();
//    reverseLightsON();
//    reverseLightsOFF();
    delay(100);

}

void loop()
{

    angle_update(45, 'R');
    delay(500);
    angle_update(45, 'L');
    delay(500);


}
