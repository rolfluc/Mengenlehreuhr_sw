#include "ClockController.h"

ClockController::ClockController(CharliePlexedArray* px0, CharliePlexedArray* px1)
{
	PixelArray0 = px0;
	PixelArray1 = px1;
}

void ClockController::UpdateClock(ClockUpdate clock)
{
	switch (clock)
	{
	case ClockUpdate::Update_s:
		{
			SetSecondsMask();
			Seconds = Seconds + 1;
			if (Seconds >= 60)
			{
				UpdateClock(ClockUpdate::Update_m);
				Seconds = 0;
			}
			break;	
		}
	case ClockUpdate::Update_m:
		{
			Minutes = Minutes + 1;
			if (Minutes >= 60)
			{
				UpdateClock(ClockUpdate::Update_h);
				Minutes = 0;
			}
			SetMinutesMask();
			break;	
		}
	case ClockUpdate::Update_h:
		{
			Hours = Hours + 1;
			if (Hours >= 24)
			{
				Hours = 0;
			}
			SetHoursMask();
			break;
		}
	default:
		break;
	}	
}

void ClockController::SetSecondsMask()
{
	static constexpr uint16_t secondMask = (1 << 5);
	static constexpr uint16_t clearMask = ~(1 << 5);
	if (Seconds & 0x01)
	{
		//PixelArray1->IndicateLED(5);
		pixel1Mask |= secondMask;
	}
	else
	{
		pixel1Mask &= clearMask;
	}
}

void ClockController::SetMinutesMask()
{
	static constexpr uint16_t am50 = (1 << 0);
	static constexpr uint16_t am51 = (1 << 1);
	static constexpr uint16_t rm52 = (1 << 6);
	static constexpr uint16_t am53 = (1 << 7);
	static constexpr uint16_t am54 = (1 << 10);
	static constexpr uint16_t rm55 = (1 << 11);
	static constexpr uint16_t am56 = (1 << 8);
	static constexpr uint16_t am57 = (1 << 9);
	static constexpr uint16_t rm58 = (1 << 2);
	static constexpr uint16_t am59 = (1 << 3);
	static constexpr uint16_t am510 = (1 << 4);
	static constexpr uint16_t allOff = ~(am50 | am51 | rm52 | am53 | am54 | rm55 | am56 | am57 | rm58 | am59 | am510);
	
	static constexpr uint16_t am0 = (1 << 10);
	static constexpr uint16_t am1 = (1 << 11);
	static constexpr uint16_t am2 = (1 << 4);
	static constexpr uint16_t am3 = (1 << 5);
	static constexpr uint16_t lowMinutesOff = ~(am0 | am1 | am2 | am3);
	
	if (Minutes % 5 == 1)
	{
		pixel0Mask |= am0;
	}
	if (Minutes % 5 == 2)
	{
		pixel0Mask |= am1;
	}
	if (Minutes % 5 == 3)
	{
		pixel0Mask |= am2;
	}
	if (Minutes % 5 == 4)
	{
		pixel0Mask |= am3;
	}
	if (Minutes % 5 == 0)
	{
		pixel0Mask &= lowMinutesOff;
	}
	
	if (Minutes > 4)
	{
		pixel1Mask |= am50;
	}
	if (Minutes > 9)
	{
		pixel1Mask |= am51;
	}
	if (Minutes > 14)
	{
		pixel1Mask |= rm52;
	}
	if (Minutes > 19)
	{
		pixel1Mask |= am53;
	}
	if (Minutes > 24)
	{
		pixel1Mask |= am54;
	}
	if (Minutes > 29)
	{
		pixel1Mask |= rm55;
	}
	if (Minutes > 34)
	{
		pixel1Mask |= am56;
	}
	if (Minutes > 39)
	{
		pixel1Mask |= am57;
	}
	if (Minutes > 44)
	{
		pixel1Mask |= rm58;
	}
	if (Minutes > 49)
	{
		pixel1Mask |= am59;
	}
	if (Minutes > 54)
	{
		pixel1Mask |= am510;
	}
	if (Minutes == 0)
	{
		pixel1Mask &= allOff;
	}
}

void ClockController::SetHoursMask()
{
	
	static constexpr uint16_t rh50 = (1 << 0);
	static constexpr uint16_t rh51 = (1 << 1);
	static constexpr uint16_t rh52 = (1 << 2);
	static constexpr uint16_t rh53 = (1 << 3);
	static constexpr uint16_t highHourssOff = ~(rh50 | rh51 | rh52 | rh53);
	
	static constexpr uint16_t rh0 = (1 << 6); 
	static constexpr uint16_t rh1 = (1 << 7); 
	static constexpr uint16_t rh2 = (1 << 8); 
	static constexpr uint16_t rh3 = (1 << 9); 
	static constexpr uint16_t lowHourssOff = ~(rh0 | rh1 | rh2 | rh3);
	
	if (Hours % 5 == 1)
	{
		pixel0Mask |= rh0;
	}
	if (Hours % 5 == 2)
	{
		pixel0Mask |= rh1;
	}
	if (Hours % 5 == 3)
	{
		pixel0Mask |= rh2;
	}
	if (Hours % 5 == 4)
	{
		pixel0Mask |= rh3;
	}
	if (Hours % 5 == 0)
	{
		pixel0Mask &= lowHourssOff;
	}
	
	if (Hours > 4)
	{
		pixel0Mask |= rh50;
	}
	if (Hours > 9)
	{
		pixel0Mask |= rh51;
	}
	if (Hours > 14)
	{
		pixel0Mask |= rh52;
	}
	if (Hours > 19)
	{
		pixel0Mask |= rh53;
	}
	if (Hours == 0)
	{
		pixel0Mask &= highHourssOff;
	}
}

//Strictly for testing / easier mapping.
void ClockController::DisplayLED(LEDS_0 ledbank0, LEDS_1 ledbank1)
{
	switch (ledbank0)
	{
	case LEDS_0::AM50: //C10 H, C11 L, C12 Z, C13 Z - LED0
		{
			PixelArray1->IndicateLED(0);
			break;
		}
	case LEDS_0::AM51: //C10 L, C11 H, C12 Z, C13 Z - LED1
		{
			PixelArray1->IndicateLED(1);
			break;
		}
	case LEDS_0::RM58: //C10 H, C11 Z, C12 L, C13 Z - LED2
		{
			PixelArray1->IndicateLED(2);
			break;
		}
	case LEDS_0::AM59: //C10 L, C11 Z, C12 H, C13 Z - LED3
		{
			PixelArray1->IndicateLED(3);
			break;
		}
	case LEDS_0::AM510: //C10 H, C11 Z, C12 Z, C13 L - LED4
		{
			PixelArray1->IndicateLED(4);
			break;
		}
	case LEDS_0::AS:    //C10 L, C11 Z, C12 Z, C13 H - LED5
		{
			PixelArray1->IndicateLED(5);
			break;
		}
	case LEDS_0::RM52: //C10 Z, C11 H, C12 L, C13 Z - LED6
		{
			PixelArray1->IndicateLED(6);
			break;
		}
	case LEDS_0::AM53: //C10 Z, C11 L, C12 H, C13 Z - LED7
		{
			PixelArray1->IndicateLED(7);
			break;
		}
	case LEDS_0::AM56: //C10 Z, C11 H, C12 Z, C13 L - LED8
		{
			PixelArray1->IndicateLED(8);
			break;
		}
	case LEDS_0::AM57: //C10 Z, C11 L, C12 Z, C13 H - LED9
		{
			PixelArray1->IndicateLED(9);
			break;
		}
	case LEDS_0::AM54: //C10 Z, C11 Z, C12 H, C13 L - LED10
		{
			PixelArray1->IndicateLED(10);
			break;
		}
	case LEDS_0::RM55: //C10 Z, C11 Z, C12 L, C13 H - LED11
		{
			PixelArray1->IndicateLED(11);
			break;
		}
	case LEDS_0::None: // Intentional Fallthrough
	default:
		{
			PixelArray1->IndicateLED(0xff);
			break;
		}
	}

	switch (ledbank1)
	{
	case LEDS_1::RH50: //C00 H, C01 L, C02 Z, C03 Z - LED0
		{
			PixelArray0->IndicateLED(0);
			break;
		}
	case LEDS_1::RH51: //C00 L, C01 H, C02 Z, C03 Z - LED1
		{
			PixelArray0->IndicateLED(1);
			break;
		}
	case LEDS_1::RH52: //C00 H, C01 Z, C02 L, C03 Z - LED2
		{
			PixelArray0->IndicateLED(2);
			break;
		}
	case LEDS_1::RH53: //C00 L, C01 Z, C02 H, C03 Z - LED3
		{
			PixelArray0->IndicateLED(3);
			break;
		}
	case LEDS_1::AM2: //C00 H, C01 Z, C02 Z, C03 L - LED4
		{
			PixelArray0->IndicateLED(4);
			break;
		}
	case LEDS_1::AM3: //C00 L, C01 Z, C02 Z, C03 H - LED5
		{
			PixelArray0->IndicateLED(5);
			break;
		}
	case LEDS_1::RH0: //C00 Z, C01 H, C02 L, C03 Z - LED6
		{
			PixelArray0->IndicateLED(6);
			break;
		}
	case LEDS_1::RH1: //C00 Z, C01 L, C02 H, C03 Z - LED7
		{
			PixelArray0->IndicateLED(7);
			break;
		}
	case LEDS_1::RH2: //C00 Z, C01 H, C02 Z, C03 L - LED8
		{
			PixelArray0->IndicateLED(8);
			break;
		}
	case LEDS_1::RH3: //C00 Z, C01 L, C02 Z, C03 H - LED9
		{
			PixelArray0->IndicateLED(9);
			break;
		}
	case LEDS_1::AM0: //C00 Z, C01 Z, C02 H, C03 L - LED10
		{
			PixelArray0->IndicateLED(10);
			break;
		}
	case LEDS_1::AM1: //C00 Z, C01 Z, C02 L, C03 H - LED11
		{
			PixelArray0->IndicateLED(11);
			break;
		}
	case LEDS_1::None: // Intentional Fallthrough
	default:
		{
			PixelArray0->IndicateLED(0xff);
			break;
		}
	}
}

//Showclock does not handle timing. It is strictly an interface to show one LED at a time for both clocks.
void ClockController::ShowClock()
{
#if 1
	if (pixel0Mask & (1 << maskPointer))
	{
		PixelArray0->IndicateLED(maskPointer);
	}
	else
	{
		PixelArray0->IndicateLED(0xff);
	}
	if (pixel1Mask & (1 << maskPointer))
	{
		PixelArray1->IndicateLED(maskPointer);
	}
	else
	{
		PixelArray1->IndicateLED(0xff);
	}
#else
	if (maskPointer == 0)
	{
		DisplayLED(LEDS_0::AM50, LEDS_1::RH50);
	}
	else if (maskPointer == 1)
	{
		DisplayLED(LEDS_0::AM51, LEDS_1::RH51);	
	}
	else if (maskPointer == 2)
	{
		DisplayLED(LEDS_0::RM52, LEDS_1::RH52);
	}
	else if (maskPointer == 3)
	{
		DisplayLED(LEDS_0::AM53, LEDS_1::RH53);
	}
	else if (maskPointer == 4) 
	{
		DisplayLED(LEDS_0::AM510, LEDS_1::AM2);	
	}
	else if (maskPointer == 5)
	{
		DisplayLED(LEDS_0::AS, LEDS_1::AM3);
	}
	else if (maskPointer == 6)
	{
		DisplayLED(LEDS_0::AM59, LEDS_1::RH0);
	}
	else if (maskPointer == 7)
	{
		DisplayLED(LEDS_0::RM58, LEDS_1::RH1);
	}
	else if (maskPointer == 8)
	{
		DisplayLED(LEDS_0::AM56, LEDS_1::RH2);
	}
	else if (maskPointer == 9)
	{
		DisplayLED(LEDS_0::AM57, LEDS_1::RH3); 
	}
	else if (maskPointer == 10)
	{
		DisplayLED(LEDS_0::AM54, LEDS_1::AM0);
	}
	else if (maskPointer == 11)
	{
		DisplayLED(LEDS_0::RM55, LEDS_1::AM1); 
	}
#endif
	maskPointer = (maskPointer + 1) % ledCnt;
}

ClockController::~ClockController()
{
	
}
