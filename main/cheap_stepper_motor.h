/*
 * cheap_stepper_motor.h
 *
 *  Created on: 2019. maj. 8.
 *      Author: peter.brogli
 */

#ifndef MAIN_CHEAP_STEPPER_MOTOR_H_
#define MAIN_CHEAP_STEPPER_MOTOR_H_

#include "driver/gpio.h"

#define GPIO_MOTOR_R_IN1    5
#define GPIO_MOTOR_R_IN2    17
#define GPIO_MOTOR_R_IN3    16
#define GPIO_MOTOR_R_IN4    4

#define GPIO_MOTOR_L_IN1    26
#define GPIO_MOTOR_L_IN2    27
#define GPIO_MOTOR_L_IN3    14
#define GPIO_MOTOR_L_IN4    12

#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<GPIO_MOTOR_R_IN1)|(1ULL<<GPIO_MOTOR_R_IN2)|(1ULL<<GPIO_MOTOR_R_IN3)|(1ULL<<GPIO_MOTOR_R_IN4)|(1ULL<<GPIO_MOTOR_L_IN1)|(1ULL<<GPIO_MOTOR_L_IN2)|(1ULL<<GPIO_MOTOR_L_IN3)|(1ULL<<GPIO_MOTOR_L_IN4))
#define GPIO_INPUT_PIN_SEL  ()

void GPIO_init(void);

#endif /* MAIN_CHEAP_STEPPER_MOTOR_H_ */