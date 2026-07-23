/*
 * system_types.h
 *
 *  Created on: Jul 20, 2026
 *      Author: nicolelau
 */

#ifndef SYSTEM_TYPES_H
#define SYSTEM_TYPES_H

#include <stdbool.h>
#include <stdint.h>

/*=============================
 * Demo Scenarios
 *=============================*/

typedef enum
{
    DEMO_NORMAL_CHARGING = 0,
    DEMO_BUS_OUTSIDE_MARGIN,
    DEMO_OVERTEMPERATURE,
    DEMO_DRIVER_FAULT

} DemoScenario;

/*=============================
 * System States
 *=============================*/

typedef enum
{
    STATE_IDLE = 0,
    STATE_PRECHARGE,
    STATE_ALIGNMENT_CHECK,
    STATE_CHARGING,
    STATE_FAULT,
    STATE_SHUTDOWN

} SystemState;

/*=============================
 * System Inputs
 *=============================*/

typedef struct
{
    float busDistance_cm;

    float driverTemperature_C;
    float mcuTemperature_C;

    float voltageSample;
    float currentSample;

    float powerFactor;

} SystemInputs;

/*=============================
 * System Outputs
 *=============================*/

typedef struct
{
    bool pwmEnabled;

    bool chargingEnabled;

    uint8_t capacitorMask;

} SystemOutputs;

#endif /* INC_SYSTEM_TYPES_H_ */
