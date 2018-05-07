#ifndef __LIB_MAIN_H
#define __LIB_MAIN_H

#include <stdint.h>

#define MHz 000000
#define kHz 000

#define _XTAL_FREQ 32MHz//!<周波数設定

/**
オシレータを設定します
*/
void InitOSC(void);

/**
すべてのポートをアナログに設定します
*/
void setAllDigitalPort(void);

#endif
