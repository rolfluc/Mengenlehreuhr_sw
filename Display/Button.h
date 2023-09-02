#pragma once
#include "GPIO.h"
#include <stdint.h>

enum class ButtonState
{
	State_Unchecked,
	State_Pressed,
	State_NotPressed,
};

class Button
{
public:
	Button(GPIO* pin, uint32_t debouse_ms);
	ButtonState CheckState();
	~Button();
private:
	GPIO* gpio;
	static constexpr uint32_t  holdCheckTime_ms = 500;
	uint32_t debounceTime_ms;
	uint32_t changeTime_ms;
	ButtonState currentState;
};

