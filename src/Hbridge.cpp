/*
 * Hbridge.cpp
 *
 *  Created on: 28. 3. 2017
 *      Author: Michal
 */

#include "Hbridge.h"

H_bridge::H_bridge(uint8_t _EnableLeft, uint8_t _EnableRight, GPIO_TypeDef *_ModeGPIO, uint8_t _ModePin1, uint8_t _ModePin2, uint8_t _ModePin3, uint8_t _ModePin4)
{
	this->EnableLeft = _EnableLeft;
	this->EnableRight = _EnableRight;
	this->ModePin1 = _ModePin1;
	this->ModePin2 = _ModePin2;
	this->ModePin3 = _ModePin3;
	this->ModePin4 = _ModePin4;
	this->ModeGPIO = _ModeGPIO;

	InitGPIO();
	InitPWM();
}

void H_bridge::InitGPIO(void)
{
	if(ModeGPIO == GPIOA)	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	else if(ModeGPIO == GPIOB)	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	else if(ModeGPIO == GPIOC)	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);
	else if(ModeGPIO == GPIOD)	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD,ENABLE);
	else if(ModeGPIO == GPIOE)	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE,ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM3EN,ENABLE);		//TIMER3 clock enable

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = (1 << this->ModePin1) | (1 << this->ModePin2) | (1 << this->ModePin3) | (1 << this->ModePin4);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(ModeGPIO,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = (1 << this->EnableLeft)| (1 << this->EnableRight);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA,this->EnableLeft,GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA,this->EnableRight,GPIO_AF_1);

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
	GPIO_WriteBit(ModeGPIO,(1 << ModePin1),Bit_SET);
	GPIO_WriteBit(ModeGPIO,(1 << ModePin2),Bit_RESET);
	GPIO_WriteBit(ModeGPIO,(1 << ModePin3),Bit_SET);
	GPIO_WriteBit(ModeGPIO,(1 << ModePin4),Bit_RESET);

	this->OCInit.TIM_Pulse=speedL;
	TIM_OC1Init(TIM3,&this->OCInit);

	this->OCInit.TIM_Pulse=speedR;
	TIM_OC1Init(TIM3,&this->OCInit);
}

