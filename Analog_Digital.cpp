/*
 * ADC.cpp
 *
 *  Created on: Nov 23, 2015
 *      Author: werner
 */

#include "Analog_Digital.h"
#include "avr/io.h"
#include "avr/interrupt.h"
#include "util/delay.h"
#include "math.h"
#include "stdlib.h"
#include "Uart.h"

Analog_Digital * Analog_Digital::adc;

void operator delete(void * p) {
	free(p);
}

Analog_Digital::Analog_Digital() {
	// TODO Auto-generated constructor stub
	sei();
	ADMUX = 0x40;
	ADCSRA = 0xEF;

	adc = this;
}

Analog_Digital::Analog_Digital(Channel channel, FREQ freq, Reference ref) {
	// TODO Auto-generated constructor stub
	this->reference = 0;
	if(channel == INTERNAL1V1) vout = 1.1;
	else this->vout = 0;
	//DIDR0 -> default
	ADMUX = (ref << 6)||(channel);
	ADCSRA = 0xA8;          //10101000
	ADCSRA = (ADCSRA||freq);
	//ADCSRB -> default in free running mode

	adc = this;
}

Analog_Digital::~Analog_Digital() {
	// TODO Auto-generated destructor stub
}

unsigned int Analog_Digital::to_analog(unsigned int val){
	return ((long)5000*(long)val)/1023;
}

unsigned int Analog_Digital::to_vref(unsigned int val){
	if(ADIF == 1){
		this->reference = (this->vout * 1023)/val;
		return this->reference;
	}else{
		return -1;
	}
}

ISR(ADC_vect){
	Analog_Digital::interrupt_adc();
}

void Analog_Digital::interrupt_adc(){
	adc->buffer.push(ADC);
}

volatile int Analog_Digital::available() {
	return this->buffer.available();
}

unsigned int Analog_Digital::rms(int repeat){
	Uart u;
	int aux = 0;
	unsigned long int accumulated = 0;
	unsigned long int val = 0;
	while(aux < repeat){
		val = this->buffer.pop();
		accumulated += val * val;
		aux++;
	}
	return sqrt(accumulated/repeat);
}

double  Analog_Digital::mylog(double x)
{
	int l = -1; // mylog2(0) will return -1

	while (x != 0u){
		x = (unsigned) x >> 1u;
		++l;
	}
	return l*0.693147181;
}


unsigned int Analog_Digital::temperature(unsigned int measure){
	int R2 = 10000;
	float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
	unsigned long R1 = R2*(1023.0/measure - 1.0);
	float aux = mylog(R1);
	return (1.0/(c1+c2*aux+c3*aux*aux*aux))-273.15-8;
}

