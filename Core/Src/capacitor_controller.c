/*
 * capacitor_controller.c
 *
 *  Created on: Jul 22, 2026
 *      Author: nicolelau
 */


#include "capacitor_controller.h"
#include <math.h>

#define FIXED_CAPACITANCE 19.9f
#define NUM_CAPACITORS 5


/*
 * Capacitor values in nF
 *
 * Bit mapping:
 *
 * Bit 0 -> C1
 * Bit 1 -> C2
 * Bit 2 -> C3
 * Bit 3 -> C4
 * Bit 4 -> C5
 *
 */

static float capacitorValues[NUM_CAPACITORS] =
{
    0.6,
    1.8,
    3.2,
    4.1,
    4.5
};



/*
 * Calculate total capacitance
 * based on capacitor switch mask
 *
 * Example:
 *
 * mask = 00101
 *
 * C1 ON
 * C3 ON
 *
 * Total:
 *
 * 0.6 + 3.2 = 3.8 nF
 */

float CalculateSwitchCapacitance(uint8_t mask)
{

    float total = 0;


    for(int i = 0; i < NUM_CAPACITORS; i++)
    {

        if(mask & (1 << i))
        {
            total += capacitorValues[i];
        }

    }


    return total;
}




/*
 * Search all 32 capacitor combinations
 *
 */

uint8_t FindBestCapacitorMask(float targetCapacitance)
{

    uint8_t bestMask = 0;


    float smallestError = 9999;


    for(uint8_t mask = 0; mask < 32; mask++)
    {

    	float currentCap =
    	        CalculateSwitchCapacitance(mask);


        float requiredSwitchCap =
                targetCapacitance - FIXED_CAPACITANCE;


        float error =
                fabs(requiredSwitchCap - currentCap);



        if(error < smallestError)
        {

            smallestError = error;

            bestMask = mask;

        }

    }


    return bestMask;

}

float CalculateTargetCapacitance(float misalignment_mm)
{

    if(misalignment_mm <= 0)
        return 19.9f;

    else if(misalignment_mm <= 10)
        return 20.5f;

    else if(misalignment_mm <= 20)
        return 21.7f;

    else if(misalignment_mm <= 30)
        return 23.1f;

    else if(misalignment_mm <= 40)
        return 24.0f;

    else
        return 24.4f;

}
