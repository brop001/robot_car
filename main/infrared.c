/*
 * infrared.c
 *
 *  Created on: 2019. May. 22.
 *      Author: peter.brogli
 */

#include "infrared.h"

void ir_sensor_init(void)
{
   	gpio_config_t io_conf;
        io_conf.intr_type = GPIO_PIN_INTR_DISABLE;//disable interrupt
        io_conf.mode = GPIO_MODE_INPUT;//set as output mode
	    io_conf.pin_bit_mask = GPIO_IR_SENSOR_PIN_SEL;//bit mask of the pins that you want to set,e.g.GPIO18/19
	    io_conf.pull_down_en = 0;//enable pull-down mode
	    io_conf.pull_up_en = 0;//disable pull-up mode
    gpio_config(&io_conf);//configure GPIO with the given settings
}

int get_ir_sensor_L2()
{
    return(gpio_get_level(GPIO_IR_SENSOR_L2));
}

int get_ir_sensor_L1()
{
    return(gpio_get_level(GPIO_IR_SENSOR_L1));
}

int get_ir_sensor_R1()
{
    return(gpio_get_level(GPIO_IR_SENSOR_R1));
}

int get_ir_sensor_R2()
{
    return(gpio_get_level(GPIO_IR_SENSOR_R2));
}