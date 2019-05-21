/*
 * infrared.h
 *
 *  Created on: 2019. May. 22.
 *      Author: peter.brogli
 */

#ifndef MAIN_INFRARED_H_
#define MAIN_INFRARED_H_

#include "driver/gpio.h"

#define GPIO_IR_SENSOR_L2 5
#define GPIO_IR_SENSOR_L1 18 
#define GPIO_IR_SENSOR_R1 19
#define GPIO_IR_SENSOR_R2 21

#define GPIO_IR_SENSOR_PIN_SEL  ((1ULL<<GPIO_IR_SENSOR_L2)|(1ULL<<GPIO_IR_SENSOR_L1)|(1ULL<<GPIO_IR_SENSOR_R1)|(1ULL<<GPIO_IR_SENSOR_R2))

void ir_sensor_init(void);

int get_ir_sensor_L2(void);
int get_ir_sensor_L1(void);
int get_ir_sensor_R1(void);
int get_ir_sensor_R2(void);

#endif /* MAIN_INFRARED_H_ */