#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "BDCdrv.h"
#include "SERVOdrv.h"
#include "UART.h"
#include "executer.h"
#include "queue.h"


volatile uint16_t millisec = 0;


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
    char data = queue_read(&data);
    execute(&data);
}

ISR (USART_RX_vect)
{
    char data = UART_Receive();
    queue_write(data);
}

ISR (TIMER2_COMPA_vect)
{
    scheduler(&millisec);
}