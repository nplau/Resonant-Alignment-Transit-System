/*
 * config.h
 *
 *  Created on: Jul 20, 2026
 *      Author: nicolelau
 */

#ifndef CONFIG_H
#define CONFIG_H

/* Bus Detection */

#define BUS_DETECTION_DISTANCE_CM      150.0f

/* Charging Margin 5cm */

#define CHARGING_MIN_DISTANCE_CM        45.0f
#define CHARGING_MAX_DISTANCE_CM        50.0f

/* Safety Limits */

#define MAX_INPUT_CURRENT_A      		250.0f
#define MAX_INPUT_VOLTAGE_V      		420.0f

#define MAX_DRIVER_TEMP_C               70.0f
#define MAX_MCU_TEMP_C                  70.0f

/* Capacitor Defaults */

#define DEFAULT_CAPACITOR_MASK          0b10100

#endif /* INC_CONFIG_H_ */
