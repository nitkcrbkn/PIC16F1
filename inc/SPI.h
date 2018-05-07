/* 
 * File:   SPI.h
 * Author: evaota
 *
 * Created on 2015/04/02, 20:19
 */

#ifndef SPI_H
#define	SPI_H

#include <stdint.h>

/**
SPIを初期化します
*/
void SSP_init(void);

/**
SPIの送信関数（未検証？）
\sa SSP_init
*/
void SSP_Send(uint8_t add,uint8_t data);
/**
SPIの受信関数（未検証？）
\sa SSP_init
*/

/**

\sa SSP_init
*/
uint8_t SSP_Read(uint8_t add);
#endif	/* SPI_H */

