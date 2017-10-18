#include "counter.h"
#include "aduc812.h"
#include "common.h"



void InitCounter(void ){

	TMOD |= ~T0_GATE |  T0_CT|	T0_M0 | ~T1_M1;
	TH0 = 0x0;
	TL0 = 0x0;

	//Intrrupt Enable Regs
	//Enable Timer1 interrupts
	ET0 = 1;
	//Enable all
	EA = 1;
	//start Timer1
	TR0 = 1;
}

unsigned long GetCounterVal (void){
	return (TH0 << 8);
}
