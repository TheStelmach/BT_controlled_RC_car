#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "BDCdrv.h"
#include "SERVOdrv.h"
#include "UART.h"
#include "executer.h"
#include "queue.h"


uint16_t millisec = 0;


void setup() 
{
    sysTick_init();
    UART_init(); // not needed, can use arduino's serial, but works so might as well...
    queue_init();
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
    char command = (nextInQueue(&currQueue, &queue[]));
    if (command != 0) execute(command);


}

ISR (USART_RX_vect)
{
    char newCommand = UART_Receive();
    sendToQueue(&currQueue, newCommand, &queue[]);

//    printQueue(task);
//    UART_Transmit('A');
}

ISR (TIMER2_COMPA_vect)
{
    scheduler(&millisec);
}