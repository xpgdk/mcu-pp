#ifndef _STELLARIS_GPIO_H
#define _STELLARIS_GPIO_H

namespace MCU {

template<unsigned PORT, int PIN>
class StaticStellarisGPIO {
public:
	inline static void Write(int value) {
		HWREG((PORT) + (GPIO_O_DATA + ((PIN_BIT) << 2))) = value << PIN;
	}

	static int Read() {
		return (HWREG((PORT) + (GPIO_O_DATA + ((PIN_BIT) << 2))) >> PIN) & 1;
	}

	static void ConfigureDirection(GPIO::Direction direction) {
		if( direction == GPIO::Output ) {
			MAP_GPIOPinTypeGPIOOutput(PORT, PIN_BIT);
		} else {
			MAP_GPIOPinTypeGPIOInput(PORT, PIN_BIT);
		}
	}

	static void ConfigureInterrupt(GPIO::Trigger trigger) {
#if 0
		LPC_GPIO_TypeDef *ulPort = (LPC_GPIO_TypeDef*)PORT;
		switch(trigger) {
			case GPIO::EdgeRising:
				ulPort->IS &= ~PIN_BIT;
				ulPort->IBE &= ~PIN_BIT;
				ulPort->IEV |= PIN_BIT;
			break;
			case GPIO::EdgeFalling:
				ulPort->IS &= ~PIN_BIT;
				ulPort->IBE &= ~PIN_BIT;
				ulPort->IEV &= ~PIN_BIT;
			break;
			case GPIO::EdgeBoth:
				ulPort->IS &= ~PIN_BIT;
				ulPort->IBE |= PIN_BIT;
			break;
			case GPIO::LevelHigh:
				ulPort->IS |= PIN_BIT;
				ulPort->IBE &= ~PIN_BIT;
				ulPort->IEV |= PIN_BIT;
			break;
			case GPIO::LevelLow:
				ulPort->IS |= PIN_BIT;
				ulPort->IBE &= ~PIN_BIT;
				ulPort->IEV &= ~PIN_BIT;
			break;
		}
#endif
	}

	static void EnableInterrupt() {
#if 0
		LPC_GPIO_TypeDef *ulPort = (LPC_GPIO_TypeDef*)PORT;
		ulPort->IE |= PIN_BIT;
#endif
	}

	static void DisableInterrupt() {
#if 0
		LPC_GPIO_TypeDef *ulPort = (LPC_GPIO_TypeDef*)PORT;
		ulPort->IE &= ~PIN_BIT;
#endif
	}

	static void ClearInterrupt() {
#if 0
		LPC_GPIO_TypeDef *ulPort = (LPC_GPIO_TypeDef*)PORT;
		ulPort->IC |= PIN_BIT;
#endif
	}

private:
	static const int PIN_BIT = (1<<PIN);
};

}

#endif
