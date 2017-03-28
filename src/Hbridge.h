/*
 * Hbridge.h
 *
 *  Created on: 28. 3. 2017
 *      Author: Michal
 */

#ifndef HBRIDGE_H_
#define HBRIDGE_H_

#include "stm32f0xx.h"


class H_bridge {
private:
	uint16_t EnableLeft;
	uint16_t EnableRight;
	uint16_t ModePin1;
	uint16_t ModePin2;
	uint16_t ModePin3;
	uint16_t ModePin4;
	GPIO_TypeDef *ModeGPIO;
	TIM_OCInitTypeDef OCInit;

public:
	H_bridge(uint16_t _EnableLeft, uint16_t _EnableRight, GPIO_TypeDef *_ModeGPIO, uint16_t _ModePin1, uint16_t _ModePin2, uint16_t _ModePin3, uint16_t _ModePin4);
	void InitGPIO(void);
	void InitPWM(void);
	void Move(uint16_t speedL, uint16_t speedR);
};

#endif /* HBRIDGE_H_ */
