/*
 * Accelerometer.h
 *
 *  Created on: 5 Şub 2023
 *      Author: Veli Ertunç
 */

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_
#include <stm32f4xx_hal.h>

/* Read/Write command */
#define READWRITE_CMD                     ((uint8_t)0x80)
/* Multiple byte read/write command */
#define MULTIPLEBYTE_CMD                  ((uint8_t)0x40)


namespace STM32F4Discovery{

	//For LIS3DSH
	class Accelerometer {
		private:
		GPIO_TypeDef* accelPort = GPIOE;
		GPIO_TypeDef* spi1Port = GPIOA;
		uint32_t int1Pin = GPIO_PIN_0;
		uint32_t int2Pin = GPIO_PIN_1;
		uint32_t csPin = GPIO_PIN_3;
		SPI_HandleTypeDef* hSPI;
		const float sensitivity = 0.06;

		void initCSPin() {
			GPIO_InitTypeDef cfg;
			__HAL_RCC_GPIOE_CLK_ENABLE();
			cfg.Pin = csPin;
			cfg.Mode = GPIO_MODE_OUTPUT_PP;
			cfg.Pull = GPIO_NOPULL;
			cfg.Speed = GPIO_SPEED_MEDIUM;
			HAL_GPIO_Init(accelPort, &cfg);

			csHigh();
		}

		void csLow(){ HAL_GPIO_WritePin(accelPort, csPin, GPIO_PIN_RESET); }
		void csHigh(){ HAL_GPIO_WritePin(accelPort, csPin, GPIO_PIN_SET); }

		void initSPI(){
			if (HAL_SPI_GetState(hSPI) == HAL_SPI_STATE_RESET) {
				SPI_InitTypeDef spiCfg;
			    spiCfg.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
			    spiCfg.Direction = SPI_DIRECTION_2LINES;
			    spiCfg.CLKPhase = SPI_PHASE_1EDGE;
			    spiCfg.CLKPolarity = SPI_POLARITY_LOW;
			    spiCfg.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
			    spiCfg.CRCPolynomial = 7;
			    spiCfg.DataSize = SPI_DATASIZE_8BIT;
			    spiCfg.FirstBit = SPI_FIRSTBIT_MSB;
			    spiCfg.NSS = SPI_NSS_SOFT;
			    spiCfg.TIMode = SPI_TIMODE_DISABLED;
			    spiCfg.Mode = SPI_MODE_MASTER;
			    hSPI->Init = spiCfg;

			    //Enable SPI1 and GPIOA clocks
			    __HAL_RCC_SPI1_CLK_ENABLE();
			    __HAL_RCC_GPIOA_CLK_ENABLE();
			    /*
			     * SCK = GPIO_PIN_5
			     * MISO = GPIO_PIN_6
			     * MOSI = GPIO_PIN_7
			     * AF = GPIO_AF5_SPI1
			     */
			    GPIO_InitTypeDef spiGpioCfg;
			    spiGpioCfg.Pin = (GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
			    spiGpioCfg.Mode = GPIO_MODE_AF_PP;
			    spiGpioCfg.Pull = GPIO_PULLDOWN;
			    spiGpioCfg.Speed = GPIO_SPEED_MEDIUM;
			    spiGpioCfg.Alternate = GPIO_AF5_SPI1;
			    HAL_GPIO_Init(spi1Port, &spiGpioCfg);

			    HAL_SPI_Init(hSPI);
			}
		}

		/**
		 * @brief Reads {len} bytes starting from the register at {addr}
		 *
		 * @param addr		: The beginning register address
		 * @param len		: The length of the data which will be read
		 * @return An array of {len} bytes
		 */
		uint8_t* readRegister(uint8_t addr, uint16_t len){
			uint8_t buffer[len];

			addr |= (uint8_t)(READWRITE_CMD);

			if (len>1) {
				addr |= (uint8_t)MULTIPLEBYTE_CMD;
			}

			csLow();
			//Send address which will be written
			uint8_t received=0;
			if (HAL_SPI_TransmitReceive(hSPI, &addr, &received,1, 0x1000) != HAL_OK) {
				HAL_SPI_DeInit(hSPI);
				initSPI();
			}
			uint32_t i=0;
			uint8_t dummy=0x00;
			//Send the data
			for(;len >= 1;i++,len--)
			{
				if (HAL_SPI_TransmitReceive(hSPI, &dummy, &received,1, 0x1000) != HAL_OK) {
					HAL_SPI_DeInit(hSPI);
					initSPI();
				}
				buffer[i]=received;
			}

			csHigh();

			return buffer;
		}

		/**
		 * @brief Writes the buffer with the length {len} to the register at {addr}
		 *
		 * @param buffer	: The buffer which will be written
		 * @param addr		: The beginning register address
		 * @param len		: The length of the data which will be written
		 */
		void writeRegister(uint8_t* buffer, uint8_t addr, uint16_t len){
			if (len>1) {
				addr |= (uint8_t)MULTIPLEBYTE_CMD;
			}

			csLow();
			//Send address which will be written
			uint8_t received=0;
			if (HAL_SPI_TransmitReceive(hSPI, &addr, &received,1, 0x1000) != HAL_OK) {
				HAL_SPI_DeInit(hSPI);
				initSPI();
			}

			//Send the data
			while(len>=1)
			{
				if (HAL_SPI_TransmitReceive(hSPI, buffer, &received,1, 0x1000) != HAL_OK) {
					HAL_SPI_DeInit(hSPI);
					initSPI();
				}
				len--;
				buffer++;
			}
			csHigh();
		}

		/**
		 * @brief Reads the axis with the given low address byte
		 *
		 * @param lowAddr: The lower byte of the address of the axis
		 * @return The calculated angle value
		 */
		float readAxis(uint8_t lowAddr){
			float value = 0.0;
			uint8_t lsb = *readRegister(lowAddr, 1);
			uint8_t msb = *readRegister(lowAddr + 1, 1);
			value = ((msb << 8) + lsb) * sensitivity;
			return value;
		}

		public:
		Accelerometer();
		~Accelerometer();
		void Reset();
		void ConfigureIT();
		float getX();
		float getY();
		float getZ();
	};

}
#endif /* ACCELEROMETER_H_ */
