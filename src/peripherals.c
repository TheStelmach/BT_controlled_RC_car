#include <avr/io.h>
#include <avr/interrupt.h>
#include "peripherals.h"
#include "TWI.h"

void periph_init() // ALL PERIPHERALS INITIALIZED HERE
{
    // INBUILT LED (PB5)
    DDRB |= (1<<LEDPIN); 

    // HEADLIGHTS

}

void toggle_inbuilt_LED() 
{ 
    if (PORTB & 0x20) PORTB &= (~(1<<LEDENABLE));
    else PORTB |= (1<<LEDENABLE);
}

void toggle_headlights()
{
    // SELECT PINS FOR HEADLIGHTS FIRST, THEN WRITE THE SAME CODE AS FOR THE BUILT-IN LED
}

// OPTIONAL: USE THE TOF SENSOR TO WRITE THE OBSTACLE AVOIDANCE FEATURE, BASED ON "TWI.h" INCLUDED



