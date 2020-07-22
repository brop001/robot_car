/*
 * broglisz_functions.c
 *
 *  Created on: 2020. jul. 21.
 *      Author: peter.brogli
 */

#include "broglisz_functions.h"
#include "RGB_led.h"
#include "buzzer.h"
#include "motor_driver.h"
#include "delay_.h"
#include "infrared.h"



void buzzer_led(int freq, int delay){
    buzzer(freq,delay);
    if((freq>=261)&&(freq<349))
    {
        set_led(LED_RED);
    }
    if((freq>=349)&&(freq<455))
    {
        set_led(LED_GREEN);
    }
    if((freq>=455)&&(freq<554))
    {
        set_led(LED_BLUE);
    }
    if((freq>=554)&&(freq<622))
    {
        set_led(LED_YELLOW);
    }
    if((freq>=622)&&(freq<698))
    {
        set_led(LED_CYAN);
    }
    if((freq>=698)&&(freq<784))
    {
        set_led(LED_MAGENTA);
    }
    if((freq>=784)&&(freq<880))
    {
        set_led(LED_WHITE);
    }

}

void star_wars_music(){
    
    while(1)
    {
        buzzer_led(NOTE_a, 500);
        buzzer_led(NOTE_a, 500);
        buzzer_led(NOTE_a, 500);
        buzzer_led(NOTE_f, 350);
        buzzer_led(NOTE_cH, 150);
        buzzer_led(NOTE_a, 500);
        buzzer_led(NOTE_f, 350);
        buzzer_led(NOTE_cH, 150);
        buzzer_led(NOTE_a, 650);
        
        delay_ms(500);
        
        buzzer_led(NOTE_eH, 500);
        buzzer_led(NOTE_eH, 500);
        buzzer_led(NOTE_eH, 500);
        buzzer_led(NOTE_fH, 350);
        buzzer_led(NOTE_cH, 150);
        buzzer_led(NOTE_gS, 500);
        buzzer_led(NOTE_f, 350);
        buzzer_led(NOTE_cH, 150);
        buzzer_led(NOTE_a, 650);
        
        delay_ms(500);


        //Play second section
        //secondSection();
        buzzer_led(NOTE_aH, 500);
        buzzer_led(NOTE_a, 300);
        buzzer_led(NOTE_a, 150);
        buzzer_led(NOTE_aH, 500);
        buzzer_led(NOTE_gSH, 325);
        buzzer_led(NOTE_gH, 175);
        buzzer_led(NOTE_fSH, 125);
        buzzer_led(NOTE_fH, 125);
        buzzer_led(NOTE_fSH, 250);
        
        delay_ms(325);
        
        buzzer_led(NOTE_aS, 250);
        buzzer_led(NOTE_dSH, 500);
        buzzer_led(NOTE_dH, 325);
        buzzer_led(NOTE_cSH, 175);
        buzzer_led(NOTE_cH, 125);
        buzzer_led(NOTE_b, 125);
        buzzer_led(NOTE_cH, 250);
        
        delay_ms(350);


        //Variant 1
        buzzer_led(NOTE_f, 250);
        buzzer_led(NOTE_gS, 500);
        buzzer_led(NOTE_f, 350);
        buzzer_led(NOTE_a, 125);
        buzzer_led(NOTE_cH, 500);
        buzzer_led(NOTE_a, 375);
        buzzer_led(NOTE_cH, 125);
        buzzer_led(NOTE_eH, 650);
        
        delay_ms(500);
        
        //Repeat second section
        //secondSection();
        buzzer_led(NOTE_aH, 500);
        buzzer_led(NOTE_a, 300);
        buzzer_led(NOTE_a, 150);
        buzzer_led(NOTE_aH, 500);
        buzzer_led(NOTE_gSH, 325);
        buzzer_led(NOTE_gH, 175);
        buzzer_led(NOTE_fSH, 125);
        buzzer_led(NOTE_fH, 125);
        buzzer_led(NOTE_fSH, 250);
        
        delay_ms(325);
        
        buzzer_led(NOTE_aS, 250);
        buzzer_led(NOTE_dSH, 500);
        buzzer_led(NOTE_dH, 325);
        buzzer_led(NOTE_cSH, 175);
        buzzer_led(NOTE_cH, 125);
        buzzer_led(NOTE_b, 125);
        buzzer_led(NOTE_cH, 250);
        
        delay_ms(350);


        //Variant 2
        buzzer_led(NOTE_f, 250);
        buzzer_led(NOTE_gS, 500);
        buzzer_led(NOTE_f, 375);
        buzzer_led(NOTE_cH, 125);
        buzzer_led(NOTE_a, 500);
        buzzer_led(NOTE_f, 375);
        buzzer_led(NOTE_cH, 125);
        buzzer_led(NOTE_a, 650);
    }
}



void move_car_avoid(){

    int a,b,c,d;
    int fwd_request = 1;
    

    while(1)
    {
        a = get_ir_sensor_R2();
        b = get_ir_sensor_R1();
        c = get_ir_sensor_L1();
        d = get_ir_sensor_L2();
        
        if((a==IR_FREE)&&(b==IR_FREE)&&(c==IR_FREE)&&(d==IR_FREE))
        {
            if(fwd_request==1){
                printf("FOWARD\n");
                start_car(1,50);
                fwd_request=0;
            }
        }
        if(((a==IR_DETECT)||(b==IR_DETECT))&&(c==IR_FREE)&&(d==IR_FREE))
        {
            printf("DETECT OBSTACLE AT RIGHT\n");
            stop_car();
            set_motor_R(500,1,50);
            fwd_request=1;
        }
        if((a==IR_FREE)&&(b==IR_FREE)&&((c==IR_DETECT)||(d==IR_DETECT)))
        {
            printf("DETECT OBSTACLE AT LEFT\n");
            stop_car();
            set_motor_L(500,1,50);
            fwd_request=1;
        }
        delay_ms(50);
    }
}