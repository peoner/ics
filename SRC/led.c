#include "aduc812.h"
#include "max.h"
#include "common.h"

//период
const unsigned char T = 16;
//яркость диодов
unsigned char led_st[8];
//текущее состояние t
unsigned char ti = 1;

const unsigned char ledON[] = {1, 2, 4, 8, 16, 32, 64, 128};
unsigned char l = 0;
unsigned char i = 0;

void T1_ISR(void) __interrupt( TF1_VECTOR ){

	for (l = 0, i =0; i < 8; i++) {
		if(ti & led_st[i]){
			l |= ledON[i];
		}
	}
	write_max(SV, l);
	ti = ti << 1;
    if(ti == 64)
        ti = 1;
}

void InitLed(){
	SetVector(0x201B, (void *) T1_ISR);
	TMOD &= 0x0F;
	/*T1_GATE = 0; T1_CT = 0;
	T1_M0 = 0; T1_M1 = 1;*/

	TMOD |= ~T1_GATE | ~ T1_CT|	~T1_M0 |T1_M1;

	TH1 = 0xF0;
	TL1 = 0xF0;

	//Intrrupt Enable Regs
	//Enable Timer1 interrupts
	ET1 = 1;
	//Enable all
	EA = 1;
	//start Timer1
	TR1 = 1;
}

void led2( unsigned char n, unsigned char brightnes ){
    if( n > 7 ) return;
	brightnes = brightnes > 100 ? 100 : brightnes;
    led_st[n] = (brightnes * T) / 100;
}

void led( unsigned char n, unsigned char brightnes ){
    if( n > 7 ) return;
    led_st[n] = brightnes;
}

void leds( unsigned char on ){
    char i = 0;
	for (; i < 8; i++) {
		led_st[i] = (on & (1 << i)) ? T : 0;
	}
}
