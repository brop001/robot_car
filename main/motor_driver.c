/*
 * motor_driver.c
 *
 *  Created on: 2019. May. 8.
 *      Author: peter.brogli
 */

#include "motor_driver.h"
#include "driver/mcpwm.h"

#define PCNT_TEST_UNIT      PCNT_UNIT_0
#define PCNT_H_LIM_VAL      10
#define PCNT_L_LIM_VAL     -10
#define PCNT_THRESH1_VAL    5
#define PCNT_THRESH0_VAL   -5
#define PCNT_INPUT_SIG_IO   4  // Pulse Input GPIO
#define PCNT_INPUT_CTRL_IO  5  // Control GPIO HIGH=count up, LOW=count down
#define LEDC_OUTPUT_IO      18 // Output GPIO of a sample 1 Hz pulse generator

xQueueHandle pcnt_evt_queue;   // A queue to handle pulse counter events
pcnt_isr_handle_t user_isr_handle = NULL; //user's ISR service handle

/* A sample structure to pass events from the PCNT
 * interrupt handler to the main program.
 */
typedef struct {
    int unit;  // the PCNT unit that originated an interrupt
    uint32_t status; // information on the event type that caused the interrupt
} pcnt_evt_t;

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


    pcnt_config_t pcnt_config = {
        // Set PCNT input signal and control GPIOs
        .pulse_gpio_num = GPIO_MOTOR_R_SENSOR,
        .channel = PCNT_CHANNEL_0,
        .unit = PCNT_UNIT_0,
        // What to do on the positive / negative edge of pulse input?
        .pos_mode = PCNT_COUNT_INC,   // Count up on the positive edge
        .neg_mode = PCNT_COUNT_DIS,   // Keep the counter value on the negative edge
        // What to do when control input is low or high?
        
        // Set the maximum and minimum limit values to watch
        .counter_h_lim = PCNT_H_LIM_VAL,
        .counter_l_lim = PCNT_L_LIM_VAL,
    };
    /* Initialize PCNT unit */
    pcnt_unit_config(&pcnt_config);


    /* Initialize PCNT's counter */
    pcnt_counter_pause(PCNT_TEST_UNIT);
    pcnt_counter_clear(PCNT_TEST_UNIT);

    /* Everything is set up, now go to counting */
    pcnt_counter_resume(PCNT_TEST_UNIT);

}

void set_motor_R_fwd(float speed)
{
    //pcnt_counter_pause(PCNT_TEST_UNIT);
    //pcnt_counter_clear(PCNT_TEST_UNIT);

    /* Everything is set up, now go to counting */
    //pcnt_counter_resume(PCNT_TEST_UNIT);
    //int count = 0;
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0,MCPWM_OPR_A,0.0);
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0,MCPWM_OPR_B,speed);
    /*for(;;){
        if(pcnt_get_counter_value(PCNT_TEST_UNIT, &count)>20)break;
    }*/
    
}

void set_motor_R_rvs(float speed)
{
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0,MCPWM_OPR_A,speed);
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0,MCPWM_OPR_B,0);
}

void set_motor_R_stop()
{
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0,MCPWM_OPR_A,0);
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0,MCPWM_OPR_B,0);
}

void set_motor_L_fwd(float speed)
{
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1,MCPWM_OPR_A,0);
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1,MCPWM_OPR_B,speed);
}

void set_motor_L_rvs(float speed)
{
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1,MCPWM_OPR_A,speed);
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1,MCPWM_OPR_B,0);
}

void set_motor_L_stop()
{
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1,MCPWM_OPR_A,0);
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1,MCPWM_OPR_B,0);
}

