/*
 * File:   UART_Driver.h
 * Author: Oishi
 *
 * Created on 2015/02/22, 19:27
 */
#ifndef UART_DRIVER_H
#define	UART_DRIVER_H

#include <stdint.h>

/**
USARTモジュールでの割り込み処理
\sa InitUART
 */
void InterUART( void ) ;
//機能：	UARTの割り込み時の読み出し関数

/**
USARTモジュールの初期化関数
\sa initUART
\param rx 受信ピン設定(普段は0）
\param tx 送信ピン設定(普段は0）
\param brg ボーレート設定（32MHｚで9600bits/secの時、204）
 */
void InitUART(uint8_t rx, uint8_t tx,uint8_t brg) ;
//機能：	UART初期化関数
//引数：	rx...受信ピン設定（1938などは関係なし）
//			tx...送信ピン設定（1938などは関係なし）
//			brg...速度＠9600bit/sec（32MHz...207、16MHz...103）

/**
USARTでの送信関数
\sa initUART
\param dt 送信データ
 */
void UART_Write(uint8_t dt) ;

/**
USARTでの受信関数
\sa initUART
\ret データが送られてきたら、送られたUARTの読み出し値で、何もバッファに残っていなければ0xFFFF
 */
uint16_t UART_Read() ;

/**
UARTバッファクリア関数
\sa initUART
 */
void UART_Flush() ;

#endif	/* UART_DRIVER_H */
