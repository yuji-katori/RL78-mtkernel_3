/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.00.00
 *
 *    Copyright (C) 2006-2019 by Ken Sakamura.
 *    This software is distributed under the T-License 2.1.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2019/12/11.
 *
 *----------------------------------------------------------------------
 */

/*
 *    tm_com.c
 *    T-Monitor Communication low-level device driver (C-First)
 */

#include <tk/typedef.h>
#include <sys/sysdef.h>
#include "../../libtm.h"
#include "iodefine.h"

#ifdef CLANGSPEC
EXPORT	void	tm_snd_dat( const VB* buf, INT size )
#else
EXPORT	void	tm_snd_dat( const UB* buf, INT size )
#endif /* CLANGSPEC */
{
#if USE_COM_C_FIRST
int i;
	for( i=0 ; i < size ; i++ )  {
		while( SSR00L & 0x20)  ;	// ���M�o�b�t�@�̋󂫑҂�
		SDR00 = buf[i];			// ���M�o�b�t�@�Ƀ��C�g
	}
#endif /* USE_COM_C_FIRST */
}


#ifdef CLANGSPEC
EXPORT	void	tm_rcv_dat( VB* buf, INT size )
#else
EXPORT	void	tm_rcv_dat( UB* buf, INT size )
#endif /* CLANGSPEC */
{
#if USE_COM_C_FIRST
int i;
	for( i=0 ; i < size ; i++ )  {
		while( !(SSR01L & 0x25) )  ;	// �����̎�M�҂�
		if( SSR01L & 0x20)  {		// ��M�o�b�t�@�Ƀf�[�^�����邩�H
			buf[i] = SDR01;		// ��M�o�b�t�@�Ƀ��[�h
			continue;
		}
		if( SSR01L & 0x04 )		// �t���[�~���O�G���[���H
			SIR01L = 0x04;		// �t���O���N���A
		if( SSR01L & 0x01 )		// �I�[�o�[�t���[�G���[���H
			SIR01L = 0x01;		// �t���O���N���A
		break;
	}
#endif /* USE_COM_C_FIRST */
}


EXPORT	void	tm_com_init(void)
{
#if USE_COM_C_FIRST
	SAU0EN = 1; 			// �V���A���A���C���j�b�g0���C�l�[�u��
	SPS0 = 0x0011;			// fMCK=fCLK/2(32MHz/2)
	SMR00 = 0x0022;			// UART���[�h,CK00,���M
	SCR00 = 0x8097;			// ���M,8�r�b�g,�p���e�B�Ȃ�,1�X�g�b�v�r�b�g,LSB�t�@�[�X�g
	SDR00 = 0x8800;			// 115200bps
	SOE0L_bit.no0 = 1;		// �o�͋���
	SMR01 = 0x0122;			// UART���[�h,CK00,��M
	SCR01 = 0x4097;			// ��M,8�r�b�g,�p���e�B�Ȃ�,1�X�g�b�v�r�b�g,LSB�t�@�[�X�g
	SDR01 = 0x8800;			// 115200bps
	NFEN0_bit.no0 = 1;		// RxD0�[�q�̃m�C�Y�t�B���^��ON
	PM5_bit.no1 = 0;		// TxD0�[�q���o�̓��[�h�ɐݒ�
	P5_bit.no1 = 1;			// TxD0�o�͂�L����
	PM5_bit.no0 = 1;		// RxD0�[�q����̓��[�h�ɐݒ�
      	SS0L = 0x03;			// ���M��M���싖��
#endif /* USE_COM_C_FIRST */
}