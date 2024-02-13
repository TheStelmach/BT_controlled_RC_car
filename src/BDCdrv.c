#include "Arduino.h"
#include "BDCdrv.h"

void bdc_init()
{

    TCCR0A |= (1<<WGM00) | (1<<WGM01) | (1<<COM0A1) | (1<<COM0B1);
    TCCR0A &= (~(1<<COM0A0)) & (~(1<<COM0B0));
    TCCR0B &= (~(1<<WGM02)) & (~(1<<CS01)) & (~(1<<CS00)); 
    TCCR0B |= (1<<CS02);

    // TIMER0 in Fast PWM mode
    // CS02 = 1, CS01 = CS00 = 0 -> prescaler @ 256 ->31.25kHz at 8Mhz clock.
    // OC0A -> PD6
    // OC0B -> PD5
    // DDRD |= (1<<DDD5) | (1<<DDD6);
    DDRD |= (1<<DDD5) | (1<<DDD6);

}


void bdcTurnLeft(uint8_t speed)
{
    if(OCR0B != 0) OCR0B = 0;
    OCR0A = speed; //UP TO 255
    
}


void bdcTurnRight(uint8_t speed)
{
    if(OCR0A != 0) OCR0A = 0;
    OCR0B = speed; // UP TO 255
}

void bdcCoast()
{
    PORTD &= (~(1<<DDD5)) & (~(1<<DDD6)); // DISABLE BOTH PWM
    // SELECT TWO PINS TO USE AS DRIVER ENABLE PINS. PULL BOTH PINS LOW
    OCR0A = 0;
    OCR0B = 0;
}


void bdcStop()
{
    //PULL BOTH DRIVER ENABLE PINS HIGH
    if (OCR0A != 0 || OCR0B != 0)
    {
        OCR0A = 0;
        OCR0B = 0;
    }
}

