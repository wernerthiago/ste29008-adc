#include "Analog_Digital.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include "util/atomic.h"
#include "Uart.h"
#define TIME 100

int main(){
	Analog_Digital adc;
	Uart u;
	int val = 0;
	PINB = 0x23;
	DDRB = 0x24;
	PORTB = 0x80;
	while(1){
		val = adc.available();
		if(val >= 20) {
			PORTB |= _BV(PORTB5);
			val = adc.rms(20);
			u.put(val);
		}
		_delay_ms(TIME);
	}

	return 0;
}
