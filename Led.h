/*
 * led.h
 *
 *  Created on: Nov 24, 2015
 *      Author: werner
 */

#ifndef LED_H_
#define LED_H_
#include "avr/interrupt.h"

class Led{
public:
	Led(){
		PINB = 0x23;
		DDRB = 0x24;
		PORTB = 0x80;
	}
	virtual ~Led();
	void on(){
		PORTB &= ~_BV(PORTB5);
	}

	void off(){
		PORTB |= _BV(PORTB5);
	}

};



#endif /* LED_H_ */
