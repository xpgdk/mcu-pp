#include <mcu++/fifo.hpp>

#include <stdint.h>
#include <iostream>

void assertTrue(bool val, std::string msg) {
	if( !val ) {
		std::cerr << msg << " failed" << std::endl;
	}
}

void assertEqual(uint8_t val, uint8_t exp, std::string msg) {
	if( val != exp) {
		std::cerr << msg << " failed" << std::endl;
	}
}

void assertEqual(uint16_t val, uint16_t exp, std::string msg) {
	if( val != exp) {
		std::cerr << msg << " failed" << std::endl;
	}
}

#define assertFalse(v,m) assertTrue(!(v),m)

int
main(int argc, char *argv[]) {
	MCU::Fifo<3,uint8_t> fifo;

	assertTrue(fifo.push(1), "push(1)");
	assertEqual(fifo.getUsed(), 1, "Used 1");
	assertTrue(fifo.push(2), "push(2)");
	assertEqual(fifo.getUsed(), 2, "Used 2");
	assertTrue(fifo.push(3), "push(3)");
	assertEqual(fifo.getUsed(), 3, "Used 3");
	assertFalse(fifo.push(4), "push(4)");
	assertEqual(fifo.getUsed(), 3, "Used 4");

	uint8_t v;
	assertTrue(fifo.pop(&v), "1. pop");
	assertEqual(v, 1, "1. pop value");
	assertEqual(fifo.getUsed(), 2, "Used 5");

	assertTrue(fifo.pop(&v), "2. pop");
	assertEqual(v, 2, "2. pop value");
	assertEqual(fifo.getUsed(), 1, "Used 6");

	assertTrue(fifo.pop(&v), "3. pop");
	assertEqual(v, 3, "3. pop value");
	assertEqual(fifo.getUsed(), 0, "Used 7");

	assertFalse(fifo.pop(&v), "4. pop");

	assertTrue(fifo.push(42), "push(42)");
	assertTrue(fifo.pop(&v), "4. pop");
	assertEqual(v, 42, "4. pop value");
}
