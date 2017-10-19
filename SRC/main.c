#include "aduc812.h"
#include "led.h"
#include "max.h"
#include "timer.h"
#include "counter.h"
#include "common.h"

char mod = 1;

/*
void IE1_ISR() __interrupt( IE1_VECTOR ){
	mod = ~mod;
}*/

#define LAB_DIP_VALUE 0x55
#define MAX_TICKS 6
void main( ){

    char i = 0, n = 0, br = 0;
    char inc = 1, leds_old = 0, new_led;

	InitLed();
	InitTimer();
	//InitCounter();
	//SetVector(0x2013, (void *) IE1_ISR);

	i = 0;
	leds(leds_old);
	T2CON = 0x05;
	while(1){
		if(mod){
	        for(n = 0; n < 8; n++)
	            if(n < 4)
	                led(n, br);
	            else
	                led(n, 100 - br);

	        if (inc)
	            br += 100 / 10;
	        else
	            br -= 100 / 10;
			leds(0xf0);
	        DelayMs(100);
			leds(0x0f);
			return;

			if(i == 9){
	        	inc = ~inc;
				i = 0;
			}else
				i++;
		} else{
			new_led = GetCounterVal();
			if(new_led != leds_old){
				leds_old = new_led;
				leds(leds_old);
			}
			DelayMs(100);
		}
	}
}
