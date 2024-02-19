#include <avr/io.h>
#include <avr/interrupt.h>

#include "BDCdrv.h"
#include "SERVOdrv.h"
#include "UART.h"
#include "sysTick.h"
#include "manager.h"

uint16_t millisec = 0;

void setup() 
{
    sysTick_init();
    UART_init(); // not needed, can use arduino's serial, but works so might as well...
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
    // EXECUTE TASKS FROM FIFO BUFFER
}

ISR (USART_RX_vect)
{
    Queue task = manageData();
//    printQueue(task);
//    UART_Transmit('A');
}

ISR (TIMER2_COMPA_vect)
{
    scheduler(&millisec);
}