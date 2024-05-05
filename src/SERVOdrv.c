// https://github.com/TheStelmach

#include <avr/io.h>
#include <avr/interrupt.h>
#include "SERVOdrv.h"


static uint16_t position = (uint16_t)MIDANGLE;

void servo_init()
{

    TCCR1A |= (1<<WGM11) | (1<<COM1A1);
    TCCR1A &= (~(1<<WGM10)) & (~(1<<COM1A0));
    TCCR1B |= (1<<WGM12) | (1<<WGM13) | (1<<CS11);
    TCCR1B &= (~(1<<CS10)) & (~(1<<CS12)); // CONFIGURED TIMER 1 FOR FAST PWM MODE; PRESCALER: 8

    ICR1H = (TIMERINTERRUPT) >> 8;
    ICR1L = (TIMERINTERRUPT); // TIMER TOP LIMIT

    DDRB |= (1<<SERVODATA); // PWM OUTPUT PIN

    OCR1AH = (MIDANGLE) >> 8;
    OCR1AL = (MIDANGLE); // INITIAL POSITION IS 90deg

    //WRITE ANOTHER LIB USING INTERRUPTS ONLY

}

void angle_update(uint16_t angle, char dir) // UPDATE ANGLE
{
    uint16_t degToMicroSec = (((uint16_t)MAXANGLE-(uint16_t)MINANGLE)/180)*(angle);
    if (dir == 'L') position = MIDANGLE - degToMicroSec;
    else if (dir == 'R') position = MIDANGLE + degToMicroSec;
    else return; // ERROR OCCURS HERE, FUNCTION HALTS WITHOUT UPDATING THE POSITION

    OCR1AH = (position) >> 8;
    OCR1AL = (position);
}
