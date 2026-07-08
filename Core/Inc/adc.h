/*
 * adc.h
 *
 *  Created on: Jul 7, 2026
 *      Author: nicolelau
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "main.h"

void ADC_Module_Init(ADC_HandleTypeDef *hadc);
uint32_t ADC_ReadRaw(void);
float ADC_ReadVoltage(void);

#endif /* INC_ADC_H_ */
