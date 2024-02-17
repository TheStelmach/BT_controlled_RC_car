#include <avr/io.h>
#include <avr/interrupt.h>
#include <Arduino.h> // TO BE REMOVED, USING FOR DELAY COMMANDS WHILE DEVELOPING SOFTWARE

#include "BDCdrv.h"
#include "SERVOdrv.h"
#include "UART.h"


void setup() 
{

//    systick();
    UART_init(); // not needed, you can use arduino's serial, but works
//    BT_connect();
    bdc_init();
    servo_init();
//    I2C_init();
//    speedometer_init();
//    obstAvoid_init();
//    smartCruise_init();
//    lights_init();

}

    char received;

void loop()
{

    unsigned char rcvd = USART_Receive();
    UART_Transmit(rcvd); 
    
}
