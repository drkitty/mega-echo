#include <stdint.h>

#include <avr/cpufunc.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "timer.h"
#include "utils.h"


int main()
{
    DDRB |= 1<<DDB7;

    T1_config(wgm_ctc_ocr, cs_none);
    T1C_config(com_toggle, 0);
    sei();
    OCR1AH = 0x10;
    OCR1AL = 0x0;
    T1_config(-1, cs_clkio_1024);

    spin();
}
