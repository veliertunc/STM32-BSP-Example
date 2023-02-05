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

namespace STM32F4Discovery{
	class Led {
		public:

		Led(uint32_t);

		void On(void);

		void Off(void);

		void Toggle(void);

		private:
			GPIO_TypeDef* _port = GPIOD;
			uint32_t _pin;
	};
}
#endif /* LED_H_ */
