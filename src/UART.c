#include "pic.h"
#include "./../../PIC16F1/inc/UART.h"



#define UART_BUFFER_SIZE   32// �t�r�`�q�s�̎�M�o�b�t�@�T�C�Y

uint8_t UART_Buffer[UART_BUFFER_SIZE]; // ��M�����f�[�^���i�[����o�b�t�@
uint8_t UART_Buffer_inptr; // ��M�o�b�t�@�̓ǂݍ��݃|�C���^�[
uint8_t UART_Buffer_outptr; // ��M�o�b�t�@�̏������݃|�C���^�[

/*******************************************************************************
 *  InterUART( void )                                                           *
 *    �t�r�`�q�s�֘A�̊��荞�ݏ���                                              *
 *     ���̊֐��͎�M���s���ꍇ�̓��C���v���O�����̊����݊֐��ŕK���Ăт܂�     *
 *******************************************************************************/
void InterUART(void) {
    uint8_t x;
    uint8_t dt;

    if (RCIF == 1) { // �����݂͂t�r�`�q�s�ʐM�̎�M���H
        // ���W�X�^����f�[�^����M
        dt = RCREG;
        x = (UART_Buffer_outptr + 1) % UART_BUFFER_SIZE;
        if (x != UART_Buffer_inptr) {
            // �o�b�t�@�����t�łȂ��Ȃ�f�[�^��ۑ�����
            UART_Buffer[UART_Buffer_outptr] = dt;
            // �o�b�t�@�������݃|�C���^�[�����ɐi�߂�
            UART_Buffer_outptr = x;
        }

        // �I�[�o�����G���[����(RCREG�o�b�t�@���R�ڂ̃f�[�^����M������I�[�o�t���[)
        if (OERR == 1) {
            CREN = 0;
            while (OERR);
            CREN = 1;
        }

        // �����ݎ�M�t���O�����Z�b�g
        RCIF = 0;
    }
}

/*******************************************************************************
 *  InitUART(rx,tx,brg)                                                         *
 *    �t�r�`�q�s�ʐM�̏��������s������                                          *
 *    rx  : ��M(RX)����s���̔ԍ����w�肷��                                    *
 *    tx  : ���M(TX)����s���̔ԍ����w�肷��                                    *
 *    brg : �{�[���[�g�W�F�l���[�^�̒l���w�肵�܂�(�ʐM���x�ɂȂ�܂�)          *
 *******************************************************************************/
void InitUART(uint8_t rx, uint8_t tx, uint8_t brg) {
    TRISCbits.TRISC7 = 1;
    TRISCbits.TRISC6 = 0;
    TXSTA = 0b00100100; // ���M���ݒ�F�񓯊����[�h�@�W�r�b�g�E�m���p���e�B
    RCSTA = 0b10010000; // ��M���ݒ�
    SPBRG = brg; // �{�[���[�g�̐ݒ�
    BRGH = 0;
    RCIF = 0; // USART�����ݎ�M�t���O�̏�����
    RCIE = 1; // USART�����ݎ�M��L���ɂ���
    PEIE = 1; // ���ӑ��u�����݂�L���ɂ���
    GIE = 1; // �S�����ݏ�����������
    UART_Buffer_inptr = 0; // ��M�o�b�t�@�̓ǂݍ��݃|�C���^�[�̏�����
    UART_Buffer_outptr = 0; // ��M�o�b�t�@�̏������݃|�C���^�[�̏�����
}

/*******************************************************************************
 *  UART_Send(dt,num)                                                           *
 *    ����Ɏw�肵�����̃f�[�^�𑗐M���鏈��                                  *
 *                                                                              *
 *    dt  : ���M����f�[�^���i�[�����z����w�肵�܂��B                          *
 *    num : ���M����f�[�^�̌����w�肵�܂��B                                  *
 *******************************************************************************/
void UART_Send(const uint8_t *dt) {
    while (1) {
        while (TXIF == 0); // ���M�\�ɂȂ�܂ő҂�
        TXREG = *dt; // ���M����
        if (*dt == 0)break;
        *dt++;
    }
}

/*******************************************************************************
 *  UART_Write(dt)                                                              *
 *    ����ɂP�o�C�g�̃f�[�^�𑗐M���鏈��                                      *
 *                                                                              *
 *    dt  : ���M����f�[�^���w�肵�܂��B                                        *
 *******************************************************************************/
void UART_Write(uint8_t dt) {
    while (TXIF == 0); // ���M�\�ɂȂ�܂ő҂�
    TXREG = dt; // ���M����
}

/*******************************************************************************
 *  ans = UART_Available()                                                      *
 *    ��M�����f�[�^�̌���Ԃ�����                                            *
 *                                                                              *
 *    ans : ��M�����f�[�^�̌���Ԃ��܂��B                                    *
 *******************************************************************************/
int UART_Available() {
    return (UART_Buffer_outptr + UART_BUFFER_SIZE - UART_Buffer_inptr) % UART_BUFFER_SIZE;
}

/*******************************************************************************
 *  ans = UART_Read()                                                           *
 *    ��M�����f�[�^���P�o�C�g�ǂݍ��ޏ���                                      *
 *                                                                              *
 *    ans : ��M�����f�[�^��Ԃ��܂�  0xffff��Ԃ������M�f�[�^�͋�ł��B      *
 *******************************************************************************/
uint16_t UART_Read() {
    uint16_t ans;

    // �o�b�t�@�͋�ł���
    if (UART_Buffer_inptr == UART_Buffer_outptr) return 0xffff;
    // �o�b�t�@����ǂݏo��
    ans = UART_Buffer[UART_Buffer_inptr];
    // �o�b�t�@�ǂݍ��݃|�C���^�[�����ɐi�߂�
    UART_Buffer_inptr = (UART_Buffer_inptr + 1) % UART_BUFFER_SIZE;

    return ans;
}

/*******************************************************************************
 *  UART_Flush()                                                                *
 *    ��M�o�b�t�@���N���A���鏈��                                              *
 *******************************************************************************/
void UART_Flush() {
    UART_Buffer_inptr = 0; // ��M�o�b�t�@�̓ǂݍ��݃|�C���^�[�̏�����
    UART_Buffer_outptr = 0; // ��M�o�b�t�@�̏������݃|�C���^�[�̏�����
}
