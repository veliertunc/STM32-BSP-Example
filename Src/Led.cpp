/*
 * Led.cpp
 *
 *  Created on: 4 Şub 2023
 *      Author: Veli Ertunç
 */
#include "stm32f4xx_hal.h"
#include "Led.h"

using namespace STM32F4Discovery;

Led::Led(uint32_t pin){
	GPIO_InitTypeDef initCfg;
	_pin = pin;

	//Enable the peripheral clock
	__HAL_RCC_GPIOD_CLK_ENABLE();

	initCfg.Pin = pin;
	initCfg.Mode = GPIO_MODE_OUTPUT_PP;
	initCfg.Pull = GPIO_PULLUP;
	initCfg.Speed = GPIO_SPEED_FAST;

	//Configure the pin
	HAL_GPIO_Init(_port, &initCfg);

	//Reset the pin
	Off();
}

void Led::On(void)
{
	HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_SET);
}

void Led::Off(void)
{
	HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_RESET);
}

void Led::Toggle(void)
{
	HAL_GPIO_TogglePin(_port, _pin);
}

