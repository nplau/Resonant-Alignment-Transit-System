/*
 * debug.h
 *
 *  Created on: Jul 7, 2026
 *      Author: nicolelau
 */


#ifndef DEBUG_H
#define DEBUG_H

#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

void Debug_Init(UART_HandleTypeDef *huart);
void Debug_Print(const char *format, ...);

#endif /* INC_DEBUG_H_ */
