/*
 * simulation.h
 *
 *  Created on: Jul 20, 2026
 *      Author: nicolelau
 */

#ifndef SIMULATION_H
#define SIMULATION_H

#include "system_types.h"

void Simulation_Init(DemoScenario scenario);

SystemInputs Simulation_GetInputs(void);

#endif /* INC_SIMULATION_H_ */
