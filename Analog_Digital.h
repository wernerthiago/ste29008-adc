/*
 * ADC.h
 *
 *  Created on: Nov 23, 2015
 *      Author: werner
 */

#ifndef Analog_Digital_H_
#define Analog_Digital_H_

#include "Circular_Buffer.h"

class Analog_Digital {
public:
	static const int Buffer_Size = 23;
	Analog_Digital();
	virtual ~Analog_Digital();
	unsigned long int to_analog(unsigned long int val);
	unsigned long int rms(int repeat);
	void interrupt_adc();
private:
	Circular_Buffer<Buffer_Size> buffer;
};

#endif /* ADC_H_ */
