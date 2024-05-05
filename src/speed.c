// https://github.com/TheStelmach

#include <avr/io.h>
#include <avr/interrupt.h>
#include "speed.h"

#define SLIP_THRESHOLD 0.2
int prevTimeRearWheel = 0, prevTimeLeftWheel = 0, prevTimeRightWheel = 0;

void speed_init()
{
    // MOTOR ENCODER
    // ENABLE INT1 INTERRUPTS AT FALLING EDGE
    EICRA |= (1<<ISC11);
    EICRA &= (~(1<<ISC10));
    DDRD &= (~(1<<INTERRUPT1_PIN)); // PIN PD2 ENABLED AS INPUT
    PORTD |= (1<<INTERRUPT1_PIN_ENABLE); // INTERNAL PULLUP ACTIVATED
    EIMSK |= (1<<INT1);

    // FRONT WHEELS
    // ENABLE INT0 INTERRUPTS AT FALLING EDGE
    EICRA |= (1<<ISC01);
    EICRA &= (~(1<<ISC00));
    DDRD &= (~(1<<INTERRUPT0_PIN)); // PIN PD2 ENABLED AS INPUT
    PORTD |= (1<<INTERRUPT0_PIN_ENABLE); // INTERNAL PULLUP ACTIVATED
    EIMSK |= (1<<INT0);
    DDRC &= (~(1<<DDC1)) & (~(1<<DDC2));
    PORTC |= (1<<PIN1) | (1<<PIN2); // INTERNAL PULLUPS ACTIVATED
}

void update_tachometer(int *motorSpeed, int millisec)
{
    float speed = (255*79)/(millisec-prevTimeRearWheel);
    // MULTIPLIED BY 79 TO SCALE THE VALUE. AT MAXIMUM SPEED, IT TAKES 79ms BETWEEN ENCODER INTERRUPTS
    prevTimeRearWheel = millisec;
/*    if(speed >= 0) *motorSpeed = (uint8_t)speed;
    else *motorSpeed = 0;*/
    *motorSpeed = speed;
}

void front_wheels(int *leftWheelSpeed, int *rightWheelSpeed, int millisec)
{
    static int leftPrevMillisec = 0, rightPrevMillisec = 0;
    if((PINC & (1 << PINC1)) && !(PINC & (1 << PINC2)))
    {
        *leftWheelSpeed = 255*52/(millisec - leftPrevMillisec);
        // MULTIPLIED BY 52 TO SCALE THE VALUE. AT MAXIMUM SPEED, IT TAKES 79ms BETWEEN INTERRUPTS FOR ONE WHEEL
        leftPrevMillisec = millisec;
    }
    else if((PINC & (1 << PINC2)) && !(PINC & (1 << PINC1)))
    {
        *rightWheelSpeed = 255*52/(millisec - rightPrevMillisec);
        // MULTIPLIED BY 52 TO SCALE THE VALUE. AT MAXIMUM SPEED, IT TAKES 79ms BETWEEN INTERRUPTS FOR ONE WHEEL
        rightPrevMillisec = millisec;
    }
    else if((PINC & (1 << PINC1)) && (PINC & (1 << PINC2)))
    {
        *leftWheelSpeed = 255*52/(millisec - leftPrevMillisec);
        *rightWheelSpeed = 255*52/(millisec - rightPrevMillisec);
        leftPrevMillisec = millisec;
        rightPrevMillisec = millisec;
    }
    else return;
}

int update_speedometer(int leftWheelSpeed, int rightWheelSpeed)
{
    return ((leftWheelSpeed + rightWheelSpeed)/2);
}

float calculate_slip(int actualSpeed, int motorSpeed)
{
    float slip = (motorSpeed - actualSpeed)/motorSpeed;
    if(slip >= SLIP_THRESHOLD && slip < 1.0) return slip;
    else return 0.0;
}
