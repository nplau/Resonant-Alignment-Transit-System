/*
 * pwm.h
 *
 *  Created on: Jul 7, 2026
 *      Author: nicolelau
 */

#ifndef PWM_H
#define PWM_H

#include "main.h"

void PWM_Init(TIM_HandleTypeDef *htim);
void PWM_Start(void);
void PWM_Stop(void);
void PWM_SetDutyCycle(float duty_percent);

#endif /* INC_PWM_H_ */
