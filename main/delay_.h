/*
 * delay_.h
 *
 *  Created on: 2019. Apr. 18.
 *      Author: peter.brogli
 */

#ifndef MAIN_DELAY__H_
#define MAIN_DELAY__H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp32/rom/ets_sys.h"


void delay_ms(int ms);
void delay_us(int us);

#endif /* MAIN_DELAY__H_ */