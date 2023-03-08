/*
 * STM32F4Discovery.h
 *
 *  Created on: Mar 8, 2023
 *      Author: earge-ubuntu
 */

#ifndef STM32F4DISCOVERY_H_
#define STM32F4DISCOVERY_H_
#include <vector>
#include "Led.h"
#include "Accelerometer.h"
#include "AudioCodec.h"

namespace STM32F4Discovery {

	class STM32F4Discovery {
		public:
		STM32F4Discovery()
		{
			leds = new std::vector<Led> {
				Led(GPIO_PIN_12),
				Led(GPIO_PIN_13),
				Led(GPIO_PIN_14),
				Led(GPIO_PIN_15)
			};
			imu = new Accelerometer();
			codec = new AudioCodec();
		}
		~STM32F4Discovery();

		const AudioCodec& getCodec() const {
			return codec;
		}

		const Accelerometer& getIMU() const {
			return imu;
		}

		const std::vector<Led>& getLeds() const {
			return leds;
		}

		private:
		std::vector<Led> leds;
		Accelerometer imu;
		AudioCodec codec;

	};

}  // namespace STM32F4Discovery


#endif /* STM32F4DISCOVERY_H_ */
