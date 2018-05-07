#include <htc.h>
#include <stdint.h>
#include "../../PIC16F1/inc/delay.h"

//ウェイト　ms単位です。

void delay_ms(uint16_t ms) {
    for (; ms--;) {
        __delay_ms(1);
    }
}

void delay_10us(uint16_t us_x10) {
    for (; us_x10--;) {
        __delay_us(9);
    }
}