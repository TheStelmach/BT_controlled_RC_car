#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "TWI.h" // LIBRARY SNATCHED FROM https://github.com/Sovichea/avr-i2c-library/

#include "BDCdrv.h"
#include "SERVOdrv.h"
#include "UART.h"
#include "executer.h"
#include "queue.h"
#include "peripherals.h"


volatile uint16_t millisec = 0;


void setup() 
{
    sysTick_init();
    UART_init(); // not needed, can use arduino's serial, but works so might as well...
    queue_init();
    periph_init();
    // BT_connect();
    bdc_init();
    servo_init();
    tw_init(TW_FREQ_250K, 1);
    // speedometer_init();
    // obstAvoid_init();
    // smartCruise_init();

}

void loop()
{
    if (millisec >= 100) {toggle_inbuilt_LED(); return;} // for checking if systick works correctly
    else PORTB &= (~(1<<LEDENABLE));
    char data = 0;
    queue_read(&data);
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