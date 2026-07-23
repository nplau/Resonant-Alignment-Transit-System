/*
 * power_factor.c
 *
 *  Created on: Jul 22, 2026
 *      Author: nicolelau
 */

#include "power_factor.h"
#include <math.h>


float CalculatePowerFactor(float voltage,
                           float current)
{

    float phaseDifference = voltage - current;


    float pf = cosf(phaseDifference);


    return pf;

}
