#include <avr/io.h>
#include <avr/interrupt.h>
#include "speed.h"

void speed_init()
{
    // MOTOR ENCODER
    // ENABLE INT0 INTERRUPTS AT FALLING EDGE
    EICRA |= (1<<ISC01);
    EICRA &= (~(1<<ISC00));
    DDRD &= (~(1<<INTERRUPT_PIN)); // PIN PD2 ENABLED AS INPUT
    PORTD |= (1<<INTERRUPT_PIN_ENABLE); // INTERNAL PULLUP ACTIVATED


    // FRONT WHEEL ENCODERS
    DDRC &= (~(1<<LEFT_ENC)) & (~(1<<RIGHT_ENC)); 

}

float update_tachometer(float *motorSpeed)
{

    return 0.0;
}

float update_speedometer(float *actualSpeed)
{
    return (((30/how_many_micros_right_wheel())+(30/how_many_micros_left_wheel()))/2); 
    // AVERAGE TIME FOR ONE WHEEL REVOLUTION
}

uint16_t how_many_micros_right_wheel()
{
    uint8_t timerValueStart;
    uint8_t timerValueEnd;

    if (PINC1 == 0) {while (PINC1 == 0) {};}
    else {timerValueStart = TCNT2;}

    if (PINC1 == 0) {while (PINC1 == 0) {};}
    else {timerValueEnd = TCNT2;}

    int16_t howLong = (timerValueEnd - timerValueStart);
    if (howLong > 0) return howLong; // HOW MANY MICROSECONDS HAVE PASSED
    else howLong = (TICK - timerValueStart + timerValueEnd);
    return howLong;
}

uint16_t how_many_micros_left_wheel()
{
    uint8_t timerValueStart;
    uint8_t timerValueEnd;

    if (PINC1 == 0) {while (PINC1 == 0) {};}
    else {timerValueStart = TCNT2;}

    if (PINC1 == 0) {while (PINC1 == 0) {};}
    else {timerValueEnd = TCNT2;}

    int16_t howLong = (timerValueEnd - timerValueStart);
    if (howLong > 0) return howLong; // HOW MANY MICROSECONDS HAVE PASSED
    else howLong = (TICK - timerValueStart + timerValueEnd);
    return howLong;
}

float calculate_slip (float actualSpeed)
{

    return 0.0;
}

// TRY WITH ONE OF THE QUADRATURE LINES AS WELL...
