#include <avr/io.h>
#include <avr/interrupt.h>
// #include <stdlib.h>
#include "TWI.h" // LIBRARY SNATCHED FROM https://github.com/Sovichea/avr-i2c-library/

#include "BDCdrv.h"
#include "SERVOdrv.h"
#include "UART.h"
#include "executer.h"
#include "queue.h"
#include "peripherals.h"
#include "speed.h"

uint16_t millisec = 0;
char data = 0; // FOR UART TESTING PURPOSES
char *dataPtr = &data; // FOR UART TESTING PURPOSES

float actualSpeed = 0.0; // average speed on the front wheels
float motorSpeed = 0.0; // speed on the motor shaft, NOT ACCOUNTED FOR ANY TORQUE REDUCTION RATIOS!!!

void setup() 
{
    cli();
    sysTick_init();
    UART_init(); // not needed, can use arduino's serial, but works so might as well...
    queue_init();
    periph_init();
    servo_init();
    bdc_init();
    speed_init(); // encoders, speed calculation, slip calculation, PID
    tw_init(TW_FREQ_250K, 1);
    // BT_connect();
    // obstAvoid_init();
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

ISR (INT0_vect)
{
    update_tachometer(&motorSpeed); // IF TOO LONG - DISREGARD THE VALUE, THE CAR STOPPED
    update_speedometer(&actualSpeed);
    calculate_slip(actualSpeed);
}