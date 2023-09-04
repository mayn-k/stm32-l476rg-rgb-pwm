/*
 * hw_478_driver.h
 *
 *  Created on: Sep 4, 2023
 *      Author: github.com/mayn-k
 */

#ifndef INC_HW_478_DRIVER_H_
#define INC_HW_478_DRIVER_H_

#include <stdint.h>

void RGB_LED_INIT(void);
void RGB_LED_ON(uint8_t, uint8_t, uint8_t);
void RGB_TIM_PWM_INIT(void);
uint8_t RANDOM_0_TO_255(void);


#endif /* INC_HW_478_DRIVER_H_ */
