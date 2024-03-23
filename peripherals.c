#include <avr/io.h>
#include <avr/interrupt.h>
#include "peripherals.h"

void periph_init() // ALL PERIPHERALS INITIALIZED HERE
{
    // INBUILT LED (PB5)
    DDRB |= (1<<LEDPIN); 

    // HEADLIGHTS


    // MAGNETIC ENCODER AS5600

}

void toggle_headlights()
{

}

void toggle_inbuilt_LED() 
{ 
    if (PORTB & 0x20) PORTB &= (~(1<<LEDENABLE));
    else PORTB |= (1<<LEDENABLE);
}

