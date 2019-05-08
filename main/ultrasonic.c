/*
 * ultrasonic.c
 *
 *  Created on: 2019. May. 8.
 *      Author: peter.brogli
 */

#include "ultrasonic.h"

void ultrasonic_init()
{
    gpio_config_t io_conf;
        io_conf.intr_type = GPIO_PIN_INTR_DISABLE;//disable interrupt
        io_conf.mode = GPIO_MODE_OUTPUT;//set as output mode
	    io_conf.pin_bit_mask = GPIO_US_OUTPUT_PIN_SEL;//bit mask of the pins that you want to set,e.g.GPIO18/19
	    io_conf.pull_down_en = 0;//enable pull-down mode
	    io_conf.pull_up_en = 0;//disable pull-up mode
    gpio_config(&io_conf);//configure GPIO with the given settings

    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;//disable interrupt
        io_conf.mode = GPIO_MODE_INPUT;//set as output mode
	    io_conf.pin_bit_mask = GPIO_US_INPUT_PIN_SEL;//bit mask of the pins that you want to set,e.g.GPIO18/19
	    io_conf.pull_down_en = 0;//enable pull-down mode
	    io_conf.pull_up_en = 0;//disable pull-up mode
    gpio_config(&io_conf);//configure GPIO with the given settings

    gpio_set_level(GPIO_US_TRIGGER,0);
}

int get_us_distance_in_us()
{
    gpio_set_level(GPIO_US_TRIGGER,1);
    delay_us(20);
    gpio_set_level(GPIO_US_TRIGGER,0);

    unsigned long start = esp_timer_get_time();
    unsigned long before = 0;
    unsigned long before2 = 0;
    unsigned long after = 0;

    while(!gpio_get_level(GPIO_US_ECHO))
    {
        before = esp_timer_get_time();
        if((before-start)>1000){
            return(EXIT_FAILURE);
        }
        delay_us(1);
    }
    before = esp_timer_get_time();
    while(gpio_get_level(GPIO_US_ECHO))
    {
        after = esp_timer_get_time();
        if((after-before)>ECHO_TIMEOUT){
            return(EXIT_FAILURE);
        }
        delay_us(1);
    }
    after = esp_timer_get_time();
    return((int)(after-before));
}

int get_us_distance_in_cm()
{
    long us_distance_in_us = get_us_distance_in_us();
    if(us_distance_in_us==EXIT_FAILURE){
        return(EXIT_FAILURE);
    }
    return(us_distance_in_us/58);
}
