/*
 * Hbridge.cpp
 *
 *  Created on: 28. 3. 2017
 *      Author: Michal
 */

#include "Hbridge.h"

H_bridge::H_bridge(uint16_t _EnableLeft, uint16_t _EnableRight, GPIO_TypeDef *_ModeGPIO, uint16_t _ModePin1, uint16_t _ModePin2, uint16_t _ModePin3, uint16_t _ModePin4)
{
	this->EnableLeft = _EnableLeft;
	this->EnableRight = _EnableRight;
	this->ModePin1 = _ModePin1;
	this->ModePin2 = _ModePin2;
	this->ModePin3 = _ModePin3;
	this->ModePin4 = _ModePin4;
	this->ModeGPIO = _ModeGPIO;

	InitGPIO();

}

void H_bridge::InitGPIO(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = this->ModePin1 | this->ModePin2 | this->ModePin3 | this->ModePin4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(ModeGPIO,&GPIO_InitStructure);

	//TODO: treba dorobit vseobecne
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource4,GPIO_AF_2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_2);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4| GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void H_bridge::InitPWM(void)
{
	//TODO: cele prerobit
	TIM_TimeBaseInitTypeDef TimeBase;

    uint16_t prescaler = (uint16_t) ((32000000 / 1000000) - 1); // Shooting for 1 MHz, (1us)

    uint32_t pwm_period = 20000;

	TimeBase.TIM_ClockDivision=0;
	TimeBase.TIM_CounterMode=TIM_CounterMode_Up;
	TimeBase.TIM_Period=pwm_period-1;
	TimeBase.TIM_Prescaler=prescaler;
	TIM_TimeBaseInit(TIM3,&TimeBase);

	OCInit.TIM_OCMode=TIM_OCMode_PWM1;
	OCInit.TIM_OCPolarity=TIM_OCPolarity_High;
	OCInit.TIM_OutputState=TIM_OutputState_Enable;
	OCInit.TIM_Pulse=1000;
	TIM_OC2Init(TIM3,&OCInit);
	TIM_OC1Init(TIM3,&OCInit);

	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM3,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
}

void H_bridge::Move(uint16_t speedL, uint16_t speedR)
{
	this->OCInit.TIM_Pulse=speedL;
	TIM_OC1Init(TIM3,&this->OCInit);

	this->OCInit.TIM_Pulse=speedR;
	TIM_OC1Init(TIM3,&this->OCInit);
}

