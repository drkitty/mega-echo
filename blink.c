#include <stdint.h>

#include <avr/cpufunc.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "timer.h"
#include "usart.h"
#include "utils.h"


# define QUEUE_SIZE 30


uint8_t queue[QUEUE_SIZE];
int8_t queue_r = 0;
int8_t queue_w = 0;


ISR(USART0_RX_vect)
{
    int8_t next = (queue_w + 1) % QUEUE_SIZE;
    if (next != queue_r) {
        queue[queue_w] = UDR0;
        queue_w = next;
    };
}


ISR(USART0_UDRE_vect)
{
    if (queue_r != queue_w) {
        UDR0 = queue[queue_r];
        queue_r = (queue_r + 1) % QUEUE_SIZE;
    };
}


int main()
{
    DDRB |= 1<<DDB7;
    _NOP();

    U0_ie_config(1, 0, 1);
    U0_config(1, 1, umode_async, upar_none, ustop_1, usize_8, 103);
    // 9600 baud

    T1_config(wgm_ctc_ocr, cs_none);
    T1C_config(com_toggle, 0);
    OCR1AH = 0x10;
    OCR1AL = 0x0;
    T1_config(-1, cs_clkio_1024);

    sei();
    spin();
}
