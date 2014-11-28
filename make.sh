#!/usr/bin/env bash

set -o errexit

avr-gcc -std=c99 -Wall -mmcu=avr6 -mmcu=atmega2560 -Os -DF_CPU=16000000L -o echo timer.c utils.c usart.c echo.c
avr-objcopy -O binary echo echo.bin
