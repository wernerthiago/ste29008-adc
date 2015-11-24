#include "Analog_Digital.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#define TIME 100

int main(){
	Analog_Digital adc;
	adc.adc_init();
	int val = 0;
	//LED
	PINB = 0x23;
	DDRB = 0x24;
	PORTB = 0x80;

	while(true){
		val = adc.rms(30);
		if(val == 100) PORTB &= ~_BV(PORTB5);
		else PORTB |= _BV(PORTB5);
		_delay_ms(TIME);
	}

	return 0;
}
