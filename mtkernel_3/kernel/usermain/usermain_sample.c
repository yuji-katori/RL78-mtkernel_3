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
 *	usermain.c (usermain)
 *	User Main
 */

#include <tk/tkernel.h>
#include <string.h>
#include "iodefine.h"

EXPORT void led0_tsk(INT stacd, void *exinf);
EXPORT void led2_tsk(INT stacd, void *exinf);
EXPORT void sw1_hdr(UINT intno);

typedef enum { LED0_TSK, LED2_TSK, OBJ_KIND_NUM } OBJ_KIND;
EXPORT ID ObjID[OBJ_KIND_NUM];					// ID�e�[�u��

EXPORT INT usermain( void )
{
T_CTSK t_ctsk;
T_DINT t_dint;
ID objid;

	t_ctsk.tskatr = TA_HLNG | TA_DSNAME;			// �^�X�N������ݒ�
	t_ctsk.stksz = 256;					// �X�^�b�N�T�C�Y��256�o�C�g
	t_ctsk.itskpri = 1;					// led0_tsk�̗D��x
#ifdef CLANGSPEC
	t_ctsk.task =  led0_tsk;				// led0_tsk�̋N���A�h���X
	strcpy( t_ctsk.dsname, "led0_tsk" );			// led0_tsk�̖���
#else
	t_ctsk.task =  (FP)led0_tsk;				// led0_tsk�̋N���A�h���X
	strcpy( (char*)t_ctsk.dsname, "led0_tsk" );		// led0_tsk�̖���
#endif /* CLANGSPEC */
	if( (objid = tk_cre_tsk( &t_ctsk )) <= E_OK )		// led0_tsk�̐���
		goto ERROR;
	ObjID[LED0_TSK] = objid;
	if( tk_sta_tsk( ObjID[LED0_TSK], 0 ) != E_OK )		// led0_tsk�̋N��
		goto ERROR;

	t_ctsk.itskpri = 2;					// led2_tsk�̗D��x
#ifdef CLANGSPEC
	t_ctsk.task = led2_tsk;					// led2_tsk�̋N���A�h���X
	strcpy( t_ctsk.dsname, "led2_tsk" );			// led2_tsk�̖���
#else
	t_ctsk.task = (FP)led2_tsk;				// led2_tsk�̋N���A�h���X
	strcpy( (char*)t_ctsk.dsname, "led2_tsk" );		// led2_tsk�̖���
#endif /* CLANGSPEC */
	if( (objid = tk_cre_tsk( &t_ctsk )) <= E_OK )		// led2_tsk�̐���
		goto ERROR;
	ObjID[LED2_TSK] = objid;
	if( tk_sta_tsk( ObjID[LED2_TSK], 0 ) != E_OK )		// led2_tsk�̋N��
		goto ERROR;

	t_dint.intatr = TA_HLNG;				// �����݃n���h������
	t_dint.inthdr = sw1_hdr;				// sw1_hdr�̋N���A�h���X
	if( tk_def_int( INTP9, &t_dint ) != E_OK )		// INTP9�����݃n���h���̒�`
		goto ERROR;

	P1 = 0x80;	PM1 = 0x7F;				// LED0�̏�����
	P5 = 0x20;	PM5 = 0xDF;				// LED1�̏�����
	P0 = 0x02;	PM0 = 0xFD;				// LED2�̏�����

	PU7 = 0x20;						// SW1�̃v���A�b�v��RON
	EGN1 = 0x02;  EGP1 = 0x02;				// SW1�͗��G�b�W
	ClearInt( INTP9 );					// INTP9�̊����ݗv�����N���A
	EnableInt( INTP9, 3 );					// INTP9�̊����݂�����
	EnableInt( INTWDTI, 0 );				// INTWDTI�̊����݂�����

	while( 1 )  tk_slp_tsk(TMO_FEVR);			// �N���҂�
ERROR:
	return 0;
}

EXPORT void led0_tsk(INT stacd, void *exinf)
{
	while( 1 )  {
		tk_dly_tsk( 500 );				// 500ms�̒x��
		P1 ^= 0x80;					// LED0�̓_��
	}
}

EXPORT void led2_tsk(INT stacd, void *exinf)
{
	while( 1 )  {
		tk_slp_tsk( TMO_FEVR );				// �N���҂�(����������G�b�W�҂�)
		P0 ^= 0x02;					// LED2�̓_��
		while( E_OK == tk_slp_tsk( 10 ) )  ;		// �`���^�����O����
		tk_slp_tsk( TMO_FEVR );				// �N���҂�(�����オ��G�b�W�҂�)
		while( E_OK == tk_slp_tsk( 10 ) )  ;		// �`���^�����O����
	}
}

EXPORT void sw1_hdr(UINT intno)
{
	tk_wup_tsk( ObjID[LED2_TSK] );				// led2_tsk�̋N��
}


// OS�Ǘ��O�����݃n���h���̋L�q��
// ���[�U�I�v�V�����o�C�g�l��0xFDFFE8�ɐݒ�
// vector.asm�̃x�N�^�A�h���X2���R�����g�A�E�g
//#pragma interrupt intwdti(vect=INTWDTI,bank=RB3)
//void intwdti(void)
//{
//static unsigned char cnt;
//	WDTE = 0xAC;						// WDT�̃J�E���^�N���A
//	if( ++ cnt == 3 )  {					// ��3�b���H
//		cnt = 0;					// �J�E���g�l�̃N���A
//		P5 ^= 0x20;					// LED1�̓_��
//	}
//}
