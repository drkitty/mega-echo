#ifndef TIMER_H
#define TIMER_H

enum {
    com_dc = 0,
    com_toggle = 1,
    com_clear = 2,
    com_set = 3
};

enum {
    wgm0_normal = 0,
    wgm0_pc_pwm_full = 1,
    wgm0_ctc = 2,
    wgm0_fast_pwm_full = 3,
    wgm0_pc_pwm_OCRnx = 5,
    wgm0_fast_pwm_OCRnx = 7
};

enum {
    cs_none = 0,
    cs_clkio = 1,
    cs_clkio_8 = 2,
    cs_clkio_64 = 3,
    cs_clkio_256 = 4,
    cs_clkio_1024 = 5,
    cs_ext_falling = 6,
    cs_ext_rising = 7
};


void T0_config(int wgm, int cs);

void T0A_config(int com, int ie);

#endif  // TIMER_H
