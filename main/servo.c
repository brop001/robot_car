/*
 * servo.c
 *
 *  Created on: 2019. May. 13.
 *      Author: peter.brogli
 */

#include "servo.h"


void servo_init()
{
    gpio_config_t io_conf;
        io_conf.intr_type = GPIO_PIN_INTR_DISABLE;//disable interrupt
        io_conf.mode = GPIO_MODE_OUTPUT;//set as output mode
	    io_conf.pin_bit_mask = GPIO_SERVO_PIN_SEL;//bit mask of the pins that you want to set,e.g.GPIO18/19
	    io_conf.pull_down_en = 0;//enable pull-down mode
	    io_conf.pull_up_en = 0;//disable pull-up mode
    gpio_config(&io_conf);//configure GPIO with the given settings

    gpio_set_level(GPIO_SERVO,0);



	mcpwm_pin_config_t pin_config = {
			.mcpwm2a_out_num = GPIO_SERVO
	};
	mcpwm_set_pin(MCPWM_UNIT_1, &pin_config);

	mcpwm_config_t pwm_config;
	    pwm_config.frequency = 50;    //frequency = 1000Hz
	    pwm_config.cmpr_a = 0;       //duty cycle of PWMxA = 50.0%
	    pwm_config.counter_mode = MCPWM_UP_COUNTER;
	    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
	mcpwm_init(MCPWM_UNIT_1, MCPWM_TIMER_2, &pwm_config);
	mcpwm_stop(MCPWM_UNIT_1, MCPWM_TIMER_2);
}

void set_servo(float degree)
{
    /*mcpwm_config_t pwm_config;
		pwm_config.frequency = 50;    //frequency = 50Hz
		pwm_config.counter_mode = MCPWM_UP_COUNTER;
		pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
		pwm_config.cmpr_a = degree;       //duty cycle of PWMxA = 50.0%
	mcpwm_init(MCPWM_UNIT_1, MCPWM_TIMER_2, &pwm_config);*/

    mcpwm_config_t pwm_config;
		pwm_config.frequency = 50;    //frequency = 50Hz
		pwm_config.counter_mode = MCPWM_UP_COUNTER;
		pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
		pwm_config.cmpr_a = ((((float)(SERVO_180-SERVO_0)/180)*degree)+SERVO_0);       //duty cycle of PWMxA = 50.0%
        printf("%f\n",((((float)(SERVO_180-SERVO_0)/180)*degree)+SERVO_0));
	mcpwm_init(MCPWM_UNIT_1, MCPWM_TIMER_2, &pwm_config);
}