// https://github.com/TheStelmach

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

#define PID_KP  2.15f
#define PID_KI  0.05f
#define PID_KD  0.005f
#define PID_TAU 0.4f
#define PID_LIM_MIN 0
#define PID_LIM_MAX  255
#define PID_LIM_MIN_INT 0
#define PID_LIM_MAX_INT  120

char motorDirection, data = 0;
char switchPID = 0, switchTraction = 0, switchLights = 0, switchObstacles = 0, limitAccel = 0;
int millisec = 0, counter = 0, motorSpeed = 0, sentValue = 0, 
    desiredSpeed = 0, actualSpeed = 0, leftWheelSpeed = 0, rightWheelSpeed = 0;

PIDController pid = { PID_KP, PID_KI, PID_KD, PID_TAU, PID_LIM_MIN,
    PID_LIM_MAX, PID_LIM_MIN_INT, PID_LIM_MAX_INT};

void setup() 
{
    cli();
    sysTick_init();
    UART_init();
    queue_init();
    periph_init();
    servo_init();
    bdc_init();
    speed_init();
    PIDController_init(&pid, millisec);
    tw_init(TW_FREQ_250K, 1);
    // obstAvoid_init(); // PART OF peripherals.h & .c
    sei();
}

void loop()
{ // WHEN NOT IN INTERRUPTS, EXECUTE COMMANDS
    queue_read(&data);

    if (switchPID != 0) 
    {
        if (motorDirection == 'F') 
            bdcTurnRight(motorSpeed + PIDController_update(&pid, desiredSpeed, motorSpeed, millisec));
        else if (motorDirection == 'B')
            bdcTurnLeft(motorSpeed + PIDController_update(&pid, desiredSpeed, motorSpeed, millisec));
        else bdcStop();
    }

    if (switchTraction != 0)
    { 
        float tractionLimit = (1 - (calculate_slip(actualSpeed,motorSpeed)) * 0.5) * motorSpeed; // IF SLIP OCCURS, SLOW THE MOTOR DOWN
        if (tractionLimit <= 0.0) tractionLimit = 0;
        else if (tractionLimit > 255.0) tractionLimit = 255;
        if (motorDirection == 'F') bdcTurnRight((uint8_t)tractionLimit);
        else if (motorDirection == 'B') bdcTurnLeft((uint8_t)tractionLimit);
        else bdcStop();
    }

    if (limitAccel != 0)
    {
        if (motorDirection == 'F') 
        {
            if (motorSpeed != desiredSpeed && (motorSpeed < 255) && (motorSpeed >= 0)) 
            {
                if (motorSpeed > desiredSpeed) bdcTurnRight((uint8_t)(((motorSpeed + desiredSpeed) / 2) + 1));
                if (motorSpeed < desiredSpeed) bdcTurnRight((uint8_t)(((motorSpeed + desiredSpeed) / 2) + 1));
            }
        }
        else if (motorDirection == 'B') 
        {
            if (motorSpeed != desiredSpeed && (motorSpeed < 255) && (motorSpeed >= 0)) 
            {
                if (motorSpeed > desiredSpeed) bdcTurnLeft((uint8_t)(((motorSpeed + desiredSpeed) / 2) + 1));
                if (motorSpeed < desiredSpeed) bdcTurnLeft((uint8_t)(((motorSpeed + desiredSpeed) / 2) + 1));
            }
        }
        else bdcStop();
    }

    execute(&data, &motorDirection, &desiredSpeed);
}

ISR (USART_RX_vect)
{ // DATA FROM BLUETOOTH
    data = UART_Receive();
    queue_write(data);
}

ISR (TIMER2_COMPA_vect)
{ // SYSTICK IN EXECUTER FILE
    sysTick(&millisec);
}

ISR (INT1_vect)
{ // REAR WHEEL ENCODER PULSE
    update_tachometer(&motorSpeed, millisec); // IF TOO LONG - DISREGARD THE VALUE, THE CAR STOPPED
}

ISR (INT0_vect)
{ // FRONT WHEELS
    front_wheels(&leftWheelSpeed, &rightWheelSpeed, millisec);
    actualSpeed = update_speedometer(leftWheelSpeed, rightWheelSpeed);
}
