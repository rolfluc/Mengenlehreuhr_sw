#pragma once
#include <stdint.h>
#include "stm32f0xx_hal.h"
enum class GpioState
{
	State_Output_0,
	State_Output_1,
	State_Input,
	State_Uninit,
};

enum class GpioPull
{
	Pull_Up,
	Pull_Down,
	Pull_None
};

enum class GpioReadVal
{
	Read_High,
	Read_Low,
	Read_Output,
};

class GPIO
{
public:
	GPIO(uint16_t pinNumber, GPIO_TypeDef* gpioPort);
	void SetGpioState(GpioState state);
	void SetPull(GpioPull pull);
	GpioReadVal ReadInput();
	~GPIO();
private:
	GpioState currentState;
	uint16_t pinNum;
	GPIO_TypeDef* port;
	GPIO_InitTypeDef settings;
};

