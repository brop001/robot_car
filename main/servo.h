/*
 * servo.h
 *
 *  Created on: 2019. May. 13.
 *      Author: peter.brogli
 */

#ifndef MAIN_SERVO_H_
#define MAIN_SERVO_H_

#include "driver/gpio.h"
#include "driver/mcpwm.h"

#include "delay_.h"

#define GPIO_SERVO 12

#define GPIO_SERVO_PIN_SEL  ((1ULL<<GPIO_SERVO))

#define SERVO_180   12
#define SERVO_0     2.6

void servo_init(void);
void set_servo(float degree);


#endif /* MAIN_SERVO_H_ */