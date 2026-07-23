/*
 * state_machine.c
 *
 *  Created on: Jul 22, 2026
 *      Author: nicolelau
 */


#include "state_machine.h"

#include "simulation.h"
#include "config.h"
#include "debug.h"
#include "pwm.h"

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


    /*---------------- Safety Monitoring ----------------*/

    if (inputs.currentSample > MAX_INPUT_CURRENT_A)
    {
    	currentState = STATE_FAULT;
    }

    else if (inputs.voltageSample > MAX_INPUT_VOLTAGE_V)
    {
        currentState = STATE_FAULT;
    }

    else if (inputs.driverTemperature_C > MAX_DRIVER_TEMP_C)
    {
        currentState = STATE_FAULT;
    }

    else if (inputs.mcuTemperature_C > MAX_MCU_TEMP_C)
    {
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

        Debug_Print("Capacitor Bank\r\n");
        Debug_Print("C1 : ON\r\n");
        Debug_Print("C2 : OFF\r\n");
        Debug_Print("C3 : ON\r\n");
        Debug_Print("C4 : OFF\r\n");
        Debug_Print("C5 : OFF\r\n");

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

    	Debug_Print("Power Factor.... %.2f\r\n",
    	        inputs.powerFactor);

    	Debug_Print("Capacitor Bank\r\n");
    	Debug_Print("C1 : ON\r\n");
    	Debug_Print("C2 : OFF\r\n");
    	Debug_Print("C3 : ON\r\n");
    	Debug_Print("C4 : OFF\r\n");
    	Debug_Print("C5 : OFF\r\n");

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

        Debug_Print("\r\n[FAULT]\r\n");

        PWM_Stop();


		currentState = STATE_SHUTDOWN;


        break;
    }
}
