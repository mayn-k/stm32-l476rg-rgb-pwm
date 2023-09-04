/*
 * hw_478_driver.c
 *
 *  Created on: Sep 4, 2023
 *      Author: github.com/mayn-k
 */
#include "hw_478_driver.h"
#include "main.h"


uint8_t lcg_seed = 1;
const uint8_t lcg_multiplier = 166;
const uint8_t lcg_increment = 101;
const uint8_t lcg_modulus = 255;


void RGB_LED_INIT(void){
	__HAL_RCC_GPIOA_CLK_ENABLE(); // PA0 : RED LED, PA1 : GREEN LED
	__HAL_RCC_GPIOB_CLK_ENABLE(); // PB10 : BLUE LED

	GPIOA->MODER &= ~((GPIO_MODER_MODE0_Msk) | (GPIO_MODER_MODE1_Msk));
	GPIOB->MODER &= ~GPIO_MODER_MODE10_Msk;

	GPIOA->MODER |= ((GPIO_MODER_MODE0_1) | (GPIO_MODER_MODE1_1));
	GPIOB->MODER |= GPIO_MODER_MODE10_1;

	GPIOA->AFR[0] |= ((GPIO_AFRL_AFSEL0_0) | (GPIO_AFRL_AFSEL1_0));
	GPIOB->AFR[1] |= GPIO_AFRH_AFSEL10_0;
}


void RGB_LED_ON(uint8_t R, uint8_t G, uint8_t B){
	TIM2->CCR1 = R - 1;
	TIM2->CCR2 = G - 1;
	TIM2->CCR3 = B - 1;
}


void RGB_TIM_PWM_INIT(void){
	__HAL_RCC_TIM2_CLK_ENABLE();

	TIM2->PSC = 0;
	TIM2->ARR = 255 - 1;

	TIM2->CCR1 = 255 - 1; // Default R value
	TIM2->CCR2 = 232 - 1;  // Default G value
	TIM2->CCR3 = 23 - 1; // Default B value


	TIM2->CCMR1 |= ((TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1) | (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1));
	TIM2->CCMR2 |= (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1);


	TIM2->CCMR1 &= ~(TIM_CCMR1_CC1S | TIM_CCMR1_CC2S);
	TIM2->CCMR2 &= ~(TIM_CCMR2_CC3S);

	TIM2->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P | TIM_CCER_CC3P);


	TIM2->CCMR1 |= TIM_CCMR1_OC1PE | TIM_CCMR1_OC2PE;
	TIM2->CCMR2 |= TIM_CCMR2_OC3PE;

	TIM2->CR1 |= TIM_CR1_ARPE;

	TIM2->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E;
	TIM2->CR1 |= TIM_CR1_CEN;
}


uint8_t RANDOM_0_TO_255(void){
    lcg_seed = (lcg_seed * lcg_multiplier + lcg_increment) % lcg_modulus;
    return lcg_seed;
}

