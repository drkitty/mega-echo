#include <stdint.h>

#include <avr/cpufunc.h>
#include <avr/io.h>
#include <util/delay.h>


int main()
{
    DDRB |= 1<<DDB7;
    _NOP();
    PORTB &= ~(1<<PB7);

    TCCR0B = 0;
    TCCR0A = 1<<COM0A0 | 1<<WGM01;
    // Toggle OC0A on Compare Match; CTC; no clock source

    OCR0A = 0xFF;

    TCCR0B |= 1<<CS02 | 1<<CS00;  // clk_I/O / 1024
    while (1) {
        __asm("");
    };
}
