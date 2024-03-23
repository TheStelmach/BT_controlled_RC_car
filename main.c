#include <avr/io.h>
#include <avr/interrupt.h>
// #include <stdlib.h>
// #include "TWI.h" // LIBRARY SNATCHED FROM https://github.com/Sovichea/avr-i2c-library/

#include "BDCdrv.h"
#include "SERVOdrv.h"
#include "UART.h"
#include "executer.h"
#include "queue.h"
// #include "peripherals.h"

uint16_t millisec = 0;
char data = 0; // FOR UART TESTING PURPOSES
char *dataPtr = &data; // FOR UART TESTING PURPOSES

void setup() 
{

    sysTick_init();
    UART_init(); // not needed, can use arduino's serial, but works so might as well...
    queue_init();
    // periph_init();
    servo_init();
    bdc_init();
    // tw_init(TW_FREQ_250K, 1);
    // BT_connect();
    // speedometer_init();
    // obstAvoid_init();
    // smartCruise_init();

}

void loop()
{
    angle_update(90, 'L');
    // if (millisec >= 100) {toggle_inbuilt_LED(); return;} // for checking if systick works correctly
    // else PORTB &= (~(1<<LEDENABLE));
    // UART_Transmit(data); // FOR UART TESTING PURPOSES
    // UART_Transmit(' '); // FOR UART TESTING PURPOSES
    // UART_Transmit(millisec); // FOR SYSTICK TESTING PURPOSES
    // UART_Transmit('\n'); // FOR SYSTICK TESTING PURPOSES
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