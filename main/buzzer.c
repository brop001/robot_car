/*
 * buzzer.c
 *
 *  Created on: 2019. May. 8.
 *      Author: peter.brogli
 */

#include "buzzer.h"

#define LEDC_HS_CH0_GPIO       (18)
#define LEDC_HS_CH0_CHANNEL    LEDC_CHANNEL_0
#define LEDC_HS_CH1_GPIO       (19)
#define LEDC_HS_CH1_CHANNEL    LEDC_CHANNEL_1

#define LEDC_LS_TIMER          LEDC_TIMER_1
#define LEDC_LS_MODE           LEDC_LOW_SPEED_MODE
#define LEDC_LS_CH2_GPIO       (4)
#define LEDC_LS_CH2_CHANNEL    LEDC_CHANNEL_2
#define LEDC_LS_CH3_GPIO       (5)
#define LEDC_LS_CH3_CHANNEL    LEDC_CHANNEL_3

#define LEDC_TEST_CH_NUM       (4)
#define LEDC_TEST_DUTY         (4000)
#define LEDC_TEST_FADE_TIME    (3000)


void buzzer_init(void)
{
   	gpio_config_t io_conf;
        io_conf.intr_type = GPIO_PIN_INTR_DISABLE;//disable interrupt
        io_conf.mode = GPIO_MODE_OUTPUT;//set as output mode
	    io_conf.pin_bit_mask = GPIO_BUZZER_PIN_SEL;//bit mask of the pins that you want to set,e.g.GPIO18/19
	    io_conf.pull_down_en = 0;//enable pull-down mode
	    io_conf.pull_up_en = 0;//disable pull-up mode
    gpio_config(&io_conf);//configure GPIO with the given settings

    gpio_set_level(GPIO_BUZZER,0);


	//ledc_timer_set( LEDC_HIGH_SPEED_MODE,  LEDC_TIMER_0,  0,  LEDC_TIMER_8_BIT, LEDC_REF_TICK);
	
	/*ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_8_BIT, // resolution of PWM duty
        .freq_hz = 5000,                      // frequency of PWM signal
        .speed_mode = LEDC_HIGH_SPEED_MODE,           // timer mode
        .timer_num = LEDC_TIMER_0            // timer index
    };
    // Set configuration of timer0 for high speed channels
    ledc_timer_config(&ledc_timer);

	ledc_channel_config_t ledc_channel[1] = {
        {
            .channel    = LEDC_CHANNEL_0,
            .duty       = 50,
            .gpio_num   = GPIO_BUZZER,
            .speed_mode = LEDC_HIGH_SPEED_MODE,
            .hpoint     = 0,
            .timer_sel  = LEDC_TIMER_0
        },
    };

	ledc_channel_config(&ledc_channel[0]);*/

	mcpwm_pin_config_t pin_config = {
			.mcpwm0a_out_num = GPIO_BUZZER
	};
	mcpwm_set_pin(MCPWM_UNIT_0, &pin_config);

	mcpwm_config_t pwm_config;
	    pwm_config.frequency = 1000;    //frequency = 1000Hz
	    pwm_config.cmpr_a = 50.0;       //duty cycle of PWMxA = 50.0%
	    pwm_config.counter_mode = MCPWM_UP_COUNTER;
	    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
	mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);
	mcpwm_stop(MCPWM_UNIT_0, MCPWM_TIMER_0);
}

void buzzer(int frequency, int time_ms)
{

	ESP_ERROR_CHECK(mcpwm_set_frequency(MCPWM_UNIT_0, MCPWM_TIMER_0,frequency));
	

	mcpwm_start(MCPWM_UNIT_0, MCPWM_TIMER_0);

	delay_ms(time_ms);
	
	mcpwm_stop(MCPWM_UNIT_0, MCPWM_TIMER_0);
	
}

void start_buzzer(int frequency)
{
	if(!frequency){
		mcpwm_start(MCPWM_UNIT_0, MCPWM_TIMER_0);
	}
	else{
		mcpwm_set_frequency(MCPWM_UNIT_0, MCPWM_TIMER_0,frequency);
		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, 50);
	}
}

void set_buzzer_frequency(int frequency)
{
	mcpwm_set_frequency(MCPWM_UNIT_0, MCPWM_TIMER_0,frequency);

}

void stop_buzzer()
{
	mcpwm_set_frequency(MCPWM_UNIT_0, MCPWM_TIMER_0,1);
	mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, 100);
}

/*
int ch;

    // Set LED Controller with previously prepared configuration
    for (ch = 0; ch < LEDC_TEST_CH_NUM; ch++) {
        ledc_channel_config(&ledc_channel[ch]);
    }

    while (1) {
        printf("1. LEDC fade up to duty = %d\n", LEDC_TEST_DUTY);
        for (ch = 0; ch < LEDC_TEST_CH_NUM; ch++) {
            ledc_set_fade_with_time(ledc_channel[ch].speed_mode,
                    ledc_channel[ch].channel, LEDC_TEST_DUTY, LEDC_TEST_FADE_TIME);
            ledc_fade_start(ledc_channel[ch].speed_mode,
                    ledc_channel[ch].channel, LEDC_FADE_NO_WAIT);
        }
        vTaskDelay(LEDC_TEST_FADE_TIME / portTICK_PERIOD_MS);

        printf("2. LEDC fade down to duty = 0\n");
        for (ch = 0; ch < LEDC_TEST_CH_NUM; ch++) {
            ledc_set_fade_with_time(ledc_channel[ch].speed_mode,
                    ledc_channel[ch].channel, 0, LEDC_TEST_FADE_TIME);
            ledc_fade_start(ledc_channel[ch].speed_mode,
                    ledc_channel[ch].channel, LEDC_FADE_NO_WAIT);
        }
        vTaskDelay(LEDC_TEST_FADE_TIME / portTICK_PERIOD_MS);

        printf("3. LEDC set duty = %d without fade\n", LEDC_TEST_DUTY);
        for (ch = 0; ch < LEDC_TEST_CH_NUM; ch++) {
            ledc_set_duty(ledc_channel[ch].speed_mode, ledc_channel[ch].channel, LEDC_TEST_DUTY);
            ledc_update_duty(ledc_channel[ch].speed_mode, ledc_channel[ch].channel);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        printf("4. LEDC set duty = 0 without fade\n");
        for (ch = 0; ch < LEDC_TEST_CH_NUM; ch++) {
            ledc_set_duty(ledc_channel[ch].speed_mode, ledc_channel[ch].channel, 0);
            ledc_update_duty(ledc_channel[ch].speed_mode, ledc_channel[ch].channel);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
}*/