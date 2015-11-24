/*
 * Circular_Buffer.h
 *
 *  Created on: Nov 14, 2015
 *      Author: arliones
 */

#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_

#include <avr/io.h>

template <int SIZE>
class Circular_Buffer {
public:
    Circular_Buffer() : head(0), tail(0) {};
	virtual ~Circular_Buffer() {}

	void push(uint16_t data) {
	    buffer[head++] = data;
	    if(head == SIZE) head = 0;
	}

	uint16_t pop() {
	    uint16_t ret = buffer[tail++];
	    if(tail == SIZE) tail = 0;
	    return ret;
	}

	bool has_data() { return head != tail; }

	const int max_len() const {
		return SIZE;
	}

private:
    uint16_t buffer[SIZE];
    int head;
    int tail;
};

#endif /* BUFFER_H_ */
