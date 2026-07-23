/*
 * state_machine.c
 *
 *  Created on: Jul 22, 2026
 *      Author: nicolelau
 */


#include "state_machine.h"
#include "capacitor_controller.h"

#include "simulation.h"
#include "config.h"
#include "debug.h"
#include "pwm.h"
#include "power_factor.h"

static SystemState currentState;

void StateMachine_Init(void)
{
    currentState = STATE_IDLE;

    Simulation_Init(DEMO_NORMAL_CHARGING);

    Debug_Print("\r\n=====================================\r\n");
    Debug_Print(" Resonant Alignment Transit System\r\n");
    Debug_Print(" Firmware Demonstration\r\n");
    Debug_Print("=====================================\r\n");
}

void StateMachine_Update(void)
{
    SystemInputs inputs;

    inputs = Simulation_GetInputs();

    float powerFactor;

    powerFactor = CalculatePowerFactor(inputs.phaseDelay_us);

    uint8_t capacitorMask;
    float targetCapacitance;

    targetCapacitance =
        CalculateTargetCapacitance(inputs.misalignment_mm);


    capacitorMask =
        FindBestCapacitorMask(targetCapacitance);


    /*---------------- Safety Monitoring ----------------*/

    if (inputs.currentSample > MAX_INPUT_CURRENT_A)
    {
    	Debug_Print("\r\n[FAULT]\r\n");
    	Debug_Print("Overcurrent Fault\r\n");
    	currentState = STATE_FAULT;
    }

    else if (inputs.voltageSample > MAX_INPUT_VOLTAGE_V)
    {
    	Debug_Print("\r\n[FAULT]\r\n");
    	Debug_Print("Overvoltage Fault\r\n");
    	currentState = STATE_FAULT;
    }

    else if (inputs.driverTemperature_C > MAX_DRIVER_TEMP_C)
    {
    	Debug_Print("\r\n[FAULT]\r\n");
    	Debug_Print("Driver Overheating\r\n");
    	currentState = STATE_FAULT;
    }

    else if (inputs.mcuTemperature_C > MAX_MCU_TEMP_C)
    {
    	Debug_Print("\r\n[FAULT]\r\n");
    	Debug_Print("MCU Overheating\r\n");
    	currentState = STATE_FAULT;
    }

    switch(currentState)
    {

    case STATE_IDLE:

        Debug_Print("\r\n[IDLE]\r\n");

        Debug_Print("Distance = %.1f cm\r\n",
                inputs.busDistance_cm);

        if(inputs.busDistance_cm <= BUS_DETECTION_DISTANCE_CM)
        {
            Debug_Print("Bus Detected\r\n");
            Debug_Print("Transition: IDLE -> PRECHARGE\r\n");

            currentState = STATE_PRECHARGE;
        }

        break;

    case STATE_PRECHARGE:

        Debug_Print("\r\n[PRECHARGE]\r\n");

        Debug_Print("Loading Capacitor Bank\r\n");

        currentState = STATE_ALIGNMENT_CHECK;

        break;

    case STATE_ALIGNMENT_CHECK:

        Debug_Print("\r\n[ALIGNMENT CHECK]\r\n");

        Debug_Print("Bus Distance = %.1f cm\r\n",
                    inputs.busDistance_cm);

        if (inputs.busDistance_cm > CHARGING_MAX_DISTANCE_CM)
        {
            Debug_Print("Bus approaching charging zone...\r\n");
            Debug_Print("Waiting for proper alignment.\r\n");

            /* Stay here */
        }

        else if (inputs.busDistance_cm >= CHARGING_MIN_DISTANCE_CM &&
                 inputs.busDistance_cm <= CHARGING_MAX_DISTANCE_CM)
        {
            Debug_Print("Bus inside charging margin.\r\n");
            Debug_Print("Transition: ALIGNMENT CHECK -> CHARGING\r\n");

            currentState = STATE_CHARGING;
        }

        else
        {
            Debug_Print("Bus passed charging zone.\r\n");
            Debug_Print("Transition: ALIGNMENT CHECK -> SHUTDOWN\r\n");

            currentState = STATE_SHUTDOWN;
        }

        break;

    case STATE_CHARGING:

    	Debug_Print("\n[CHARGING]\n");

    	PWM_Start();

    	Debug_Print("PWM............. ENABLED\r\n");

    	Debug_Print("Bus Distance.... %.1f cm\r\n",
    	        inputs.busDistance_cm);

    	Debug_Print("Driver Temp..... %.1f C\r\n",
    	        inputs.driverTemperature_C);

    	Debug_Print("MCU Temp........ %.1f C\r\n",
    	        inputs.mcuTemperature_C);

    	Debug_Print("Phase Delay: %.2f us\r\n",
    	            inputs.phaseDelay_us);


    	Debug_Print("Target Capacitance: %.2f nF\r\n",
    	            targetCapacitance);

    	Debug_Print("Power Factor.... %.2f\r\n",
    	        powerFactor);

    	PrintCapacitorMask(capacitorMask);

        if(inputs.busDistance_cm < CHARGING_MIN_DISTANCE_CM ||
           inputs.busDistance_cm > CHARGING_MAX_DISTANCE_CM)
        {
        	Debug_Print("Transition: CHARGING -> SHUTDOWN\r\n");
            currentState = STATE_SHUTDOWN;
        }

        break;

    case STATE_SHUTDOWN:

        Debug_Print("\r\n[SHUTDOWN]\r\n");

        PWM_Stop();

        Debug_Print("PWM OFF\r\n");

        Debug_Print("Discharging Capacitors...\r\n");
        Debug_Print("Transition: SHUTDOWN -> IDLE\r\n");

        currentState = STATE_IDLE;

        break;

    case STATE_FAULT:

        PWM_Stop();

        Debug_Print("Driver Temp..... %.1f C\r\n",
            	        inputs.driverTemperature_C);

		Debug_Print("MCU Temp........ %.1f C\r\n",
				inputs.mcuTemperature_C);


		currentState = STATE_SHUTDOWN;


        break;
    }
}
