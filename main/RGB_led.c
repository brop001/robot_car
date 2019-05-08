/*
 * RGB_led.c
 *
 *  Created on: 2019. May. 8.
 *      Author: peter.brogli
 */

#include "RGB_led.h"

void RGB_led_init(void)
{
   	gpio_config_t io_conf;
        io_conf.intr_type = GPIO_PIN_INTR_DISABLE;//disable interrupt
        io_conf.mode = GPIO_MODE_OUTPUT;//set as output mode
	    io_conf.pin_bit_mask = GPIO_RGB_LED_PIN_SEL;//bit mask of the pins that you want to set,e.g.GPIO18/19
	    io_conf.pull_down_en = 0;//enable pull-down mode
	    io_conf.pull_up_en = 0;//disable pull-up mode
    gpio_config(&io_conf);//configure GPIO with the given settings

    gpio_set_level(GPIO_LED_R,0);
    gpio_set_level(GPIO_LED_G,0);
    gpio_set_level(GPIO_LED_B,0);



    mcpwm_pin_config_t pin_config = {
		.mcpwm1a_out_num = GPIO_LED_R,
		.mcpwm1b_out_num = GPIO_LED_G,
		.mcpwm2a_out_num = GPIO_LED_B,
	};
	mcpwm_set_pin(MCPWM_UNIT_0, &pin_config);

	mcpwm_config_t pwm_config;
		pwm_config.frequency = 1000;    //frequency = 1000Hz
		pwm_config.cmpr_a = 50.0;       //duty cycle of PWMxA = 50.0%
        pwm_config.cmpr_b = 50.0;       //duty cycle of PWMxA = 50.0%
		pwm_config.counter_mode = MCPWM_UP_COUNTER;
		pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
	mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config);
	mcpwm_stop(MCPWM_UNIT_0, MCPWM_TIMER_1);
    
    	pwm_config.frequency = 1000;    //frequency = 1000Hz
	    pwm_config.cmpr_a = 50.0;       //duty cycle of PWMxA = 50.0%
		pwm_config.counter_mode = MCPWM_UP_COUNTER;
		pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
	mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_2, &pwm_config);
	mcpwm_stop(MCPWM_UNIT_0, MCPWM_TIMER_2);

}

void set_led(int color)
{
	mcpwm_config_t pwm_config;
			pwm_config.frequency = 1000;    //frequency = 1000Hz
			pwm_config.counter_mode = MCPWM_UP_COUNTER;
			pwm_config.duty_mode = MCPWM_DUTY_MODE_0;

	switch(color){

		case 0:
			pwm_config.cmpr_a = 0;       //duty cycle of PWMxA = 50.0%
			pwm_config.cmpr_b = 0;       //duty cycle of PWMxA = 50.0%
			mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config);
			pwm_config.cmpr_a = 0;       //duty cycle of PWMxA = 50.0%
			mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_2, &pwm_config);

			printf("Led OFF\n");
			break;
		case 1:
			pwm_config.cmpr_a = PWM_R;       //duty cycle of PWMxA = 50.0%
			pwm_config.cmpr_b = 0;       //duty cycle of PWMxA = 50.0%
			mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config);
			pwm_config.cmpr_a = 0;       //duty cycle of PWMxA = 50.0%
			mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_2, &pwm_config);

			printf("Led RED\n");
			break;
		case 2:
			pwm_config.cmpr_a = 0;       //duty cycle of PWMxA = 50.0%
			pwm_config.cmpr_b = PWM_G;       //duty cycle of PWMxA = 50.0%
			mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config);
			pwm_config.cmpr_a = 0;       //duty cycle of PWMxA = 50.0%
			mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_2, &pwm_config);

			printf("Led GREEN\n");
			break;
		case 3:
			pwm_config.cmpr_a = 0;       //duty cycle of PWMxA = 50.0%
			pwm_config.cmpr_b = 0;       //duty cycle of PWMxA = 50.0%
			mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config);
			pwm_config.cmpr_a = PWM_B;       //duty cycle of PWMxA = 50.0%
			mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_2, &pwm_config);

			printf("Led BLUE\n");
			break;
		case 4:
			pwm_config.cmpr_a = PWM_R;       //duty cycle of PWMxA = 50.0%
			pwm_config.cmpr_b = PWM_G;       //duty cycle of PWMxA = 50.0%
			mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config);
			pwm_config.cmpr_a = 0;       //duty cycle of PWMxA = 50.0%
			mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_2, &pwm_config);

			printf("Led YELLOW\n");
			break;
		case 5:
			pwm_config.cmpr_a = 0;       //duty cycle of PWMxA = 50.0%
			pwm_config.cmpr_b = PWM_G;       //duty cycle of PWMxA = 50.0%
			mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config);
			pwm_config.cmpr_a = PWM_B;       //duty cycle of PWMxA = 50.0%
			mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_2, &pwm_config);

			printf("Led CYAN\n");
			break;
		case 6:
			pwm_config.cmpr_a = PWM_R;       //duty cycle of PWMxA = 50.0%
			pwm_config.cmpr_b = 0;       //duty cycle of PWMxA = 50.0%
			mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config);
			pwm_config.cmpr_a = PWM_B;       //duty cycle of PWMxA = 50.0%
			mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_2, &pwm_config);

			printf("Led MAGENTA\n");
			break;
		case 7:
			pwm_config.cmpr_a = PWM_R;       //duty cycle of PWMxA = 50.0%
			pwm_config.cmpr_b = PWM_G;       //duty cycle of PWMxA = 50.0%
			mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config);
			pwm_config.cmpr_a = PWM_B;       //duty cycle of PWMxA = 50.0%
			mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_2, &pwm_config);

			printf("Led WHITE\n");
			break;
		default:
			break;
	}
}

void set_led_color(int red, int green, int blue)
{
    mcpwm_config_t pwm_config;
        pwm_config.cmpr_a = red;       //duty cycle of PWMxA = 50.0%
        pwm_config.cmpr_b = green;       //duty cycle of PWMxA = 50.0%
	mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config);
	    pwm_config.cmpr_a = blue;       //duty cycle of PWMxA = 50.0%
	mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_2, &pwm_config);
}