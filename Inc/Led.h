/*
 * Led.h
 *
 *  Created on: 4 Şub 2023
 *      Author: Veli Ertunç
 */

#ifndef LED_H_
#define LED_H_

#include "stm32f4xx_hal.h"
#include "stm32f407xx.h"

class Led {
	public:

	Led(GPIO_Typedef*, int);

	void TurnOn(void);

	void TurnOff(void);

	void Toggle(void);

	private:
		GPIO_Typedef* _port = NULL;
		int _pin;
		void _enableClock(void) {
			if (!_port) {
				if (_port == GPIOA) {
					__HAL_RCC_GPIOA_CLK_ENABLE();
				} else if (_port == GPIOB) {
					__HAL_RCC_GPIOB_CLK_ENABLE();
				} else if (_port == GPIOC) {
					__HAL_RCC_GPIOC_CLK_ENABLE();
				} else if (_port == GPIOD) {
					__HAL_RCC_GPIOD_CLK_ENABLE();
				} else if (_port == GPIOE) {
					__HAL_RCC_GPIOE_CLK_ENABLE();
				} else if (_port == GPIOG) {
					__HAL_RCC_GPIOG_CLK_ENABLE();
				} else if (_port == GPIOH) {
					__HAL_RCC_GPIOH_CLK_ENABLE();
				} else if (_port == GPIOI) {
					__HAL_RCC_GPIOI_CLK_ENABLE();
				}
			}
		}

		void _disableClock(void) {
			if (!_port) {
				if (_port == GPIOA) {
					__HAL_RCC_GPIOA_CLK_DISABLE();
				} else if (_port == GPIOB) {
					__HAL_RCC_GPIOB_CLK_DISABLE();
				} else if (_port == GPIOC) {
					__HAL_RCC_GPIOC_CLK_DISABLE();
				} else if (_port == GPIOD) {
					__HAL_RCC_GPIOD_CLK_DISABLE();
				} else if (_port == GPIOE) {
					__HAL_RCC_GPIOE_CLK_DISABLE();
				} else if (_port == GPIOG) {
					__HAL_RCC_GPIOG_CLK_DISABLE();
				} else if (_port == GPIOH) {
					__HAL_RCC_GPIOH_CLK_DISABLE();
				} else if (_port == GPIOI) {
					__HAL_RCC_GPIOI_CLK_DISABLE();
				}
			}
		}
};




#endif /* LED_H_ */
