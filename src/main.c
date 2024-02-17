#include <avr/io.h>
#include <avr/interrupt.h>
//#include <Arduino.h> // TO BE REMOVED, USING FOR DELAY COMMANDS WHILE DEVELOPING SOFTWARE

#include "BDCdrv.h"
#include "SERVOdrv.h"
#include "UART.h"
#include "sysTick.h"
uint16_t millisec = 0;

void setup() 
{

    sysTick_init();
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

void loop()
{
    
}

ISR (USART_RX_vect)
{
    // SEND THE NEW DATA INTO THE SCHEDULER FIFO BUFFER
}

ISR (TIMER2_COMPA_vect)
{
    scheduler(&millisec);
}