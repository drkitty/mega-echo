#define _BSD_SOURCE 1

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>


int main()
{
    int arduino = open("/dev/ttyACM0", O_RDWR);
    if (arduino == -1) {
        fputs("Error: Couldn't open device.\n", stderr);
        return 1;
    };

    struct termios t;
    tcgetattr(arduino, &t);
    cfmakeraw(&t);
    tcsetattr(arduino, TCSANOW, &t);

    fputs("Waiting for Arduino to initialize...", stdout);
    fflush(stdout);
    sleep(1);
    fputs("\n", stdout);

    uint8_t rbuf;
    int rtn = 0;
    fputs("Testing...\n", stdout);
    for (int sbuf = 0x00; sbuf <= 0xFF; ++sbuf) {
        if (write(arduino, &sbuf, 1) != 1) {
            fputs("Error: Couldn't write.\n", stderr);
            return 1;
        };

        while (read(arduino, &rbuf, 1) != 1) { __asm(""); };

        if (rbuf != sbuf) {
            fprintf(stderr, "0x%02x -> 0x%02x\n", sbuf, rbuf);
            rtn = 1;
        };
    };

    return rtn;
}
