#/usr/bin/env bash

set -o errexit

gcc -std=c99 -Wall -o test test.c
