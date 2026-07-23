/*
 * simulation.c
 *
 *  Created on: Jul 20, 2026
 *      Author: Nicole
 *
 */


#include "simulation.h"


#define DEMO_LENGTH 10


static uint8_t simulation_index = 0;

static DemoScenario currentScenario;



/*
 * Normal charging scenario
 *
 * This simulates:
 *
 * 1. Bus far away
 * 2. Bus approaching
 * 3. Precharge
 * 4. Alignment check
 * 5. Charging at 0mm
 * 6. Charging at 20mm offset
 * 7. Charging at 40mm offset
 * 8. Misalignment limit exceeded
 * 9. Return to idle
 *
 */


static SystemInputs normalChargingScenario[DEMO_LENGTH] =
{


/*
 * Step 0
 *
 * No bus detected
 *
 */

{
    .busDistance_cm = 200,

    .misalignment_mm = 50,

    .driverTemperature_C = 25,
    .mcuTemperature_C = 25,

    .voltageSample = 0,
    .currentSample = 0,
	.phaseDelay_us = 0,


    .overCurrent = false,
    .overVoltage = false
},



/*
 * Step 1
 *
 * Bus approaching station
 *
 */

{
    .busDistance_cm = 140,

    .misalignment_mm = 30,

    .driverTemperature_C = 25,
    .mcuTemperature_C = 25,

    .voltageSample = 0,
    .currentSample = 0,
	.phaseDelay_us = 0,


    .overCurrent = false,
    .overVoltage = false
},




/*
 * Step 2
 *
 * Precharge begins
 *
 */

{
    .busDistance_cm = 100,

    .misalignment_mm = 30,

    .driverTemperature_C = 26,
    .mcuTemperature_C = 26,

    .voltageSample = 50,
    .currentSample = 5,
	.phaseDelay_us = 0,


    .overCurrent = false,
    .overVoltage = false
},





/*
 * Step 3
 *
 * Alignment check
 *
 */

{
    .busDistance_cm = 60,

    .misalignment_mm = 20,

    .driverTemperature_C = 27,
    .mcuTemperature_C = 26,

    .voltageSample = 100,
    .currentSample = 10,
	.phaseDelay_us = 0.2,


    .overCurrent = false,
    .overVoltage = false
},





/*
 * Step 4
 *
 * Perfect alignment
 *
 * Target capacitance:
 *
 * 19.9nF
 *
 */

{
    .busDistance_cm = 48,

    .misalignment_mm = 0,

    .driverTemperature_C = 30,
    .mcuTemperature_C = 27,

    .voltageSample = 200,
    .currentSample = 20,
	.phaseDelay_us = 0.1,

    .overCurrent = false,
    .overVoltage = false
},





/*
 * Step 5
 *
 * Normal charging
 *
 * 20mm offset
 *
 * Target:
 *
 * 21.7nF
 *
 */

{
    .busDistance_cm = 48,

    .misalignment_mm = 20,

    .driverTemperature_C = 32,
    .mcuTemperature_C = 28,

    .voltageSample = 200,
    .currentSample = 18,
	.phaseDelay_us = 0.4,


    .overCurrent = false,
    .overVoltage = false
},





/*
 * Step 6
 *
 * Larger misalignment
 *
 * 40mm
 *
 * Target:
 *
 * 24.0nF
 *
 */

{
    .busDistance_cm = 48,

    .misalignment_mm = 40,

    .driverTemperature_C = 34,
    .mcuTemperature_C = 29,

    .voltageSample = 200,
    .currentSample = 12,
	.phaseDelay_us = 0.2,


    .overCurrent = false,
    .overVoltage = false
},





/*
 * Step 7
 *
 * Misalignment outside charging margin
 *
 */

{
    .busDistance_cm = 48,

    .misalignment_mm = 50,

    .driverTemperature_C = 35,
    .mcuTemperature_C = 30,

    .voltageSample = 200,
    .currentSample = 8,
	.phaseDelay_us = 0,


    .overCurrent = false,
    .overVoltage = false
},





/*
 * Step 8
 *
 * Fault condition
 *
 */

{
    .busDistance_cm = 48,

    .misalignment_mm = 50,

    .driverTemperature_C = 90,
    .mcuTemperature_C = 80,

    .voltageSample = 250,
    .currentSample = 50,
	.phaseDelay_us = 0,



    .overCurrent = true,
    .overVoltage = false
},





/*
 * Step 9
 *
 * System returns idle
 *
 */

{
    .busDistance_cm = 200,

    .misalignment_mm = 50,

    .driverTemperature_C = 25,
    .mcuTemperature_C = 25,

    .voltageSample = 0,
    .currentSample = 0,
	.phaseDelay_us = 0,

    .overCurrent = false,
    .overVoltage = false
}


};



void Simulation_Init(DemoScenario scenario)
{
    currentScenario = scenario;

    simulation_index = 0;
}




SystemInputs Simulation_GetInputs(void)
{

    SystemInputs currentInput;


    currentInput =
        normalChargingScenario[simulation_index];



    simulation_index++;



    if(simulation_index >= DEMO_LENGTH)
    {
        simulation_index = 0;
    }



    return currentInput;

}
