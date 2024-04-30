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
float motorSpeed = 0.0; // speed on the motor shaft, NOT ACCOUNTED FOR ANY TORQUE REDUCTION RATIOS!!!
float actualSpeed = 0.0, leftWheelSpeed = 0.0, rightWheelSpeed = 0.0;

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
    // obstAvoid_init();
    sei();

}

void loop()
{ // WHEN NOT IN INTERRUPTS, EXECUTE COMMANDS
    queue_read(&data);
    if (data != 0) execute(&data);
    else 
    {
    update_speedometer(&actualSpeed, leftWheelSpeed, rightWheelSpeed);
    calculate_slip(actualSpeed);
    }
}

ISR (USART_RX_vect)
{ // DATA FROM BLUETOOTH
    data = UART_Receive(); // FOR UART TESTING PURPOSES
    queue_write(data);
}

ISR (TIMER2_COMPA_vect)
{ // SCHEDULER TICK IN EXECUTER
    scheduler(&millisec);
}

ISR (INT0_vect)
{ // REAR WHEEL ENCODER PULSE
    update_tachometer(&motorSpeed, millisec); // IF TOO LONG - DISREGARD THE VALUE, THE CAR STOPPED

}

/*
ISR (INT1_vect)
{ // FRONT WHEELS
// INTERRUPT AND PINS ARE NOT CONFIGURED
    front_wheels(&leftWheelSpeed, &rightWheelSpeed, millisec)

}
*/