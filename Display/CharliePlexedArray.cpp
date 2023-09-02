#include "CharliePlexedArray.h"
#include <memory>
#define NUMBER_LEDS 12
CharliePlexedArray::CharliePlexedArray(std::vector<GPIO*>* pins)
{
	gpioPins = pins;
}

void CharliePlexedArray::IndicateLED(uint8_t LEDNumber)
{
	gpioPins->at(0)->SetGpioState(GpioState::State_Input);
	gpioPins->at(1)->SetGpioState(GpioState::State_Input);
	gpioPins->at(2)->SetGpioState(GpioState::State_Input);
	gpioPins->at(3)->SetGpioState(GpioState::State_Input);
	switch (LEDNumber)
	{
	case 0:
		{
			//C10 H, C11 L, C12 Z, C13 Z - LED0
			gpioPins->at(0)->SetGpioState(GpioState::State_Output_1);
			gpioPins->at(1)->SetGpioState(GpioState::State_Output_0);
			break;
		}
	case 1:
		{
			//C10 L, C11 H, C12 Z, C13 Z - LED1
			gpioPins->at(0)->SetGpioState(GpioState::State_Output_0);
			gpioPins->at(1)->SetGpioState(GpioState::State_Output_1);
			
			break;
		}
	case 2:
		{
			//C10 H, C11 Z, C12 L, C13 Z - LED2
			gpioPins->at(0)->SetGpioState(GpioState::State_Output_1);
			gpioPins->at(2)->SetGpioState(GpioState::State_Output_0);
			break;
		}
	case 3:
		{
			//C10 L, C11 Z, C12 H, C13 Z - LED3
			gpioPins->at(0)->SetGpioState(GpioState::State_Output_0);
			gpioPins->at(2)->SetGpioState(GpioState::State_Output_1);
			break;
		}
	case 4:
		{
			//C10 H, C11 Z, C12 Z, C13 L - LED4
			gpioPins->at(0)->SetGpioState(GpioState::State_Output_1);
			gpioPins->at(3)->SetGpioState(GpioState::State_Output_0);
			break;
		}
	case 5:
		{
			//C10 L, C11 Z, C12 Z, C13 H - LED5
			gpioPins->at(0)->SetGpioState(GpioState::State_Output_0);
			gpioPins->at(3)->SetGpioState(GpioState::State_Output_1);
			break;
		}
	case 6:
		{
			//C10 Z, C11 H, C12 L, C13 Z - LED6
			gpioPins->at(1)->SetGpioState(GpioState::State_Output_1);
			gpioPins->at(2)->SetGpioState(GpioState::State_Output_0);
			break;
		}
	case 7:
		{
			//C10 Z, C11 L, C12 H, C13 Z - LED7
			gpioPins->at(1)->SetGpioState(GpioState::State_Output_0);
			gpioPins->at(2)->SetGpioState(GpioState::State_Output_1);
			break;
		}
	case 8:
		{
			//C10 Z, C11 H, C12 Z, C13 L - LED8
			gpioPins->at(1)->SetGpioState(GpioState::State_Output_1);
			gpioPins->at(3)->SetGpioState(GpioState::State_Output_0);
			break;
		}
	case 9:
		{
			//C10 Z, C11 L, C12 Z, C13 H - LED9
			gpioPins->at(1)->SetGpioState(GpioState::State_Output_0);
			gpioPins->at(3)->SetGpioState(GpioState::State_Output_1);
			break;
		}
	case 10:
		{
			//C10 Z, C11 Z, C12 H, C13 L - LED10
			gpioPins->at(2)->SetGpioState(GpioState::State_Output_1);
			gpioPins->at(3)->SetGpioState(GpioState::State_Output_0);
			break;
		}
	case 11:
		{
			//C10 Z, C11 Z, C12 L, C13 H - LED11
			gpioPins->at(2)->SetGpioState(GpioState::State_Output_0);
			gpioPins->at(3)->SetGpioState(GpioState::State_Output_1);
			break;
		}
	default:
		{
			break;
		}
	}
}

CharliePlexedArray::~CharliePlexedArray()
{
	
}

