/*
 * motor_driver.c
 *
 *  Created on: 2019. May. 8.
 *      Author: peter.brogli
 */

#include "motor_driver.h"
#include "driver/mcpwm.h"


void motor_init(void)
{
   	gpio_config_t io_conf;
        io_conf.intr_type = GPIO_PIN_INTR_DISABLE;//disable interrupt
        io_conf.mode = GPIO_MODE_OUTPUT;//set as output mode
	    io_conf.pin_bit_mask = GPIO_MOTOR_PIN_SEL;//bit mask of the pins that you want to set,e.g.GPIO18/19
	    io_conf.pull_down_en = 0;//enable pull-down mode
	    io_conf.pull_up_en = 0;//disable pull-up mode
    gpio_config(&io_conf);//configure GPIO with the given settings

    gpio_set_level(GPIO_MOTOR_IN1,0);
    gpio_set_level(GPIO_MOTOR_IN2,0);
    gpio_set_level(GPIO_MOTOR_IN3,0);
    gpio_set_level(GPIO_MOTOR_IN4,0);

    mcpwm_pin_config_t pin_config = {
        .mcpwm0a_out_num = GPIO_MOTOR_IN1,
	    .mcpwm0b_out_num = GPIO_MOTOR_IN2,
        .mcpwm1a_out_num = GPIO_MOTOR_IN3,
        .mcpwm1b_out_num = GPIO_MOTOR_IN4
    };
	mcpwm_set_pin(MCPWM_UNIT_1, &pin_config);

	mcpwm_config_t pwm_config;
	    pwm_config.frequency = 1000;    //frequency = 1000Hz
	    pwm_config.cmpr_a = 0.0;       //duty cycle of PWMxA = 50.0%
        pwm_config.cmpr_b = 0.0;       //duty cycle of PWMxB = 50.0%
        pwm_config.counter_mode = MCPWM_UP_COUNTER;
	    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
	mcpwm_init(MCPWM_UNIT_1, MCPWM_TIMER_0, &pwm_config);
	mcpwm_start(MCPWM_UNIT_1, MCPWM_TIMER_0);

	    pwm_config.frequency = 1000;    //frequency = 1000Hz
	    pwm_config.cmpr_a = 0.0;       //duty cycle of PWMxA = 50.0%
        pwm_config.cmpr_b = 0.0;       //duty cycle of PWMxB = 50.0%
        pwm_config.counter_mode = MCPWM_UP_COUNTER;
	    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
	mcpwm_init(MCPWM_UNIT_1, MCPWM_TIMER_1, &pwm_config);
	mcpwm_start(MCPWM_UNIT_1, MCPWM_TIMER_1);

}

void set_motor_R_fwd(float speed)
{
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0,MCPWM_OPR_A,0.0);
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0,MCPWM_OPR_B,speed);
    delay_ms(1);
}

void set_motor_R_rvs(float speed)
{
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0,MCPWM_OPR_A,speed);
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0,MCPWM_OPR_B,0);
    delay_ms(1);
}

void set_motor_R_stop()
{
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0,MCPWM_OPR_A,0);
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0,MCPWM_OPR_B,0);
    delay_ms(1);
}

void set_motor_L_fwd(float speed)
{
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1,MCPWM_OPR_A,0);
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1,MCPWM_OPR_B,speed);
    delay_ms(1);
}

void set_motor_L_rvs(float speed)
{
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1,MCPWM_OPR_A,speed);
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1,MCPWM_OPR_B,0);
    delay_ms(1);
}

void set_motor_L_stop()
{
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1,MCPWM_OPR_A,0);
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1,MCPWM_OPR_B,0);
    delay_ms(1);
}

void set_motor_R(int steps, int direction, float speed)
{
    if(direction==(1)){
        set_motor_R_fwd(speed);
    }
    if(direction==(-1)){
        set_motor_R_rvs(speed);
    }
    //delay_ms(steps);
    //set_motor_R_stop();
    xTaskCreate( counter_R_task, "Set_motor_R_task", 1024*2, (void *) steps, 1, xCounterRHandle );
}

void set_motor_L(int steps, int direction, float speed)
{
    if(direction==(1)){
        set_motor_L_fwd(speed);
    }
    if(direction==(-1)){
        set_motor_L_rvs(speed);
    }
    //delay_ms(steps);
    //set_motor_L_stop();
    xTaskCreate( counter_L_task, "Set_motor_L_task", 1024*2, (void *) steps, 1, xCounterLHandle );
}

void counter_R_task(void *parameter)
{
    int *counter = (int *)parameter;   
    delay_ms(counter);
    set_motor_R_stop();
    vTaskDelete( xCounterRHandle );
}

void counter_L_task(void *parameter)
{
    int *counter = (int *)parameter;   
    delay_ms(counter);
    set_motor_L_stop();
    vTaskDelete( xCounterRHandle );
}