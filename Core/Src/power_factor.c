/*
 * power_factor.c
 *
 *  Created on: Jul 22, 2026
 *      Author: nicolelau
 */
#include "power_factor.h"
#include <math.h>


#define FREQUENCY_HZ 85000.0f


float CalculatePowerFactor(float phaseDelay_us)
{

    float phaseRadians;

    /*2pi ft*/
    phaseRadians =
        2.0f * M_PI *
        FREQUENCY_HZ *
        (phaseDelay_us / 1000000.0f);


    return cosf(phaseRadians);

}
