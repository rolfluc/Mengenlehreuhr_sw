#pragma once
#include "CharliePlexedArray.h"
enum class ClockUpdate
{
	Update_s,
	Update_m,
	Update_h,
};

enum class LEDS_0
{
	AM50,  //C10 H, C11 L, C12 Z, C13 Z
	AM51,  //C10 L, C11 H, C12 Z, C13 Z
	RM52,  //C10 Z, C11 H, C12 L, C13 Z 
	AM53,  //C10 Z, C11 L, C12 H, C13 Z
	AM54,  //C10 Z, C11 Z, C12 H, C13 L
	RM55,  //C10 Z, C11 Z, C12 L, C13 H
	AM56,  //C10 Z, C11 H, C12 Z, C13 L
	AM57,  //C10 Z, C11 L, C12 Z, C13 H
	RM58,  //C10 H, C11 Z, C12 L, C13 Z
	AM59,  //C10 L, C11 Z, C12 H, C13 Z
	AM510, //C10 H, C11 Z, C12 Z, C13 L
	AS,    //C10 L, C11 Z, C12 Z, C13 H
	None
};

enum class LEDS_1
{
	RH50, //C00 H, C01 L, C02 Z, C03 Z
	RH51, //C00 L, C01 H, C02 Z, C03 Z 
	RH52, //C00 H, C01 Z, C02 L, C03 Z 
	RH53, //C00 L, C01 Z, C02 H, C03 Z 
	RH0,  //C00 Z, C01 H, C02 L, C03 Z
	RH1,  //C00 Z, C01 L, C02 H, C03 Z 
	AM0,  //C00 Z, C01 Z, C02 H, C03 L
	AM1,  //C00 Z, C01 Z, C02 L, C03 H 
	RH2,  //C00 Z, C01 H, C02 Z, C03 L
	RH3,  //C00 Z, C01 L, C02 Z, C03 H 
	AM2,  //C00 H, C01 Z, C02 Z, C03 L
	AM3,  //C00 L, C01 Z, C02 Z, C03 H
	None
};

class ClockController
{
public:
	ClockController(CharliePlexedArray*, CharliePlexedArray*);
	void UpdateClock(ClockUpdate);
	void ShowClock();
	~ClockController();
private:
	void DisplayLED(LEDS_0, LEDS_1);
	void SetSecondsMask();
	void SetMinutesMask();
	void SetHoursMask();
	uint8_t Hours = 0;
	uint8_t Minutes = 0;
	uint8_t Seconds = 0;
	CharliePlexedArray* PixelArray0;
	CharliePlexedArray* PixelArray1;
	
	uint16_t pixel0Mask = 0;
	uint16_t pixel1Mask = 0;
	static constexpr uint8_t ledCnt = 12;
	uint8_t maskPointer = 0;
};

