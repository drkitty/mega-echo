#include <stdbool.h>
#include <stdint.h>

#include <avr/cpufunc.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "timer.h"
#include "usart.h"
#include "utils.h"


#define QUEUE_SIZE 30


uint8_t queue[QUEUE_SIZE];
int8_t queue_r = 0;
int8_t queue_w = 0;


ISR(USART0_RX_vect)
{
    int8_t next = (queue_w + 1) % QUEUE_SIZE;
    if (next != queue_r) {
        queue[queue_w] = UDR0;
        queue_w = next;
        U0_ie_config(-1, -1, 1);
    };
}


ISR(USART0_UDRE_vect)
{
    if (queue_r != queue_w) {
        UDR0 = queue[queue_r];
        queue_r = (queue_r + 1) % QUEUE_SIZE;
    } else {
        U0_ie_config(-1, -1, 0);
    }
}


ISR(TIMER3_COMPA_vect)
{
    static int8_t inc = 0x8;
    OCR1C += inc;
    if (OCR1C % 0x100 == 0)
        inc = -inc;
}


int main()
{
    DDRB |= 1<<DDB7;
    _NOP();

    U0_ie_config(1, 0, 0);
    U0_config(1, 1, umode_async, upar_none, ustop_1, usize_8, 103);
    // 9600 baud

    T1_config(wgm_fast_pwm_icr, cs_none);
    T1C_config(com_clear, 0);
    ICR1 = 0x100;
    OCR1C = 0x20;

    T3_config(wgm_ctc_ocr, cs_none);
    T3A_config(com_dc, 1);
    OCR3A = 0x100;

    T1_config(-1, cs_clkio_1024);
    T3_config(-1, cs_clkio_1024);

    sei();
    spin();
}
