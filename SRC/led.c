#include "aduc812.h"
#include "max.h"
#include "common.h"

//период
const char T = 100
//яркость диодов
char led_st[8];
//текущее состояние t
char ti = 0;

void T0_ISR(void) __interrupt( TF0_VECTOR ){
	char l = 0;
	for (size_t i = 0; i < 8; i++) {
		if(ti < led_st[i]){
			l |= 1 << i;
		}
	}
	write_max(7, l)
	if(ti == T)
		ti = 0;
	else
		t++;
}

void InitLed(){
	SetVector(0x200B, (void *) T0_ISR)

	TH0 = 0xA0;
	TL0 = 0xA0;
	TMOD = 0x10;
	TCON = 0x10;
	ET0 = 1; EA = 1;

}

void led( unsigned char n, unsigned char brightnes ){
    if( n > 7 ) return;
	brightnes = brightnes > 100 ? 100 : brightnes;
    led_st[n] = (brightnes * T) / 100;
}

void leds( unsigned char on ){
	for (size_t i = 0; i < 8; i++) {
		led_st[i] = (on & (1 << i)) ? T : 0
	}
}
