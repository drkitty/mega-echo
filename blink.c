#include <stdint.h>

#include <avr/cpufunc.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>


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

    TCCR0B = 0;
    TCCR0A = 0;
    // WGM = normal; no clock source

    sei();
    TIMSK0 = 1<<OCIE0A;
    TCCR0B |= 1<<CS02 | 1<<CS00;  // clk_I/O / 1024

    while (1) {
        __asm("");
    };
}
