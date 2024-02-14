#include <avr/io.h>
#include <avr/interrupt.h>
#include "BDCdrv.h"


void bdc_init()
{

    TCCR0A |= (1<<WGM00) | (1<<WGM01) | (1<<COM0A1) | (1<<COM0B1);
    TCCR0A &= (~(1<<COM0A0)) & (~(1<<COM0B0));
    TCCR0B &= (~(1<<WGM02)) & (~(1<<CS02)); 
    TCCR0B |= (1<<CS00) | (1<<CS01);

    // TIMER0 in Fast PWM mode
    // CS02 = 0, CS01 = CS00 = 1 -> prescaler @ 64 ->125kHz at 8Mhz clock.
    // OC0A -> PD6
    // OC0B -> PD5
    // DDRD |= (1<<DDD5) | (1<<DDD6);

    DDRD |= (1<<A_ENABLE) | (1<<DDD5) | (1<<DDD6) | (1<<B_ENABLE);

}


void bdcTurnLeft(uint8_t speed)
{
    if (A_ENABLE != 1) DDRD |= (1<<A_ENABLE);
    if(OCR0B != 0) OCR0B = 0;
    OCR0A = speed; //UP TO 255
}


void bdcTurnRight(uint8_t speed)
{
    if (B_ENABLE != 1) DDRD |= (1<<B_ENABLE);
    if(OCR0A != 0) OCR0A = 0;
    OCR0B = speed; // UP TO 255
}

void bdcCoast()
{
    DDRD &= (~(1<<A_ENABLE)) & (~(1<<B_ENABLE));
    OCR0A = 0;
    OCR0B = 0;
}


void bdcStop()
{
    if (A_ENABLE != 1 || B_ENABLE != 1) DDRD |= (1<<A_ENABLE) | (1<<B_ENABLE);
    if (OCR0A != 0 || OCR0B != 0)
    {
        OCR0A = 255; // MAY NEED TO SET AT 0 AFTER TESTING 
        OCR0B = 255; // MAY NEED TO SET AT 0 AFTER TESTING 
    }
}

