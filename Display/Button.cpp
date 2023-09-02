#include "Button.h"

Button::Button(GPIO* pin, uint32_t debouse_ms)
	: debounceTime_ms(debouse_ms)
	, changeTime_ms(0)
{
	gpio = pin;
	gpio->SetPull(GpioPull::Pull_Up);
	gpio->SetGpioState(GpioState::State_Input);
	currentState = ButtonState::State_NotPressed;
}

ButtonState Button::CheckState()
{
	ButtonState checkState = ButtonState::State_Unchecked;
	GpioReadVal read = gpio->ReadInput();
	if (HAL_GetTick() < changeTime_ms + debounceTime_ms)
	{
		return ButtonState::State_Unchecked;
	}
	
	switch (currentState)
	{
	case ButtonState::State_Pressed:
		{ 
			if (read == GpioReadVal::Read_High)
			{
				checkState = ButtonState::State_NotPressed;
				changeTime_ms = HAL_GetTick();
			}
			break;
		}
	case ButtonState::State_NotPressed:
		{
			if (read == GpioReadVal::Read_Low)
			{
				checkState = ButtonState::State_Pressed;
				changeTime_ms = HAL_GetTick();
			}
			break;
		}
	default:
		//Unknown
		break;
	}
	return checkState;
}

Button::~Button()
{
	
}