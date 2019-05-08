/*
 * ultrasonic.h
 *
 *  Created on: 2019. May. 8.
 *      Author: peter.brogli
 */

#ifndef MAIN_ULTRASONIC_H_
#define MAIN_ULTRASONIC_H_

#include "driver/gpio.h"
#include "esp_timer.h"

#include "delay_.h"

#define GPIO_US_TRIGGER 32
#define GPIO_US_ECHO 33

#define GPIO_US_INPUT_PIN_SEL  ((1ULL<<GPIO_US_ECHO))
#define GPIO_US_OUTPUT_PIN_SEL  ((1ULL<<GPIO_US_TRIGGER))

#define ECHO_TIMEOUT 23200

void ultrasonic_init(void);
int get_us_distance_in_us(void);
int get_us_distance_in_cm(void);

#endif /* MAIN_ULTRASONIC_H_ */

