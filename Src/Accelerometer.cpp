/*
 * Accelerometer.cpp
 *
 *  Created on: 5 Şub 2023
 *      Author: Veli Ertunç
 */
#include "stm32f4xx_hal.h"
#include "Accelerometer.h"

using namespace STM32F4Discovery;

Accelerometer::Accelerometer(){
	//1. Initialize CS port and pin
	initCSPin();
	//2. Init SPI
	initSPI();
	//3. Set power mode and axes enable in CTRL REG 4 (addr: 0x20)
	//Datarate = 100Hz, XYZ enabled
	uint8_t ctrl = (uint8_t)(0x60 | 0x07);
	writeRegister(&ctrl, 0x20, 1);
	//4. Set CTRL5 register(addr : 0x24) value
	/* 4 wire serial, Selftest = Normal, Scale = 2g,
	* Anti-aliasing filter bandwidth= 800Hz
	*/
	ctrl = (uint8_t)(0x00 | 0x00 | 0x00| 0x00);
	writeRegister(&ctrl, 0x24, 1);
}

Accelerometer::~Accelerometer(){

}

/**
 * @brief Resets LIS3DSH by setting bit 7 in CTRL 6 register
 */
void Accelerometer::Reset(){

	uint8_t ctrl6Reg = *readRegister(0x25, 1);
	ctrl6Reg |= 0x80;
	writeRegister(&ctrl6Reg, 0x25, 1);
}

void Accelerometer::ConfigureIT(){

}

/**
 * @brief Gets X angle in human readable format
 *
 * @return The (raw X value * sensitivity)
 */
float Accelerometer::getX(){
	return readAxis(0x28);
}

/**
 * @brief Gets Y angle in human readable format
 *
 * @return The (raw Y value * sensitivity)
 */

float Accelerometer::getY(){
	return readAxis(0x2A);
}

/**
 * @brief Gets Z angle in human readable format
 *
 * @return The (raw Z value * sensitivity)
 */
float Accelerometer::getZ(){
	return readAxis(0x2C);
}


