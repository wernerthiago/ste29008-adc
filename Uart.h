/*
 * Uart.h
 *
 *  Created on: 13 de nov de 2015
 *      Author: aluno
 */

#ifndef UART_H_
#define UART_H_

#include "Circular_Buffer.h"

class Uart {
private:
    static Uart uart;
	static const int Buffer_Size = 23;

public:
	Uart();
	bool has_data();
	void put(uint8_t c);
	uint8_t get();

	static void rx_interrupt_handler();
	static void empty_interrupt_handler();
	static void interruptoff();
	static void interrupton();

	Circular_Buffer<Buffer_Size> rx;
	Circular_Buffer<Buffer_Size> tx;
};

#endif /* UART_H_ */
