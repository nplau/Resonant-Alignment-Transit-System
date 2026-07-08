/*
 * pwm.c
 *
 *  Created on: Jul 7, 2026
 *      Author: nicolelau
 */

#include "pwm.h"

static TIM_HandleTypeDef *pwm_timer;
static uint32_t pwm_channel = TIM_CHANNEL_1;

void PWM_Init(TIM_HandleTypeDef *htim)
{
    pwm_timer = htim;
}

void PWM_Start(void)
{
    HAL_TIM_PWM_Start(pwm_timer, pwm_channel);
}

void PWM_Stop(void)
{
    HAL_TIM_PWM_Stop(pwm_timer, pwm_channel);
}

void PWM_SetDutyCycle(float duty_percent)
{
    if (duty_percent < 0.0f) duty_percent = 0.0f;
    if (duty_percent > 100.0f) duty_percent = 100.0f;

    uint32_t period = __HAL_TIM_GET_AUTORELOAD(pwm_timer);
    uint32_t pulse = (uint32_t)((duty_percent / 100.0f) * period);

    __HAL_TIM_SET_COMPARE(pwm_timer, pwm_channel, pulse);
}
