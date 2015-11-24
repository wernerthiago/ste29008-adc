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

void operator delete(void * p) {
	free(p);
}

Analog_Digital::Analog_Digital() {
	// TODO Auto-generated constructor stub

}

Analog_Digital::~Analog_Digital() {
	// TODO Auto-generated destructor stub
}

void Analog_Digital::adc_init(){
    DIDR0 = 0x00;           //Digital input disabled on all ADC ports
    PRR &= ~(1<<PRADC);     //ADC turned on
    ADMUX = 0x60;           //AVcc, right adjusted, ADC0 pin
    sei();
    ADCSRA = 0xcF;          //ADC Enabled, no auto trigger, Interrupt enabled, 128 prescaller
}

unsigned long int Analog_Digital::to_analog(unsigned long int val){
	return (5/1023)/val;
}

ISR(ADC_vect){
    int adc_val;
    adc_val = ADCH;

    OCR0A = adc_val;
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
