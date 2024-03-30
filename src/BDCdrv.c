// https://github.com/TheStelmach

#include <avr/io.h>
#include <avr/interrupt.h>
#include "BDCdrv.h"


void bdc_init()
{

    TCCR0A |= (1<<WGM00) | (1<<WGM01) | (1<<COM0A1) | (1<<COM0B1);
    TCCR0A &= (~(1<<COM0A0)) & (~(1<<COM0B0));
    TCCR0B &= (~(1<<WGM02)) & (~(1<<CS02)); 
    TCCR0B |= (1<<CS00) | (1<<CS01); // CONFIGURED TIMER 0 FOR FAST PWM MODE; PRESCALER: 256

    DDRD |= (1<<A_ENABLE) | (1<<A_PWM) | (1<<B_PWM) | (1<<B_ENABLE); 
    PORTD |= (1<<A_EN_PIN) | (1<<B_EN_PIN);
    // TWO ENABLE PINS AND TWO PWM OUTPUTS, AS PER THE USED MOTOR DRIVER'S DATASHEET

}


void bdcTurnLeft(uint8_t speed)
{
    if (A_ENABLE != 1) DDRD |= (1<<A_ENABLE);
    if (A_EN_PIN != 1) PORTD |= (1<<A_EN_PIN); // MAKE SURE THE ENABLE PIN IS SET
    if(OCR0B != 0) OCR0B = 0; // STOP PWM ON THE OTHER PWM OUTPUT
    OCR0A = speed; //UP TO 255
}


void bdcTurnRight(uint8_t speed)
{
    if (B_ENABLE != 1) DDRD |= (1<<B_ENABLE);
    if (B_EN_PIN != 1) PORTD |= (1<<B_EN_PIN); // MAKE SURE THE ENABLE PIN IS SET
    if(OCR0A != 0) OCR0A = 0; // STOP PWM ON THE OTHER PWM OUTPUT
    OCR0B = speed; // UP TO 255
}

void bdcStop()
{
    if (A_EN_PIN != 1 || B_EN_PIN != 1) DDRD |= (1<<A_EN_PIN) | (1<<B_EN_PIN);
    if (OCR0A != 0 || OCR0B != 0)
    {
        OCR0A = 255; 
        OCR0B = 255; 
    }
}

