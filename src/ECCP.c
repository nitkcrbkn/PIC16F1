///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�؍X�Í��ꃍ�{�b�g�������D��@
//�t���u���b�W�t��N_MOSFET���[�^�[�h���C�o�[�p�֐�
//Use device microchip PIC16F1938
//MPLAB X IDE(ver.2.30)
//HI-TECH C Compiler for PIC10/12/16 MCUs Version 9.80 in Lite mode  
//Last updata 2015/5/13/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include<htc.h>
#include"./../../PIC16F1/inc/ECCP.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void pwm_init(void)PWM���g�p���邽�߂̏����ݒ�B
//�E�d�l 
//	PWM���g�� = �Q�OKHz @ �����I�V���[�^32MHz -----(1)
//	�^�C�}�[�Q�̓���J�n�@�^�C�}�[�Q�̃v���X�P�[���[�͂P�F�P-----(2)
//	ECCP���W���[���̏����ݒ�@�������t���u���b�W�@�S�o�̓A�N�e�B�ulow-----(3)
//	CCP1�̓^�C�}�[�Q���g�p------(4)
//	�ăX�^�[�g����------(5)
//	�o�̓X�e�A�����O�̕ύX������ PWM �����Ŕ������� �܂��A�o�̓|�[�g�C�i�u��-----(6)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pwm_init(void) {
    TRISA3 = 1;
    TRISA4 = 1;
    ANSELA3 = 0;
    ANSELA4 = 0;
    PR2 = 200; //(1)
    T2CON = 0b00000101; //(2)

    CCP1CON = 0b01001100; //(3)	
    CCPTMRS0 = 0b11111100; //(4)
    CCPTMRS1 = 0b00000011;

    PWM1CON = 0b00000000; //(5)
    PSTR1CON = 0b00011111; //(6)
    
    TRISC2 = 1;
    TRISB = 2; 
    TRISB = 1;
    TRISB = 4;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//void motor_ctrl(unsigned int duty,unsigned char dire):���[�^�[�̕����A��]���𐧌䂷��֐��B
//�Eduty = ���[�^�[�̉�]���x��ݒ�
//	��]���x�͍ō����x��700�i�K�Œ����\
//	�������A�ђʁiFET�̔j���j��h������95%�i700�i�K�j�ɐ���
//�Edire = ���[�^�[��]������ݒ�
//	��]�����̃f�[�^
//	+-------------------------------------------+
//	 |    �f�[�^(��i��) |     ����     �b
//	+-------------------------------------------+
//	 |        0b0000            |   �t���[�@�b
//	 |        0b0001            |   ����]   |
//	 |        0b0010            |   �t��]   |
//	 |        0b0011            |  �u���[�L �b
//	+-------------------------------------------+
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void motor_ctrl(uint16_t duty, unsigned char dire) {
    if (duty > 700)//��]���x�����ő�700�܂�//
        duty = 700;

    //��]�����f�[�^(0b0000) ,�t���[���� // 
    if (dire == 0) {
        LED1 = 0; //�O����LED�ɏ�Ԃ�\��//
        LED2 = 0;
        CCP1CON = 0b01000000; //ECCP���W���[����~//
        CCPR1L = 0; //��]���x���O�ɃZ�b�g//
        P1A = 0; //ECCP�S�o��low//
        P1B = 0;
        P1C = 0;
        P1D = 0;

    }
        //��]�����f�[�^(0b0001) ,����]���� //
    else if (dire == 1) {
        LED1 = 1; //�O����LED�ɏ�Ԃ�\��//
        LED2 = 0;
        CCP1CON = 0b01001100; //ECCP����]���[�h//
        CCPR1L = duty >> 2; //�C�ӂ̉�]���x��ݒ�//
        DC1B0 = duty & 0b00000001;
        DC1B1 = (duty & 0b00000010) >> 1;
    }
        //��]�����f�[�^(0b0010) ,�t��]���� //
    else if (dire == 2) {
        LED1 = 0; //�O����LED�ɏ�Ԃ�\��//
        LED2 = 1;
        CCP1CON = 0b11001100; //ECCP�t��]���[�h//
        CCPR1L = duty >> 2; //�C�ӂ̉�]���x��ݒ�//
        DC1B0 = duty & 0b00000001;
        DC1B1 = (duty & 0b00000010) >> 1;
    }

    //��]�����f�[�^(0b0011) ,�u���[�L���� //
    if (dire == 3) {
        LED1 = 1; //�O����LED�ɏ�Ԃ�\��//
        LED2 = 1;
        CCP1CON = 0b01000000; //ECCP���W���[����~//
        CCPR1L = 0; //��]���x���O�ɃZ�b�g//
        P1A = 0; //ECCP�S�o��low//
        P1B = 0;
        P1C = 0;
        P1D = 0;

        P1A = 0; //�u���[�L���//
        P1B = 1;
        P1C = 0;
        P1D = 1;

    }
}