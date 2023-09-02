#pragma once
#include "GPIO.h"
#include <vector>
#include <stdint.h>
#include <memory>

static constexpr uint8_t MAX_LEDS_PER_ARRAY = 12;
class CharliePlexedArray
{
public:
	CharliePlexedArray(std::vector<GPIO*>* pins);
	void IndicateLED(uint8_t LEDNumber);
	~CharliePlexedArray();
private:
	uint8_t NumberOfLEDs;
	std::vector<GPIO*>* gpioPins;
};

