/*
 * buzzer.h
 *
 *  Created on: 2019. May. 8.
 *      Author: peter.brogli
 */

#ifndef MAIN_BUZZER_H_
#define MAIN_BUZZER_H_

#include "driver/gpio.h"
#include "driver/ledc.h"
#include "driver/mcpwm.h"

#include "delay_.h"

#define GPIO_BUZZER 4

#define GPIO_BUZZER_PIN_SEL  ((1ULL<<GPIO_BUZZER))

void buzzer_init(void);
void buzzer(int frequency, int time_ms);
void start_buzzer(int frequency);
void set_buzzer_frequency(int frequency);
void stop_buzzer(void);

#endif /* MAIN_BUZZER_H_ */