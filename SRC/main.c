#include "aduc812.h"
#include "led.h"
#include "max.h"
#include "timer.h"
#include "common.h"


unsigned char dip()
{
	return read_max(EXT_LO);
}

char wrkSt;



#define LAB_DIP_VALUE 0x55
#define MAX_TICKS 6
void main( void ){

	SetVector(0x200B, (void *) T0_ISR)

	InitLed();
	InitTimer();


	while(1){
		if()
	}
}
