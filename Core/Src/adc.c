/*
 * adc.c
 *
 *  Created on: Jul 7, 2026
 *      Author: nicolelau
 */


#include "adc.h"

static ADC_HandleTypeDef *adc_handle;

void ADC_Module_Init(ADC_HandleTypeDef *hadc)
{
    adc_handle = hadc;
}

uint32_t ADC_ReadRaw(void)
{
    HAL_ADC_Start(adc_handle);
    HAL_ADC_PollForConversion(adc_handle, HAL_MAX_DELAY);
    uint32_t value = HAL_ADC_GetValue(adc_handle);
    HAL_ADC_Stop(adc_handle);

    return value;
}

float ADC_ReadVoltage(void)
{
    uint32_t raw = ADC_ReadRaw();
    return (raw / 4095.0f) * 3.3f;
}
