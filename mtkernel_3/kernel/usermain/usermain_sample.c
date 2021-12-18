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
EXPORT ID ObjID[OBJ_KIND_NUM];					// IDテーブル

EXPORT INT usermain( void )
{
T_CTSK t_ctsk;
T_DINT t_dint;
ID objid;

	t_ctsk.tskatr = TA_HLNG | TA_DSNAME;			// タスク属性を設定
	t_ctsk.stksz = 256;					// スタックサイズは256バイト
	t_ctsk.itskpri = 1;					// led0_tskの優先度
#ifdef CLANGSPEC
	t_ctsk.task =  led0_tsk;				// led0_tskの起動アドレス
	strcpy( t_ctsk.dsname, "led0_tsk" );			// led0_tskの名称
#else
	t_ctsk.task =  (FP)led0_tsk;				// led0_tskの起動アドレス
	strcpy( (char*)t_ctsk.dsname, "led0_tsk" );		// led0_tskの名称
#endif /* CLANGSPEC */
	if( (objid = tk_cre_tsk( &t_ctsk )) <= E_OK )		// led0_tskの生成
		goto ERROR;
	ObjID[LED0_TSK] = objid;
	if( tk_sta_tsk( ObjID[LED0_TSK], 0 ) != E_OK )		// led0_tskの起動
		goto ERROR;

	t_ctsk.itskpri = 2;					// led2_tskの優先度
#ifdef CLANGSPEC
	t_ctsk.task = led2_tsk;					// led2_tskの起動アドレス
	strcpy( t_ctsk.dsname, "led2_tsk" );			// led2_tskの名称
#else
	t_ctsk.task = (FP)led2_tsk;				// led2_tskの起動アドレス
	strcpy( (char*)t_ctsk.dsname, "led2_tsk" );		// led2_tskの名称
#endif /* CLANGSPEC */
	if( (objid = tk_cre_tsk( &t_ctsk )) <= E_OK )		// led2_tskの生成
		goto ERROR;
	ObjID[LED2_TSK] = objid;
	if( tk_sta_tsk( ObjID[LED2_TSK], 0 ) != E_OK )		// led2_tskの起動
		goto ERROR;

	t_dint.intatr = TA_HLNG;				// 割込みハンドラ属性
	t_dint.inthdr = sw1_hdr;				// sw1_hdrの起動アドレス
	if( tk_def_int( INTP9, &t_dint ) != E_OK )		// INTP9割込みハンドラの定義
		goto ERROR;

	P1 = 0x80;	PM1 = 0x7F;				// LED0の初期化
	P5 = 0x20;	PM5 = 0xDF;				// LED1の初期化
	P0 = 0x02;	PM0 = 0xFD;				// LED2の初期化

	PU7 = 0x20;						// SW1のプルアップ抵抗ON
	EGN1 = 0x02;  EGP1 = 0x02;				// SW1は両エッジ
	ClearInt( INTP9 );					// INTP9の割込み要求をクリア
	EnableInt( INTP9, 3 );					// INTP9の割込みを許可
	EnableInt( INTWDTI, 0 );				// INTWDTIの割込みを許可

	while( 1 )  tk_slp_tsk(TMO_FEVR);			// 起床待ち
ERROR:
	return 0;
}

EXPORT void led0_tsk(INT stacd, void *exinf)
{
	while( 1 )  {
		tk_dly_tsk( 500 );				// 500msの遅延
		P1 ^= 0x80;					// LED0の点滅
	}
}

EXPORT void led2_tsk(INT stacd, void *exinf)
{
	while( 1 )  {
		tk_slp_tsk( TMO_FEVR );				// 起床待ち(立ち下がりエッジ待ち)
		P0 ^= 0x02;					// LED2の点滅
		while( E_OK == tk_slp_tsk( 10 ) )  ;		// チャタリング除去
		tk_slp_tsk( TMO_FEVR );				// 起床待ち(立ち上がりエッジ待ち)
		while( E_OK == tk_slp_tsk( 10 ) )  ;		// チャタリング除去
	}
}

EXPORT void sw1_hdr(UINT intno)
{
	tk_wup_tsk( ObjID[LED2_TSK] );				// led2_tskの起床
}


// OS管理外割込みハンドラの記述例
// ユーザオプションバイト値を0xFDFFE8に設定
// vector.asmのベクタアドレス2をコメントアウト
//#pragma interrupt intwdti(vect=INTWDTI,bank=RB3)
//void intwdti(void)
//{
//static unsigned char cnt;
//	WDTE = 0xAC;						// WDTのカウンタクリア
//	if( ++ cnt == 3 )  {					// 約3秒か？
//		cnt = 0;					// カウント値のクリア
//		P5 ^= 0x20;					// LED1の点滅
//	}
//}
