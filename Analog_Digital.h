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
private:
	static Analog_Digital adc;
	int valor;
	int reference;
	float vout;
public:
	enum FREQ{
		FREQ2 = 0x01,
		FREQ4 = 0x02,
		FREQ8 = 0x03,
		FREQ16 = 0x04,
		FREQ32 = 0x05,
		FREQ64 = 0x06,
		FREQ128 = 0x07,
	};
	enum Channel{
		CHANNEL0 = 0x0,
		CHANNEL1 = 0x1,
		CHANNEL2 = 0x2,
		CHANNEL3 = 0x3,
		CHANNEL4 = 0x4,
		CHANNEL5 = 0x5,
		CHANNEL6 = 0x6,
		CHANNEL7 = 0x7,
		CHANNEL8 = 0x8,
		INTERNAL1V1 = 0xE,
		INTERNALGND = 0xF
	};
	enum Reference{
		AREF = 0x0,
		AVCC = 0x1,
		RESERVED = 0x2,
		A1V1 = 0x3
	};

	static const int Buffer_Size = 23;
	Analog_Digital();
	Analog_Digital(Channel channel, FREQ freq,Reference ref, int mode);
	virtual ~Analog_Digital();
	int get_raw();
	int get_volt();
	int get_ref();
	unsigned long int to_analog(unsigned long int val);
	unsigned long int rms(int repeat);
	static void interrupt_adc();
	Circular_Buffer<Buffer_Size> buffer;
};

#endif /* ADC_H_ */
