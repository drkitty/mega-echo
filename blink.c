#include <stdint.h>

#include <avr/cpufunc.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "timer.h"
#include "usart.h"
#include "utils.h"


ISR(TIMER1_COMPC_vect)
{
    UDR0 = 'x';
}


int main()
{
    DDRB |= 1<<DDB7;
    _NOP();

    U0_ie_config(0, 0, 0);
    U0_config(0, 1, umode_async, upar_none, ustop_1, usize_8, 103);

    T1_config(wgm_ctc_ocr, cs_none);
    T1C_config(com_toggle, 1);
    sei();
    OCR1AH = 0x10;
    OCR1AL = 0x0;
    T1_config(-1, cs_clkio_1024);

    spin();
}
