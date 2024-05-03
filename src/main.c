#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

#include "TWI.h" // LIBRARY SNATCHED FROM https://github.com/Sovichea/avr-i2c-library/

#include "BDCdrv.h"
#include "SERVOdrv.h"
#include "UART.h"
#include "executer.h"
#include "queue.h"
#include "peripherals.h"
#include "speed.h"
#include "PID.h"

#define PID_KP  2.0f
#define PID_KI  0.5f
#define PID_KD  0.25f
#define PID_TAU 0.02f
#define PID_LIM_MIN -10.0f
#define PID_LIM_MAX  10.0f
#define PID_LIM_MIN_INT -5.0f
#define PID_LIM_MAX_INT  5.0f
#define SAMPLE_TIME_S 0.05f

uint16_t millisec = 0;
char data = 0;
uint16_t motorSpeed = 0.0; // speed on the motor shaft, NOT ACCOUNTED FOR ANY TORQUE REDUCTION RATIOS!!!
char motorDirection;
float desiredSpeed = 0.0, actualSpeed = 0.0, leftWheelSpeed = 0.0, rightWheelSpeed = 0.0;

PIDController pid = { PID_KP, PID_KI, PID_KD, PID_TAU, PID_LIM_MIN,
    PID_LIM_MAX, PID_LIM_MIN_INT, PID_LIM_MAX_INT, SAMPLE_TIME_S };

void setup() 
{
    cli();
    sysTick_init();
    UART_init(); // not needed, can use arduino's serial, but works so might as well...
    queue_init();
    periph_init();
    servo_init();
    bdc_init();
    speed_init();
    PIDController_init(&pid);
    tw_init(TW_FREQ_250K, 1);
    // obstAvoid_init();
    sei();

}

void loop()
{ // WHEN NOT IN INTERRUPTS, EXECUTE COMMANDS
    queue_read(&data);
    if (data) execute(&data, &motorDirection, &desiredSpeed);
    else 
    {
        update_speedometer(&actualSpeed, leftWheelSpeed, rightWheelSpeed);
        calculate_slip(actualSpeed);
        if (switchPID == 1) 
        {
            if (motorDirection == 'F') bdcTurnRight(PIDController_update(&pid, desiredSpeed, motorSpeed));
            else if (motorDirection == 'B') bdcTurnLeft(PIDController_update(&pid, desiredSpeed, motorSpeed));
        }
        //else if (switchPID == 0 && limitAccel == 0)

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
    //update_tachometer(&motorSpeed, millisec); // IF TOO LONG - DISREGARD THE VALUE, THE CAR STOPPED
    PORTB ^= (1 << PB5); // TOGGLES ON-BOARD LED FOR INDICATION
    UART_Transmit((uint8_t)motorSpeed);
}

/*
ISR (INT1_vect)
{ // FRONT WHEELS
// INTERRUPT AND PINS ARE NOT CONFIGURED
    front_wheels(&leftWheelSpeed, &rightWheelSpeed, millisec)

}
*/