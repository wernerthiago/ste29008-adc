/*
 * ADC.h
 *
 *  Created on: Nov 23, 2015
 *      Author: werner
 */

#ifndef Analog_Digital_H_
#define Analog_Digital_H_

class Analog_Digital {
public:
	Analog_Digital();
	virtual ~Analog_Digital();
	void adc_init();
	unsigned long int to_analog(unsigned long int val);
	unsigned long int rms(int repeat);
};

#endif /* ADC_H_ */
