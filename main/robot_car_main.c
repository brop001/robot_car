/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

#include "delay_.h"
#include "gpio_init.h"
#include "buzzer.h"
#include "RGB_led.h"
#include "ultrasonic.h"


static const char* TAG = "robot_car";

void app_main()
{   
    buzzer_init();
    RGB_led_init();
    ultrasonic_init();

    int us_distance_in_cm = 0;

    for(;;){
        //printf("Hello world\n");
        //delay_ms(1000);
        //buzzer(200,500);
        
        us_distance_in_cm = get_us_distance_in_cm();
        if(us_distance_in_cm == EXIT_FAILURE)printf("Distance measurement failed!\n");
        else printf("us_distance_in_ms: %d\n",us_distance_in_cm);
        delay_ms(100);

        /*for(int i=0;i<8;i++){
			set_led(i);
			delay_ms(1000);
            
		}*/

    }
}
