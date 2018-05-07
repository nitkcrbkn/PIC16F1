#ifndef __DELAY_H
#define __DELAY_H

#include "lib_main.h"

/**
ウェイト関数でms単位で待ちます
\param ms 待ち時間[ms]
*/
void delay_ms(uint16_t ms);
/**
ウェイト関数で10us単位で待ちます
\param us_x10 待ち時間[x10 ux]
*/
void delay_10us(uint16_t us_x10);

#endif
