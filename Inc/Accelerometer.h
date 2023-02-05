/*
 * Accelerometer.h
 *
 *  Created on: 5 Şub 2023
 *      Author: Veli Ertunç
 */

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_


namespace STM32F4Discovery{
	class Accelerometer {
		private:
		GPIO_TypeDef* _port = GPIOE;
		uint16_t int1Pin = GPIO_PIN_0;
		uint16_t int2Pin = GPIO_PIN_1;
		uint16_t csPin = GPIO_PIN_3;
		public:
	};

}
#endif /* ACCELEROMETER_H_ */
