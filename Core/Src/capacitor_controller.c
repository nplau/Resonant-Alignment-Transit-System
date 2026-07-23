/*
 * capacitor_controller.c
 *
 *  Created on: Jul 22, 2026
 *      Author: nicolelau
 */


#include "capacitor_controller.h"


uint8_t FindBestCapacitorMask(float currentPF)
{

    uint8_t bestMask = 0;


    if(currentPF < 0.8)
    {
        bestMask = 0b11111;
    }

    else if(currentPF < 0.95)
    {
        bestMask = 0b00111;
    }

    else
    {
        bestMask = 0b00001;
    }


    return bestMask;

}
