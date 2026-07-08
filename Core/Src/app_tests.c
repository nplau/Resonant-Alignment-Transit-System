/*
 * app_tests.c
 *
 *  Created on: Jul 7, 2026
 *      Author: nicolelau
 */

#include "main.h"
#include "app_tests.h"
#include "test_config.h"
#include "debug.h"
#include "pwm.h"
#include "adc.h"

void AppTests_Run(void)
{
#ifdef TEST_DEBUG
    Debug_Print("Debug test running...\r\n");
    HAL_Delay(1000);
#endif

#ifdef TEST_PWM
    PWM_SetDutyCycle(25.0f);
    Debug_Print("PWM Duty: 25%%\r\n");
    HAL_Delay(1000);

    PWM_SetDutyCycle(50.0f);
    Debug_Print("PWM Duty: 50%%\r\n");
    HAL_Delay(1000);

    PWM_SetDutyCycle(75.0f);
    Debug_Print("PWM Duty: 75%%\r\n");
    HAL_Delay(1000);
#endif

#ifdef TEST_ADC
    float voltage = ADC_ReadVoltage();
    Debug_Print("ADC Voltage: %.2f V\r\n", voltage);
    HAL_Delay(1000);
#endif
}
