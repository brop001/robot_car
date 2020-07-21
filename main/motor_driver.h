/*
 * motor_driver.h
 *
 *  Created on: 2019. May. 8.
 *      Author: peter.brogli
 */

#ifndef MAIN_MOTOR_DRIVER_H_
#define MAIN_MOTOR_DRIVER_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#include "delay_.h"

#define GPIO_MOTOR_IN1    25
#define GPIO_MOTOR_IN2    26
#define GPIO_MOTOR_IN3    27
#define GPIO_MOTOR_IN4    14
#define GPIO_MOTOR_R_SENSOR 34
#define GPIO_MOTOR_L_SENSOR 35

#define GPIO_MOTOR_PIN_SEL  ((1ULL<<GPIO_MOTOR_IN1)|(1ULL<<GPIO_MOTOR_IN2)|(1ULL<<GPIO_MOTOR_IN3)|(1ULL<<GPIO_MOTOR_IN4))
#define GPIO_MOTOR_SPEED_SENSOR_PIN_SEL  ((1ULL<<GPIO_MOTOR_SPEED_SENSOR_L)|(1ULL<<GPIO_MOTOR_SPEED_SENSOR_L))

TaskHandle_t xCounterRHandle;
TaskHandle_t xCounterLHandle;

void motor_init(void);

void set_motor_R_fwd(float speed);
void set_motor_R_rvs(float speed);
void set_motor_R_stop(void);
void set_motor_L_fwd(float speed);
void set_motor_L_rvs(float speed);
void set_motor_L_stop(void);
void start_car(int direction, float speed);
void stop_car(void);

void set_motor_R(int steps, int direction, float speed);
void set_motor_L(int steps, int direction, float speed);

void counter_R_task(void *parameter);
void counter_L_task(void *parameter);

#endif /* MAIN_MOTOR_DRIVER_H_ */