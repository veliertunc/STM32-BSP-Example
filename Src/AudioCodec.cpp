/*
 * AudioCodec.cpp
 *
 *  Created on: Mar 8, 2023
 *      Author: Veli Ertunç
 */

#include "AudioCodec.h"
#include "stm32f4xx_hal.h"

using namespace STM32F4Discovery;

AudioCodec::AudioCodec()
{
	GPIO_InitTypeDef cfg;

	__HAL_RCC_GPIOD_CLK_ENABLE();

	cfg.Pin = GPIO_PIN_4;
	cfg.Mode = GPIO_MODE_OUTPUT_PP;
	cfg.Speed = GPIO_SPEED_FAST;
	cfg.Pull  = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &cfg);

	//Init I2C1
	i2c_Init();

	//Pull reset pin to GND
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_Delay(5);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_Delay(5);

}

AudioCodec::~AudioCodec()
{

}

void AudioCodec::Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
	i2c_WriteData(Addr, Reg, Value);
}

uint8_t AudioCodec::Read(uint8_t Addr, uint8_t Reg)
{
	return i2c_ReadData(Addr, Reg);
}
