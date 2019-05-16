/*
 * motor_driver.h
 *
 *  Created on: 2019. May. 8.
 *      Author: peter.brogli
 */

#ifndef MAIN_MOTOR_DRIVER_H_
#define MAIN_MOTOR_DRIVER_H_

#include "driver/gpio.h"
#include "driver/pcnt.h"

#define GPIO_MOTOR_IN1    25
#define GPIO_MOTOR_IN2    26
#define GPIO_MOTOR_IN3    27
#define GPIO_MOTOR_IN4    14
#define GPIO_MOTOR_R_SENSOR 34
#define GPIO_MOTOR_L_SENSOR 35

#define GPIO_MOTOR_PIN_SEL  ((1ULL<<GPIO_MOTOR_IN1)|(1ULL<<GPIO_MOTOR_IN2)|(1ULL<<GPIO_MOTOR_IN3)|(1ULL<<GPIO_MOTOR_IN4))

void motor_init(void);

void set_motor_R_fwd(float speed);
void set_motor_R_rvs(float speed);
void set_motor_R_stop(void);
void set_motor_L_fwd(float speed);
void set_motor_L_rvs(float speed);
void set_motor_L_stop(void);

#endif /* MAIN_MOTOR_DRIVER_H_ */