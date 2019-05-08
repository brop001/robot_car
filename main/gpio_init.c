/*
 * gpio_init.h
 *
 *  Created on: 2019. maj. 8.
 *      Author: peter.brogli
 */

#include "gpio_init.h"

void GPIO_init(void)
{

	gpio_config_t io_conf;

		io_conf.intr_type = GPIO_PIN_INTR_DISABLE;//disable interrupt
	    io_conf.mode = GPIO_MODE_OUTPUT;//set as output mode
	    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;//bit mask of the pins that you want to set,e.g.GPIO18/19
	    io_conf.pull_down_en = 0;//enable pull-down mode
	    io_conf.pull_up_en = 0;//disable pull-up mode
	gpio_config(&io_conf);//configure GPIO with the given settings

	gpio_set_level(GPIO_MOTOR_R_IN1,0);
	gpio_set_level(GPIO_MOTOR_R_IN2,0);
	gpio_set_level(GPIO_MOTOR_R_IN3,0);
	gpio_set_level(GPIO_MOTOR_R_IN4,0);

    gpio_set_level(GPIO_MOTOR_L_IN1,0);
    gpio_set_level(GPIO_MOTOR_L_IN2,0);
    gpio_set_level(GPIO_MOTOR_L_IN3,0);
    gpio_set_level(GPIO_MOTOR_L_IN4,0);
}