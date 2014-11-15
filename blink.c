#include <stdint.h>

#include <avr/cpufunc.h>
#include <avr/io.h>
#include <util/delay.h>


int main()
{
    DDRB |= 1<<DDB7;
    _NOP();
    while (1) {
        PORTB |= (1<<PB7);
        for (uint32_t i = 0; i <= 500000; ++i) { __asm(""); };
        PORTB &= ~(1<<PB7);
        for (uint32_t i = 0; i <= 500000; ++i) { __asm(""); };
        PORTB |= (1<<PB7);
        for (uint32_t i = 0; i <= 500000; ++i) { __asm(""); };
        PORTB &= ~(1<<PB7);
        for (uint32_t i = 0; i <= 1500000; ++i) { __asm(""); };
    };
}
