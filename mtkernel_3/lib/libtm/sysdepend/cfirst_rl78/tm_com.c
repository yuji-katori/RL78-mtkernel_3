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
		while( SSR00L & 0x20)  ;	// 送信バッファの空き待ち
		SDR00 = buf[i];			// 送信バッファにライト
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
		while( !(SSR01L & 0x25) )  ;	// 何かの受信待ち
		if( SSR01L & 0x20)  {		// 受信バッファにデータがあるか？
			buf[i] = SDR01;		// 受信バッファにリード
			continue;
		}
		if( SSR01L & 0x04 )		// フレーミングエラーか？
			SIR01L = 0x04;		// フラグをクリア
		if( SSR01L & 0x01 )		// オーバーフローエラーか？
			SIR01L = 0x01;		// フラグをクリア
		break;
	}
#endif /* USE_COM_C_FIRST */
}


EXPORT	void	tm_com_init(void)
{
#if USE_COM_C_FIRST
	SAU0EN = 1; 			// シリアルアレイユニット0をイネーブル
	SPS0 = 0x0011;			// fMCK=fCLK/2(32MHz/2)
	SMR00 = 0x0022;			// UARTモード,CK00,送信
	SCR00 = 0x8097;			// 送信,8ビット,パリティなし,1ストップビット,LSBファースト
	SDR00 = 0x8800;			// 115200bps
	SOE0L_bit.no0 = 1;		// 出力許可
	SMR01 = 0x0122;			// UARTモード,CK00,受信
	SCR01 = 0x4097;			// 受信,8ビット,パリティなし,1ストップビット,LSBファースト
	SDR01 = 0x8800;			// 115200bps
	NFEN0_bit.no0 = 1;		// RxD0端子のノイズフィルタをON
	PM5_bit.no1 = 0;		// TxD0端子を出力モードに設定
	P5_bit.no1 = 1;			// TxD0出力を有効化
	PM5_bit.no0 = 1;		// RxD0端子を入力モードに設定
      	SS0L = 0x03;			// 送信受信動作許可
#endif /* USE_COM_C_FIRST */
}