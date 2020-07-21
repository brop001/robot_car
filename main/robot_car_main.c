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
#include "infrared.h"

#include "broglisz_functions.h"

//static const char* TAG = "robot_car";

TaskHandle_t xservo_test_Handle;
TaskHandle_t xRGB_led_test_Handle;
TaskHandle_t xbuzzer_test_Handle;
TaskHandle_t xultrasonic_test_Handle;
TaskHandle_t xmotor_test_Handle;
TaskHandle_t xinfrared_test_Handle;
TaskHandle_t xdemo_task_Handle;
TaskHandle_t xmusic_task_Handle;
TaskHandle_t xmoving_task_Handle;

void servo_test(void *parameters);
void RGB_led_test(void *parameters);
void buzzer_test(void *parameters);
void ultrasonic_test(void *parameters);
void motor_test(void *parameters);
void infrared_test(void *parameters);
void demo_task(void *parameters);
void music_task(void *parameters);
void moving_task(void *parameters);

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

void motor_test(void *parameters)
{
    while(1){
        set_motor_R(500,1,50);
        set_motor_L(500,1,60);
        delay_ms(1000);

        set_motor_R(200,-1,50);
        set_motor_L(200,-1,60);
        delay_ms(3000);

        set_motor_R(2000,1,50);
        set_motor_L(2000,-1,50);
        delay_ms(5000);
        
        set_motor_R(2000,-1,50);
        set_motor_L(2000,1,50);
        delay_ms(5000);
    }
}

void infrared_test(void *parameters)
{
    while(1){
        printf("L2: %d  L1: %d  R1: %d  R2: %d\n", get_ir_sensor_L2(),get_ir_sensor_L1(),get_ir_sensor_R1(),get_ir_sensor_R2());
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

void music_task(void *parameters)
{
    while(1){
        star_wars_music();
    }
}

void moving_task(void *parameters)
{
     while(1){
        move_car_aviod();
     }
}

void app_main()
{   
    buzzer_init();
    RGB_led_init();
    ultrasonic_init();
    motor_init();
    servo_init();
    ir_sensor_init();

    //xTaskCreate(&servo_test, "servo_test", 1024 * 12, NULL, 5, xservo_test_Handle);
    //xTaskCreate(&RGB_led_test, "RGB_led_test", 1024 * 12, NULL, 5, xRGB_led_test_Handle);
    //xTaskCreate(&buzzer_test, "buzzer_test", 1024 * 12, NULL, 5, xbuzzer_test_Handle);
    //xTaskCreate(&ultrasonic_test, "ultrasonic_test", 1024 * 12, NULL, 5, xultrasonic_test_Handle);
    //xTaskCreate(&motor_test, "motor_test", 1024 * 12, NULL, 5, xmotor_test_Handle);
    //xTaskCreate(&infrared_test, "infrared_test", 1024 * 12, NULL, 5, xinfrared_test_Handle);
    //xTaskCreate(&demo_task, "demo_task", 1024 * 12, NULL, 5, xdemo_task_Handle);
    xTaskCreate(&music_task, "music_task", 1024 * 12, NULL, 5, xmusic_task_Handle);
    //xTaskCreate(&moving_task, "moving_task", 1024 * 12, NULL, 5, xmoving_task_Handle);
    

    
    for(;;){
        delay_ms(100);
    }
}
