/*
 * ADC.cpp
 *
 *  Created on: Nov 23, 2015
 *      Author: werner
 */

#include "Analog_Digital.h"
#include "avr/io.h"
#include "avr/interrupt.h"
#include "math.h"
#include "stdlib.h"
#include "Uart.h"

Analog_Digital Analog_Digital::adc;

void operator delete(void * p) {
	free(p);
}

Analog_Digital::Analog_Digital() {
	// TODO Auto-generated constructor stub
    //DIDR0 -> default
    PRR &= ~(1<<PRADC);     //ADC turned on
    //ADMUX -> default
    ADCSRA = 0xAB;          //ADC Enabled, no auto trigger, Interrupt enabled, 128 prescaller
    //ADCSRB -> default in free running mode
}

Analog_Digital::Analog_Digital(Channel channel, FREQ freq, Reference ref, int mode) {
	// TODO Auto-generated constructor stub
	this->reference = 0;
	if(channel == INTERNAL1V1) vout = 1.1;
	else this->vout = 0;
    //DIDR0 -> default
    PRR &= ~(1<<PRADC);     //ADC turned on
    ADMUX = (ref << 6)||(channel);
    ADCSRA = 0xA8;          //10101000
    ADCSRA = (ADCSRA||freq);
    //ADCSRB -> default in free running mode
}

Analog_Digital::~Analog_Digital() {
	// TODO Auto-generated destructor stub
}

unsigned long int Analog_Digital::to_analog(unsigned long int val){
	if(ADIF == 1){
		return (5/1023)/val;
	}else{
		return -1;
	}
}

ISR(ADC_vect){
	Analog_Digital::interrupt_adc();
}

void Analog_Digital::interrupt_adc(){
    int adc_val;
    adc_val = ADC;
    adc.buffer.push(adc_val);
    ADCSRA |= 1<<ADSC;
}

unsigned long int Analog_Digital::rms(int repeat){
	int aux = 0;
	unsigned long accumulated = 0;
	while(aux < repeat){
		int digital_value = OCR0A;
		accumulated = digital_value * digital_value;
		aux++;
	}

	return sqrt(accumulated/repeat);
}
