// https://github.com/TheStelmach

#include <avr/io.h>
#include <avr/interrupt.h>
// #include <stdlib.h>
// #include "TWI.h" // LIBRARY SNATCHED FROM https://github.com/Sovichea/avr-i2c-library/

#include "BDCdrv.h"
#include "SERVOdrv.h"
#include "UART.h"
#include "executer.h"
#include "queue.h"
#include "peripherals.h"

uint16_t millisec = 0;
char data = 0; // FOR UART TESTING PURPOSES
char *dataPtr = &data; // FOR UART TESTING PURPOSES

void setup() 
{
    cli();
    sysTick_init();
    UART_init(); // not needed, can use arduino's serial, but works so might as well...
    queue_init();
    periph_init();
    servo_init();
    bdc_init();
    // tw_init(TW_FREQ_250K, 1);
    // BT_connect();
    // speedometer_init();
    // obstAvoid_init();
    // smartCruise_init();
    sei();

}

void loop()
{
    queue_read(&data);
    execute(&data);
}

ISR (USART_RX_vect)
{
    *dataPtr = UART_Receive(); // FOR UART TESTING PURPOSES
    queue_write(data);
}

ISR (TIMER2_COMPA_vect)
{
    scheduler(&millisec);
}
