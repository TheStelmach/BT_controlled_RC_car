#include <avr/io.h>
#include <avr/interrupt.h>
#include "speed.h"

uint16_t prevTimeRearWheel = 0.0, prevTimeLeftWheel = 0.0, prevTimeRightWheel = 0.0;

void speed_init()
{
    // USING INBUILT LED FOR INDICATIONS AND TESTING
    DDRB |= (1<<DDB5);

    // MOTOR ENCODER
    // ENABLE INT0 INTERRUPTS AT FALLING EDGE
    EICRA |= (1<<ISC01);
    EICRA &= (~(1<<ISC00));
    DDRD &= (~(1<<INTERRUPT_PIN)); // PIN PD2 ENABLED AS INPUT
    PORTD |= (1<<INTERRUPT_PIN_ENABLE); // INTERNAL PULLUP ACTIVATED
    EIMSK |= (1<<INT0);


    // FRONT WHEELS
    // DDRC &= (~(1<<LEFT_ENC)) & (~(1<<RIGHT_ENC)); 

}

void update_tachometer(uint16_t *motorSpeed, uint16_t millisec) // uint32_t might not be supported, if problems arise - go back to uint16_t
{
    //float speed = 60000/(millisec-prevTimeRearWheel); // REVOLUTIONS PER MINUTE
    float speed = 255/(millisec-prevTimeRearWheel);
    prevTimeRearWheel = millisec;
    if(speed <= 50.0) *motorSpeed = speed;
    else *motorSpeed = 0.0;
}

void front_wheels(float *leftWheelSpeed, float *rightWheelSpeed, uint16_t millisec)
{

    return;
}

void update_speedometer(float *actualSpeed, float leftWheelSpeed, float rightWheelSpeed)
{

    return;
}

float calculate_slip (float actualSpeed)
{

    return 0.0;
}
