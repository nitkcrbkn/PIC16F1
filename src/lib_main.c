#include "../../PIC16F1/inc/lib_main.h"
#include <htc.h>

void InitOSC(void) {
    OSCCON = 0xF0; //PLL　Enable
}

void setAllDigitalPort(void) {
    ANSELA = 0x00;
    ANSELB = 0x00;
}