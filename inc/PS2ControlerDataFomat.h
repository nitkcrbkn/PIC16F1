/* 
 * File:   PS2ControalerDataFomat.h
 * Author: oishi
 *
 * Created on 2015/05/26, 9:26
 */

#ifndef PS2CONTROALERDATAFOMAT_H
#define	PS2CONTROALERDATAFOMAT_H

#ifdef	__cplusplus
extern "C" {
#endif

/*PS2 controaler 定義データ*/

#define Left    0x08
#define Down	0x04
#define Up  0x01
#define Right   0x02

#define Circle 0x02
#define Tri	0x01
#define Sq 0x08
#define Cross	0x04

#define L1	0x08
#define L2	0x04
#define R1	0x02
#define R2	0x01

#define None 0x00
#define Zyuzi	0x01
#define Marutoka	0x02
#define LR	0x03
#define LY	0x04
#define LX	0x05
#define RY	0x06
#define RX	0x07

#ifdef	__cplusplus
}
#endif

#endif	/* PS2CONTROALERDATAFOMAT_H */

