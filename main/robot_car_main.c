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
#include "buzzer.h"
#include "RGB_led.h"
#include "ultrasonic.h"
#include "motor_driver.h"
#include "servo.h"


static const char* TAG = "robot_car";

void servo_test(void *parameters);
void RGB_led_test(void *parameters);
void buzzer_test(void *parameters);
void ultrasonic_test(void *parameters);
void demo_task(void *parameters);


void servo_test(void *parameters)
{
    while(1){
        for(int i=0;i<181;i++)
        {
           
            set_servo(i);
            printf("Servo duty cycle: %d\n",i);
            //if(!i)delay_ms(5000);
            delay_ms(10);
        }
        for(int i=180;i>0;i--)
        {
            set_servo(i);
            printf("Servo duty cycle: %d\n",i);
            //if(!i)delay_ms(5000);
            delay_ms(10);
        }
        //set_servo(0);
        //delay_ms(2000);
        //set_servo(180);
        //delay_ms(2000);
    }
}

void RGB_led_test(void *parameters)
{
    while(1){
        for(int i=0;i<8;i++){
			set_led(i);
			delay_ms(1000);
            
		}
    }
}

void buzzer_test(void *parameters)
{
    while(1){
        delay_ms(1000);
        buzzer(200,500);
        delay_ms(1000);
        buzzer(1000,500);
    }
}

void ultrasonic_test(void *parameters)
{
    float us_distance_in_cm = 0;
    while(1){
        us_distance_in_cm = get_us_distance_in_cm();
        if(us_distance_in_cm == EXIT_FAILURE)printf("Distance measurement failed!\n");
        else printf("us_distance_in_ms: %.2f\n",us_distance_in_cm);
        delay_ms(100);
    }
}

void demo_task(void *parameters)
{
    int us_distance_in_cm = 0;
    int state = 0;
    start_buzzer(0);
    while(1){

        switch(state)
        {
            case 0: 
                set_servo(state);
                printf("Servo: %d\n",state);
                set_led(LED_RED);
                delay_ms(2000);
                start_buzzer(10);
                for(int i=0;i<100;i++){
                    
                    us_distance_in_cm = get_us_distance_in_cm();
                    if(us_distance_in_cm == EXIT_FAILURE)printf("Distance measurement failed!\n");
                    else printf("us_distance_in_cm: %d\n",us_distance_in_cm);    

                    if((us_distance_in_cm>5)&&(us_distance_in_cm<40)){
                        set_buzzer_frequency((us_distance_in_cm-5)*100);
                    }
                    delay_ms(60);
                }
                stop_buzzer();
                state = 45;
                break;

            case 45:
                set_servo(state);
                printf("Servo: %d\n",state);
                set_led(LED_BLUE);
                delay_ms(2000);
                start_buzzer(10);
                for(int i=0;i<100;i++){
                    
                    us_distance_in_cm = get_us_distance_in_cm();
                    if(us_distance_in_cm == EXIT_FAILURE)printf("Distance measurement failed!\n");
                    else printf("us_distance_in_cm: %d\n",us_distance_in_cm);                    
                    
                    if((us_distance_in_cm>5)&&(us_distance_in_cm<40)){
                        set_buzzer_frequency((us_distance_in_cm-5)*100);
                    }
                    delay_ms(60);
                }
                stop_buzzer();
                state = 90;
                break;

            case 90:
                set_servo(state);
                printf("Servo: %d\n",state);
                set_led(LED_GREEN);
                delay_ms(2000);
                start_buzzer(10);
                for(int i=0;i<100;i++){
                    
                    us_distance_in_cm = get_us_distance_in_cm();
                    if(us_distance_in_cm == EXIT_FAILURE)printf("Distance measurement failed!\n");
                    else printf("us_distance_in_cm: %d\n",us_distance_in_cm);                    
                    
                    if((us_distance_in_cm>5)&&(us_distance_in_cm<40)){
                        set_buzzer_frequency((us_distance_in_cm-5)*100);
                    }
                    delay_ms(60);
                }
                stop_buzzer();
                state = 135;
                break;
                
            case 135:
                set_servo(state);
                printf("Servo: %d\n",state);
                set_led(LED_YELLOW);
                delay_ms(2000);
                start_buzzer(10);
                for(int i=0;i<100;i++){
                    
                    us_distance_in_cm = get_us_distance_in_cm();
                    if(us_distance_in_cm == EXIT_FAILURE)printf("Distance measurement failed!\n");
                    else printf("us_distance_in_cm: %d\n",us_distance_in_cm);                    
                    
                    if((us_distance_in_cm>5)&&(us_distance_in_cm<40)){
                        set_buzzer_frequency((us_distance_in_cm-5)*100);
                    }
                    delay_ms(60);
                }
                stop_buzzer();
                state = 180;
                break;

            case 180:
                set_servo(state);
                printf("Servo: %d\n",state);
                set_led(LED_CYAN);
                delay_ms(2000);
                start_buzzer(10);
                for(int i=0;i<100;i++){
                    
                    us_distance_in_cm = get_us_distance_in_cm();
                    if(us_distance_in_cm == EXIT_FAILURE)printf("Distance measurement failed!\n");
                    else printf("us_distance_in_cm: %d\n",us_distance_in_cm);                    
                    
                    if((us_distance_in_cm>5)&&(us_distance_in_cm<40)){
                        set_buzzer_frequency((us_distance_in_cm-5)*100);
                    }
                    delay_ms(60);
                }
                stop_buzzer();
                state = 0;
                break;

            default:
                state = 0;
                break;
        }
    }
}

void app_main()
{   
    buzzer_init();
    RGB_led_init();
    ultrasonic_init();
    motor_init();
    servo_init();

    
    //xTaskCreate(&RGB_led_test, "RGB_led_test", 1024 * 12, NULL, 5, NULL);
    //xTaskCreate(&buzzer_test, "buzzer_test", 1024 * 12, NULL, 5, NULL);
    //xTaskCreate(&ultrasonic_test, "ultrasonic_test", 1024 * 12, NULL, 5, NULL);
    //xTaskCreate(&demo_task, "demo_task", 1024 * 12, NULL, 5, NULL);
    printf("set_motor_R_fwd(30)\n");
    //set_motor_R_fwd(70.0);
    set_motor_L_fwd(70.0);
    int count = 0;
    for(;;){
            
            //delay_ms(100);

            pcnt_get_counter_value(PCNT_UNIT_0, &count);
            printf("%d.\n",count);
            delay_ms(1000);
            /*printf("set_motor_R_rvs(50)\n");
            set_motor_R_fwd(50.0);
            set_motor_L_fwd(50.0);
            delay_ms(1000);
            printf("set_motor_R_stop()\n");
            set_motor_R_stop();
            set_motor_L_stop();
            delay_ms(1000);
            printf("set_motor_L_fwd(50)\n");
            set_motor_L_fwd(50.0);
            set_motor_L_rvs(50.0);
            delay_ms(1000);
            printf("set_motor_L_rvs(80)\n");
            set_motor_L_rvs(100.0);
            set_motor_L_rvs(100.0);
            delay_ms(1000);
            printf("set_motor_L_stop()\n");
            set_motor_L_stop();
            set_motor_R_stop();
            delay_ms(1000);*/

    }
}
