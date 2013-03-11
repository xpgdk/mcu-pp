#ifndef _MCU_GPIO_HPP
#define _MCU_GPIO_HPP

namespace MCU {

class GPIO {
public:
	typedef enum Direction {
		Input, Output
	} Direction;

	typedef enum Trigger {
		EdgeRising,
		EdgeFalling,
		EdgeBoth,
		LevelHigh,
		LevelLow
	} Trigger;
};

}
#endif
