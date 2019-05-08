/*
 * delay_.c
 *
 *  Created on: 2019. Apr. 18.
 *      Author: peter.brogli
 */

#include "delay_.h"

void delay_ms(int ms)
{
	vTaskDelay(ms / portTICK_RATE_MS);
}

void delay_us(int us)
{
	ets_delay_us(us);
}