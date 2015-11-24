#include "Analog_Digital.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include "util/atomic.h"
#include "Uart.h"
#include "Led.h"
#define TIME 100

int main(){
	Analog_Digital adc;
	Uart u;
	sei();
	int val = 0;

	while(1){
		val = adc.rms(30);
		//if(u.has_data())
			u.put(val);
		_delay_ms(TIME);

	}

	return 0;
}
