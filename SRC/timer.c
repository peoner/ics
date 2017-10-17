#include "timer.h"
##include "aduc812.h"


unsigned long ms_counter ;

void T2_ISR ( void ) __interrupt(5){
	ms_counter++;
}

void InitTimer(void ){
	ms_counter = 0 ;
	SetVector( 0x202B, ( void ∗)T2_ISR );
	TH2 = 0xFF − 0x03 ;
	TL2 = 0xFF − 0x98 ;
	RCAP2L = TL2;
	RCAP2H = TH2;
	T2CON = 0x05;
	ET2 = 1;
	EA = 1;
}

unsigned long GetMsCounter (void){
	return ms_counter;
}

unsigned long DTimeMs( unsigned long t0 ){
	return ms_counter − t0;
}

void DelayMs (unsigned long t ){
 	unsigned longtarget = ms_counter + t;
	while ( target > ms_counter ) {}
}
