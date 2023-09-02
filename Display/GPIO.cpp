#include "GPIO.h"
GPIO::GPIO(uint16_t pinNumber, GPIO_TypeDef* gpioPort)
{
	currentState = GpioState::State_Uninit;
	pinNum = pinNumber;
	port = gpioPort;
	settings.Mode = MODE_INPUT;
	settings.Pin = pinNum;
	settings.Pull = GPIO_NOPULL;
	settings.Speed = GPIO_SPEED_LOW;
}

void GPIO::SetGpioState(GpioState state)
{
	if (currentState == GpioState::State_Input  && state != GpioState::State_Input)
	{
		settings.Mode = MODE_OUTPUT;
		HAL_GPIO_Init(port, &settings);
		
		if (state == GpioState::State_Output_0)
		{
			HAL_GPIO_WritePin(port, pinNum, GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(port, pinNum, GPIO_PIN_SET);
		}
		currentState = state;
	}
	// If currnetly an output, and we're setting an output, set the pin state
	else if(currentState != GpioState::State_Input && state != GpioState::State_Input)  
	{
		if (state == GpioState::State_Output_0)
		{
			HAL_GPIO_WritePin(port, pinNum, GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(port, pinNum, GPIO_PIN_SET);
		}
		currentState = state;
	}
	// If currently an output and don't want to be, set as input
	else if(currentState != GpioState::State_Input && state == GpioState::State_Input)
	{
		settings.Mode = MODE_INPUT;
		HAL_GPIO_Init(port, &settings);
		currentState = state;
	}
}

void GPIO::SetPull(GpioPull pull)
{
	switch (pull)
	{
	case GpioPull::Pull_Up:
		{
			settings.Pull = GPIO_PULLUP;
			break;
		}
	case GpioPull::Pull_Down:
		{
			settings.Pull = GPIO_PULLDOWN;
			break;
		}
	case GpioPull::Pull_None:
		{
			settings.Pull = GPIO_NOPULL;
			break;
		}
	default:
		settings.Pull = GPIO_NOPULL;
		break;
	}
}

GpioReadVal GPIO::ReadInput()
{
	if (currentState != GpioState::State_Input)
	{
		return GpioReadVal::Read_Output;
	}
	
	GPIO_PinState read = HAL_GPIO_ReadPin(port, pinNum);
	return read == GPIO_PIN_SET ? GpioReadVal::Read_High : GpioReadVal::Read_Low;
}

GPIO::~GPIO()
{
	
}