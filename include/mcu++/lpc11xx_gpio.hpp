#ifndef _MCU_LPC1XX_GPIO_HPP
#define _MCU_LPC1XX_GPIO_HPP

namespace MCU {

template<unsigned PORT, int PIN>
class StaticLPCGPIO {
public:
	inline static void Write(int value) {
		LPC_GPIO_TypeDef *ulPort = (LPC_GPIO_TypeDef*)PORT;
		ulPort->MASKED_ACCESS[PIN_BIT] = value << PIN;
	}

	static int Read() {
		LPC_GPIO_TypeDef *ulPort = (LPC_GPIO_TypeDef*)PORT;
		return (ulPort->MASKED_ACCESS[PIN_BIT] >> PIN) & 0x01;
	}

	static void ConfigureDirection(GPIO::Direction direction) {
		LPC_GPIO_TypeDef *ulPort = (LPC_GPIO_TypeDef*)PORT;
		if( direction == GPIO::Output ) {
			ulPort->DIR |= PIN_BIT;
		} else {
			ulPort->DIR &= ~PIN_BIT;
		}
	}

	static void ConfigureInterrupt(GPIO::Trigger trigger) {
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
	}

	static void EnableInterrupt() {
		LPC_GPIO_TypeDef *ulPort = (LPC_GPIO_TypeDef*)PORT;
		ulPort->IE |= PIN_BIT;
	}

	static void DisableInterrupt() {
		LPC_GPIO_TypeDef *ulPort = (LPC_GPIO_TypeDef*)PORT;
		ulPort->IE &= ~PIN_BIT;
	}

	static void ClearInterrupt() {
		LPC_GPIO_TypeDef *ulPort = (LPC_GPIO_TypeDef*)PORT;
		ulPort->IC |= PIN_BIT;
	}

	static LPC_GPIO_TypeDef* getPort() {
		return (LPC_GPIO_TypeDef*)PORT;
	}

private:
	static const int PIN_BIT = (1<<PIN);
};

}

#endif
