/*
 * debug.c
 *
 *  Created on: Jul 7, 2026
 *      Author: nicolelau
 */


#include "debug.h"

static UART_HandleTypeDef *debug_uart;

void Debug_Init(UART_HandleTypeDef *huart)
{
    debug_uart = huart;
}

void Debug_Print(const char *format, ...)
{
    char buffer[128];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    HAL_UART_Transmit(debug_uart, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
}

void PrintCapacitorMask(uint8_t mask)
{

    Debug_Print("Capacitor Mask: ");

    for(int i = 4; i >= 0; i--)
    {

        if(mask & (1 << i))
        {
            Debug_Print("1");
        }
        else
        {
            Debug_Print("0");
        }

    }

    Debug_Print("\r\n");

}
