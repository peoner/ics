#include "counter.h"
#include "aduc812.h"
#include "common.h"



void InitCounter(void ){
	TMOD &= 0xF0;
	TMOD |=  (T0_CT) |	(T0_M0);
	TH0 = 0x0;
	TL0 = 0x0;
	TCON |= 0x04;
	//Intrrupt Enable Regs
	//Enable Timer1 interrupts
	TR0 = 1;
	ET0 = 1;
	//Enable all
	EA = 1;
	//start Timer0

}

unsigned long GetCounterVal (void){
	return (TH0 << 8) | (TL0);
}
