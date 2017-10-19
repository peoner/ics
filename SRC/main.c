#include "aduc812.h"
#include "led.h"
#include "max.h"
#include "timer.h"
#include "counter.h"
#include "common.h"

char mod;


void IE1_ISR() __interrupt( IE1_VECTOR ){
	mod = ~mod;
}

#define LAB_DIP_VALUE 0x55
#define MAX_TICKS 6
void main( ){
    
    char i = 0, n = 0, br = 0;
    char inc = 0, leds_old = 0, new_led;
    
    mod = 0;
    mod = ~mod;
    
	InitLed();
	InitTimer();
	InitCounter();
	
    SetVector(0x2013, (void *) IE1_ISR);
    EX1 = 1;
    
	i = 0;

	while(1){
		if(mod){
	        for(n = 0; n < 8; n++){
	            if(n < 4)
	                led(n, br);
	            else
	                led(n, 100 - br);
            }

	        if (!inc)
	            br += 100 / 10;
	        else
	            br -= 100 / 10;
	        DelayMs(10);
			
			if(i == 9){
	        	inc = ~inc;
				i = 0;
			}else
				i++;
		} else{
			leds(GetCounterVal());
			DelayMs(1);
		}
	}
}
