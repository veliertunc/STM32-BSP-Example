/*
 * Led.cpp
 *
 *  Created on: 4 Şub 2023
 *      Author: Veli Ertunç
 */

#include "Led.h"

Led::Led(GPIO_Typedef* port = GPIOD, int pin){
	GPIO_InitTypeDef initCfg;
	_port = port;
	_pin = pin;
	_enableClock();
	initCfg.Pin = __pin;
	initCfg.Mode = GPIO_MODE_OUTPUT_PP;
	initCfg.Pull = GPIO_PULLUP;
	initCfg.Speed = GPIO_SPEED_FAST;

	HAL_GPIO_Init(_port, initCfg);

	HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_RESET);

	TurnOff();
}

void Led::TurnOn(void)
{
	HAL_GPIO_WritePin(_port,_pin, GPIO_PIN_SET);
}

void Led::TurnOff(void)
{
	HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_RESET);
}

void Led::Toggle(void)
{
	HAL_GPIO_TogglePin(_port, _pin);
}

