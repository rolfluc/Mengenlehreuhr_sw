#include <stm32f0xx_hal.h>
#include <stm32_hal_legacy.h>
#include <GPIO.h>
#include "CharliePlexedArray.h"
#include "ClockController.h"
#include "Button.h"
#include <vector>
#include <memory>

static GPIO CH00(GPIO_PIN_7, GPIOA);
static GPIO CH01(GPIO_PIN_5, GPIOA);
static GPIO CH02(GPIO_PIN_6, GPIOA);
static GPIO CH03(GPIO_PIN_2, GPIOA);
static GPIO CH10(GPIO_PIN_3, GPIOA);
static GPIO CH11(GPIO_PIN_4, GPIOA);
static GPIO CH12(GPIO_PIN_1, GPIOA);
static GPIO CH13(GPIO_PIN_0, GPIOA);
static GPIO SW_M(GPIO_PIN_0, GPIOF);
static GPIO SW_H(GPIO_PIN_1, GPIOF);

static std::vector<GPIO*> set0Pins {&CH00, &CH01, &CH02, &CH03};
static std::vector<GPIO*> set1Pins {&CH10, &CH11, &CH12, &CH13};

static CharliePlexedArray set0(&set0Pins);
static CharliePlexedArray set1(&set1Pins);
static ClockController clock(&set0, &set1);
static Button button_m(&SW_M, 200);
static Button button_h(&SW_H, 200);
static uint64_t time_ms = 1;

#ifdef __cplusplus
extern "C"
#endif
void SysTick_Handler(void)
{
	
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
	time_ms += 1;
	if (time_ms % 1000 == 0) {
		clock.UpdateClock(ClockUpdate::Update_s);
	}
}

void HandleButtons()
{
	ButtonState buttonM = button_m.CheckState();
	ButtonState buttonH = button_h.CheckState();
	
	if (buttonM == ButtonState::State_Pressed)
	{
		clock.UpdateClock(ClockUpdate::Update_m);
	}
	
	if (buttonH == ButtonState::State_Pressed)
	{
		clock.UpdateClock(ClockUpdate::Update_h);
	}
}

static const uint32_t ButtonCheckTime_ms = 250;

int main(void)
{
	static uint32_t lastButtonCheck = 0;
	HAL_Init();

	__GPIOA_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();
	__GPIOF_CLK_ENABLE();

	for (;;)
	{
		//~1000hz
		clock.ShowClock();
		
		if (lastButtonCheck + ButtonCheckTime_ms > HAL_GetTick())
		{
			HandleButtons();
			lastButtonCheck = HAL_GetTick();
		}
	}
}
