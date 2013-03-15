#ifndef _MCU_FIFO_HPP
#define _MCU_FIFO_HPP

#include <stdint.h>

namespace MCU {

template<uint16_t Size, typename Type>
class Fifo {
public:
	Fifo() 
		: pushIndex(0),
		  popIndex(0),
		  used(0)
	{
	}

	inline bool push(Type element) {
		if( used >= Size ) {
			return false;
		}
		buffer[pushIndex] = element;
		pushIndex = (pushIndex + 1) % Size;
		used++;
		return true;
	}

	inline bool pop(Type *element) {
		if( used == 0 ) {
			return false;
		}
		*element = buffer[popIndex];
		popIndex = (popIndex + 1) % Size;
		used--;
		return true;
	}

	inline uint16_t getUsed() {
		return used;
	}

	inline void clear() {
		used = 0;
	}

private:
	Type 		buffer[Size];
	uint16_t	pushIndex;
	uint16_t	popIndex;
	uint16_t	used;
};

}

#endif
