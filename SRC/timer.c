#include "timer.h"
#include "aduc812.h"
#include "common.h"
#include "led.h"

#define MAXBASE 8

volatile unsigned long ms_counter ;

void T2_cnt ( void ) __interrupt(5){ /* 0x2B timer 2 external and overflow */
	ms_counter++;
	TF2 = 0;
}

void InitTimer(void ){
	ms_counter = 0;

	SetVector( 0x202B, ( void *)T2_cnt );

	TL2 = 0x5F;
	//TH2 = 0xFF-0x08;
	TH2 = 0x50;

	//capture/reload bytes of Timer2
	RCAP2L = TL2;
	RCAP2H = TH2;
	//start and capture mod
	T2CON = 0x05;
	leds(T2CON);
	return;
	//Intrrupt Enable Regs
	//Enable Timer2 interrupts and all
	TR2 = 1;
	ET2 = 1;	EA = 1;
	TF2 = 0;


}

unsigned long GetMsCounter (void){
	return ms_counter;
}

unsigned long DTimeMs( unsigned long t0 ){
	return ms_counter - t0;
}

void DelayMs (unsigned long t ){
 	unsigned long target = ms_counter + t;

	while ( target > ms_counter ) {
		leds(T2CON);
	}
}
