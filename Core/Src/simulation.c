/*
 * simulation.c
 *
 *  Created on: Jul 20, 2026
 *      Author: Nicole
 *
 */

#include "simulation.h"


#define DEMO_LENGTH 8


static uint8_t simulation_index = 0;
static DemoScenario currentScenario;

static SystemInputs normalChargingScenario[DEMO_LENGTH] =
{

    /*
     * Step 0:
     * Bus far away
     * System should remain idle
     */
    {
        .busDistance_cm = 200,

        .driverTemperature_C = 25,
        .mcuTemperature_C = 25,

        .powerFactor = 0.0,

        .overCurrent = false,
        .overVoltage = false
    },


    /*
     * Step 1:
     * Bus approaching station
     */
    {
        .busDistance_cm = 100,

        .driverTemperature_C = 25,
        .mcuTemperature_C = 25,

        .powerFactor = 0.0,

        .overCurrent = false,
        .overVoltage = false
    },


    /*
     * Step 2:
     * Precharge region
     */
    {
        .busDistance_cm = 50,

        .driverTemperature_C = 26,
        .mcuTemperature_C = 25,

        .powerFactor = 0.2,

        .overCurrent = false,
        .overVoltage = false
    },


    /*
     * Step 3:
     * Alignment check
     */
    {
        .busDistance_cm = 20,

        .driverTemperature_C = 27,
        .mcuTemperature_C = 26,

        .powerFactor = 0.8,

        .overCurrent = false,
        .overVoltage = false
    },


    /*
     * Step 4:
     * Bus aligned, charging begins
     */
    {
        .busDistance_cm = 10,

        .driverTemperature_C = 30,
        .mcuTemperature_C = 27,

        .powerFactor = 0.98,

        .overCurrent = false,
        .overVoltage = false
    },


    /*
     * Step 5:
     * Stable charging
     */
    {
        .busDistance_cm = 10,

        .driverTemperature_C = 32,
        .mcuTemperature_C = 28,

        .powerFactor = 0.99,

        .overCurrent = false,
        .overVoltage = false
    },


    /*
     * Step 6:
     * Bus leaving alignment margin
     */
    {
        .busDistance_cm = 30,

        .driverTemperature_C = 33,
        .mcuTemperature_C = 29,

        .powerFactor = 0.7,

        .overCurrent = false,
        .overVoltage = false
    },


    /*
     * Step 7:
     * Return to idle
     */
    {
        .busDistance_cm = 200,

        .driverTemperature_C = 25,
        .mcuTemperature_C = 25,

        .powerFactor = 0.0,

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


    currentInput = normalChargingScenario[simulation_index];


    simulation_index++;


    if(simulation_index >= DEMO_LENGTH)
    {
        simulation_index = 0;
    }


    return currentInput;
}
