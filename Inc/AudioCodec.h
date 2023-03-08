/*
 * AudioCodec.h
 *
 *  Created on: Mar 8, 2023
 *      Author: Veli Ertunç
 */

#ifndef AUDIOCODEC_H_
#define AUDIOCODEC_H_

#include "stm32f4xx_hal.h"
#include "stm32f407xx.h"

namespace STM32F4Discovery {

	class AudioCodec {
		public:
		AudioCodec();
		~AudioCodec();
		void Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
		uint8_t Read(uint8_t Addr, uint8_t Reg);

		private:
		GPIO_TypeDef* sclSdaPort=GPIOB;
		I2C_HandleTypeDef    I2cHandle;

		void i2c_Init(void)
		{
		  if(HAL_I2C_GetState(&I2cHandle) == HAL_I2C_STATE_RESET)
		  {
		    /* DISCOVERY_I2Cx peripheral configuration */
		    I2cHandle.Init.ClockSpeed = BSP_I2C_SPEED;
		    I2cHandle.Init.DutyCycle = I2C_DUTYCYCLE_2;
		    I2cHandle.Init.OwnAddress1 = 0x33;
		    I2cHandle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
		    I2cHandle.Instance = I2C1;

		    /* Init the I2C */
		    i2c_MspInit();
		    HAL_I2C_Init(&I2cHandle);
		  }
		}

		void i2c_MspInit(void)
		{
		  GPIO_InitTypeDef  GPIO_InitStruct;

		  /* Enable I2C GPIO clocks */
		  __HAL_RCC_GPIOB_CLK_ENABLE();

		  /* DISCOVERY_I2Cx SCL and SDA pins configuration ---------------------------*/
		  GPIO_InitStruct.Pin = DISCOVERY_I2Cx_SCL_PIN | DISCOVERY_I2Cx_SDA_PIN;
		  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		  GPIO_InitStruct.Pull  = GPIO_NOPULL;
		  GPIO_InitStruct.Alternate  = DISCOVERY_I2Cx_SCL_SDA_AF;
		  HAL_GPIO_Init(DISCOVERY_I2Cx_SCL_SDA_GPIO_PORT, &GPIO_InitStruct);

		  /* Enable the DISCOVERY_I2Cx peripheral clock */
		  __HAL_RCC_I2C1_CLK_ENABLE();

		  /* Force the I2C peripheral clock reset */
		  __HAL_RCC_I2C1_FORCE_RESET();

		  /* Release the I2C peripheral clock reset */
		  __HAL_RCC_I2C1_RELEASE_RESET();

		  /* Enable and set I2Cx Interrupt to the highest priority */
		  HAL_NVIC_SetPriority(DISCOVERY_I2Cx_EV_IRQn, 0, 0);
		  HAL_NVIC_EnableIRQ(DISCOVERY_I2Cx_EV_IRQn);

		  /* Enable and set I2Cx Interrupt to the highest priority */
		  HAL_NVIC_SetPriority(DISCOVERY_I2Cx_ER_IRQn, 0, 0);
		  HAL_NVIC_EnableIRQ(DISCOVERY_I2Cx_ER_IRQn);
		}

		/**
		  * @brief  Write a value in a register of the device through BUS.
		  * @param  Addr: Device address on BUS Bus.
		  * @param  Reg: The target register address to write
		  * @param  Value: The target register value to be written
		  * @retval HAL status
		  */
		void i2c_WriteData(uint8_t Addr, uint8_t Reg, uint8_t Value)
		{
		  HAL_StatusTypeDef status = HAL_OK;

		  status = HAL_I2C_Mem_Write(&I2cHandle, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, 0x1000);

		  /* Check the communication status */
		  if(status != HAL_OK)
		  {
		    /* Wait */
		    while(1);
		  }
		}

		uint8_t i2c_ReadData(uint8_t Addr, uint8_t Reg)
		{
			  HAL_StatusTypeDef status = HAL_OK;
			  uint8_t value = 0;

			  status = HAL_I2C_Mem_Read(&I2cHandle, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &value, 1,I2cxTimeout);

			  /* Check the communication status */
			  if(status != HAL_OK)
			  {
			    /* Wait */
			    while(1);
			  }
			  return value;
		}
	};

}  // namespace STM32F4Discovery

#endif /* AUDIOCODEC_H_ */
