#include <stdint.h>

#include <avr/cpufunc.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "timer.h"


ISR(TIMER0_COMPA_vect)
{
    static uint8_t i = 0;
    if (i == 10) {
        PORTB ^= 1<<PB7;
        i = 0;
    } else {
        ++i;
    };
}


int main()
{
    DDRB |= 1<<DDB7;
    _NOP();
    PORTB &= ~(1<<PB7);

    T0_config(0, 0);
    T0A_config(0, 1);
    sei();
    T0_config(-1, 5);

    while (1) {
        __asm("");
    };
}
