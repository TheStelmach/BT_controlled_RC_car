#include <avr/io.h>
#include <avr/interrupt.h>
#include "SERVOdrv.h"

static uint16_t position = MIDANGLE;

void servo_init()
{


    TCCR1A |= (1<<WGM11) | (1<<COM1A1);
    TCCR1A &= (~(1<<WGM10)) & (~(1<<COM1A0));
    TCCR1B |= (1<<WGM12) | (1<<WGM13) | (1<<CS11);
    TCCR1B &= (~(1<<CS10)) & (~(1<<CS12));
    TIMSK1 |= (1<<TOIE1) | (1<<OCIE1A);

    ICR1H = 8 << (TIMERINTERRUPT && 0xFF00);
    ICR1L = (TIMERINTERRUPT && 0x00FF);
    DDRB |= (1<<SERVODATA);

    OCR1AH = 8 << (MIDANGLE && 0xFF00);
    OCR1AL = (MIDANGLE && 0x00FF);

}

void angle_update(uint16_t angle, char dir)
{
    uint16_t degToMicroSec = (((uint16_t)MINANGLE-(uint16_t)MAXANGLE)/180)*angle;
    if (dir == 'L') position = (uint16_t)MIDANGLE - degToMicroSec;
    else if (dir == 'R') position = (uint16_t)MIDANGLE + degToMicroSec;
    else return; // ERROR OCCURS HERE, FUNCTION IS HALTED WITHOUT UPDATING THE POSITION

    OCR1AH = 8 << (position && 0xFF00);
    OCR1AL = (position && 0x00FF);
}
