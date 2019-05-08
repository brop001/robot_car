/*
 * RGB_led.h
 *
 *  Created on: 2019. May. 8.
 *      Author: peter.brogli
 */

#ifndef MAIN_RGB_LED_H_
#define MAIN_RGB_LED_H_

#include "driver/gpio.h"
#include "driver/mcpwm.h"

#include "delay_.h"


#define	GPIO_LED_R 27
#define	GPIO_LED_G 25
#define	GPIO_LED_B 26

#define GPIO_RGB_LED_PIN_SEL  ((1ULL<<GPIO_LED_R)|(1ULL<<GPIO_LED_G)|(1ULL<<GPIO_LED_B))

#define LED_OFF 0
#define LED_RED 1
#define LED_GREEN 2
#define LED_BLUE 3
#define LED_YELLOW 4
#define LED_CYAN 5
#define LED_MAGENTA 6
#define LED_WHITE 7

#define PWM_R 40
#define PWM_G 10
#define PWM_B 30

void RGB_led_init(void);
void set_led(int color);
void set_led_color(int red, int green, int blue);

#endif /* MAIN_RGB_LED_H_ */