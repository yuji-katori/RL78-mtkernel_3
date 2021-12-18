#include <string.h>
#include <tk/tkernel.h>
#include "iodefine.h"

IMPORT void out_lvlled(unsigned short data);
IMPORT void out_7segled(unsigned char segment,unsigned char digit);
EXPORT void ad_tsk(INT stacd, void *exinf);
EXPORT void led_tsk(INT stacd, void *exinf);
EXPORT void intad_hdr(UINT dintno);
EXPORT void led_cyc(void *exinf);
EXPORT void sw_cyc(void *exinf);

typedef enum { AD_TSK, LED_TSK, LED_CYC, SW_CYC, AD_FLG, LED_MBF, OBJ_KIND_NUM } OBJ_KIND;
EXPORT ID ObjID[OBJ_KIND_NUM];					// ID Table

/************************************************************************************************/
/*	usermain										*/
/************************************************************************************************/
EXPORT INT usermain( void )
{
ID objid;
T_CTSK t_ctsk;							// Task Parameter Packet
T_DINT t_dint;							// Interrupt Handler Parameter Packet
T_CCYC t_ccyc;							// Cyclic Handler Parameter Packet
T_CFLG t_cflg;							// Event Flag Parameter Packet
T_CMBF t_cmbf;							// Message Buffer Parameter Packet
	t_ctsk.tskatr = TA_HLNG | TA_DSNAME;			// Set Attribute
	t_ctsk.stksz = 256;					// Set Stack Size
	t_ctsk.itskpri = 2;					// Set Priority of ad_tsk
#ifdef CLANGSPEC
	t_ctsk.task =  ad_tsk;					// Set Start Address of ad_tsk
	strcpy( t_ctsk.dsname, "ad_tsk" );			// Set Name of ad_tsk
#else
	t_ctsk.task =  (FP)ad_tsk;				// Set Start Address of ad_tsk
	strcpy( (char*)t_ctsk.dsname, "ad_tsk" );		// Set Name of ad_tsk
#endif /* CLANGSPEC */
	if( (objid = tk_cre_tsk( &t_ctsk )) <= E_OK )		// Create ad_tsk
		goto ERROR;
	ObjID[AD_TSK] = objid;					// Set ID of ad_tsk

	t_ctsk.itskpri = 1;					// Set Priority of led_tsk
#ifdef CLANGSPEC
	t_ctsk.task = led_tsk;					// Set Start Address of led_tsk
	strcpy( t_ctsk.dsname, "led_tsk" );			// Set Name of led_tsk
#else
	t_ctsk.task = (FP)led_tsk;				// Set Start Address of led_tsk
	strcpy( (char*)t_ctsk.dsname, "led_tsk" );		// Set Name of led_tsk
#endif /* CLANGSPEC */
	if( (objid = tk_cre_tsk( &t_ctsk )) <= E_OK )		// Create led_tsk
		goto ERROR;
	ObjID[LED_TSK] = objid;					// Set ID of led_tsk

	t_dint.intatr = TA_HLNG;				// Set Attribute
#ifdef CLANGSPEC
	t_dint.inthdr = intad_hdr;				// Set Start Address of intad_hdr
#else
	t_dint.inthdr = (FP)intad_hdr;				// Set Start Address of intad_hdr
#endif /* CLANGSPEC */
	if( tk_def_int( INTAD, &t_dint ) != E_OK )		// Define intad_hdr
		goto ERROR;

	t_ccyc.cycatr = TA_HLNG | TA_STA | TA_DSNAME;		// Set Attribute
	t_ccyc.cyctim = 5;					// Set Cycle Time
	t_ccyc.cycphs = 500;					// Set Cycle Phase
#ifdef CLANGSPEC
	t_ccyc.cychdr = led_cyc;				// Set Start Address of led_cyc
	strcpy( t_ccyc.dsname, "led_cyc" );			// Set Name of led_cyc
#else
	t_ccyc.cychdr = (FP)led_cyc;				// Set Start Address of led_cyc
	strcpy( (char*)t_ccyc.dsname, "led_cyc" );		// Set Name of led_cyc
#endif /* CLANGSPEC */
	if( (objid = tk_cre_cyc( &t_ccyc )) <= E_OK )		// Create led_cyc
		goto ERROR;
	ObjID[LED_CYC] = objid;					// Set ID of led_cyc

	t_ccyc.cyctim = 20;					// Set Cycle Time
	t_ccyc.cycphs = 500;					// Set Cycle Phase
#ifdef CLANGSPEC
	t_ccyc.cychdr = sw_cyc;					// Set Start Address of sw_cyc
	strcpy( t_ccyc.dsname, "sw_cyc" );			// Set Name of sw_cyc
#else
	t_ccyc.cychdr = (FP)sw_cyc;				// Set Start Address of sw_cyc
	strcpy( (char*)t_ccyc.dsname, "sw_cyc" );		// Set Name of sw_cyc
#endif /* CLANGSPEC */
	if( (objid = tk_cre_cyc( &t_ccyc )) <= E_OK )		// Create sw_cyc
		goto ERROR;
	ObjID[SW_CYC] = objid;					// Set ID of led_cyc

	t_cflg.flgatr = TA_TFIFO | TA_WSGL | TA_DSNAME;		// Set Attribute
	t_cflg.iflgptn = 0;					// Set Initial Pattern
#ifdef CLANGSPEC
	strcpy( t_cflg.dsname, "ad_flg" );			// Set Name of ad_flg
#else
	strcpy( (char*)t_cflg.dsname, "ad_flg" );		// Set Name of ad_flg
#endif /* CLANGSPEC */
	if( (objid = tk_cre_flg( &t_cflg )) <= E_OK )		// Create ad_flg
		goto ERROR;
	ObjID[AD_FLG] = objid;					// Set ID of ad_flg

	t_cmbf.mbfatr = TA_TFIFO | TA_DSNAME;			// Set Attribute
	t_cmbf.bufsz = 0;					// Set Buffer Size
	t_cmbf.maxmsz = 4;					// Set Maximun Size
#ifdef CLANGSPEC
	strcpy( t_cmbf.dsname, "led_mbf" );			// Set Name of led_mbf
#else
	strcpy( (char*)t_cmbf.dsname, "led_mbf" );		// Set Name of led_mbf
#endif /* CLANGSPEC */
	if( (objid = tk_cre_mbf( &t_cmbf )) <= E_OK )		// Create led_mbf
		goto ERROR;
	ObjID[LED_MBF] = objid;					// Set ID of led_mbf

	PM7 = 0xF8;						// LED1-3 is Output
	PM1 = 0xD9;						// LED4,5,Clock is Output
	PM3 = 0xFD;						// Latch is Output
	PMC0 = 0xF7;						// P03 is Digital Pin
	PM0 = 0xE7;						// LED6,DataPin is Output

	ADCEN = 1;						// Clock Supply to A/D
	ADPC = 0x02;						// Only A0 Analog Pin
	ADM0 = 0x01;						// Enable A/D Convertor
	ADM1 = 0x20;						// One Shot Mode
	EnableInt( INTAD, 3 );					// Enable INTAD

	tk_sta_tsk( ObjID[AD_TSK], 0 );				// Start ad_tsk
	tk_sta_tsk( ObjID[LED_TSK], 0 );			// Start led_tsk
	
	while( 1 )  tk_slp_tsk( TMO_FEVR );
ERROR:
	return 0;
}

/************************************************************************************************/
/*	INTAD Interrupt Handler									*/
/************************************************************************************************/
EXPORT void intad_hdr(UINT dintno)
{
	tk_set_flg( ObjID[AD_FLG], ADCR+1 );			// set A/D result
}

/************************************************************************************************/
/*	A/D Task										*/
/************************************************************************************************/
EXPORT void ad_tsk(INT stacd, void *exinf)
{
static const unsigned char seg[] =				// Segment Pattern
	{ 0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09 };
unsigned short volume;						// Volume
unsigned char i, data[4];					// Loop Counter, Segment Data
UINT flgptn;							// Return Parameter
	while( 1 ) {
		ADCS = 1;					// A/D Start
		tk_wai_flg( ObjID[AD_FLG], 0x0001, TWF_ORW | TWF_CLR, &flgptn, TMO_FEVR );
								// Wait A/D End
		volume = flgptn - 1;				// Set A/D Result
		out_lvlled( volume >>= 6 );			// Output Level LED
		for( i=0 ; i<4 ; i++ ) {			// Digit Loop
			data[i] = seg[volume%10];		// Set Segment Line
			if( !( volume/=10 ) )			// Set Next Analize
				break;				// Zero Find ?
		}
		while( ++i<4 )					// Digit Loop
			data[i] = 0xFF;				// Clear Segment Line
		tk_snd_mbf( ObjID[LED_MBF], data, sizeof(data), TMO_FEVR );
	}							// Send Segment Data
}

/************************************************************************************************/
/*	LED Task										*/
/************************************************************************************************/
EXPORT void led_tsk(INT stacd, void *exinf)
{
static const unsigned char dig[] = { 0x10, 0x20, 0x40, 0x80 };	// Digit Data
unsigned char i, seg[4];					// Loop Counter, Segment Data
	while( 1 ) {
		for( i=0 ; i<4 ; i++ ) {			// Digit Loop
			out_7segled( seg[i], dig[i] );		// Output 7 Segment LED
			tk_slp_tsk( TMO_FEVR );			// Wait 5ms
		}
		tk_rcv_mbf( ObjID[LED_MBF], seg, TMO_POL );	// Receive Segment
	}
}

/************************************************************************************************/
/*	LED Cyclic Hander									*/
/************************************************************************************************/
EXPORT void led_cyc(void *exinf)				// 5ms Cyclic
{
	tk_wup_tsk( ObjID[LED_TSK] );				// Wakeup to led_tsk
}

/************************************************************************************************/
/*	SW Cyclic Hander									*/
/************************************************************************************************/
EXPORT void sw_cyc(void *exinf)					// 20ms Cyclic
{
static unsigned char sw;					// Switch Value
	sw = (sw << 1) + (P2 & 0x02);				// Set Switch Value
	if( ( sw & 0x06 ) == 0x04 )				// Push Switch ?
		ADMK ^= 1;					// Change INTAD Status
}

/************************************************************************************************/
/*	KeyStudio Driver Sample									*/
/************************************************************************************************/
void out_lvlled(unsigned short data)
{
union { __bitf_T bit; unsigned char byte; } work;	// Bit Field Variable
	work.byte = ~(data>>2);				// Output data Result
	P0_bit.no3 = work.bit.no2;			// LED6(2^4 of data)
	P1_bit.no1 = work.bit.no3;			// LED5(2^5 of data)
	P1_bit.no2 = work.bit.no4;			// LED4(2^6 of data)
	P7_bit.no2 = work.bit.no5;			// LED3(2^7 of data)
	P7_bit.no1 = work.bit.no6;			// LED2(2^8 of data)
	P7_bit.no0 = work.bit.no7;			// LED1(2^9 of data)
}

void out_7segled(unsigned char segment,unsigned char digit)
{
unsigned char i;					// Loop Counter, Segment Data
	for( i=0 ; i<8 ; i++ )  {			// Segment Loop
		P0_bit.no4 = segment;			// Set Segment Line
		P1_bit.no5 = 1;				// Clock is High
		P1_bit.no5 = 0;				// Clock is Low
		segment >>= 1;				// Shift Segment Data
	}
	for( i=0 ; i<8 ; i++ )  {			// Segment Loop
		P0_bit.no4 = digit;			// Set Digit Data
		P1_bit.no5 = 1;				// Clock Pin is High
		P1_bit.no5 = 0;				// Clock Pin is Low
		digit >>= 1;				// Shift Digit Data
	}
	P3_bit.no1 = 1;					// Latch Pin is HIGH
	P3_bit.no1 = 0;					// Latch Pin is LOW
}