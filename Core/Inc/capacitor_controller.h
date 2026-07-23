/*
 * capacitor_controller.h
 *
 *  Created on: Jul 22, 2026
 *      Author: nicolelau
 */

#ifndef CAPACITOR_CONTROLLER_H
#define CAPACITOR_CONTROLLER_H

#include <stdint.h>


float CalculateSwitchCapacitance(uint8_t mask);

uint8_t FindBestCapacitorMask(float targetCapacitance);

float CalculateTargetCapacitance(float misalignment_mm);


#endif /* INC_CAPACITOR_CONTROLLER_H_ */
