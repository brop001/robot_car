/*
 * broglisz_functions.h
 *
 *  Created on: 2020. jul. 21.
 *      Author: peter.brogli
 */

#ifndef MAIN_BROGLISZ_FUNCTIONS_H_
#define MAIN_BROGLISZ_FUNCTIONS_H_

#define NOTE_c 261
#define NOTE_d 294
#define NOTE_e 329
#define NOTE_f 349
#define NOTE_g 391
#define NOTE_gS 415
#define NOTE_a 440
#define NOTE_aS 455
#define NOTE_b 466
#define NOTE_cH 523
#define NOTE_cSH 554
#define NOTE_dH 587
#define NOTE_dSH 622
#define NOTE_eH 659
#define NOTE_fH 698
#define NOTE_fSH 740
#define NOTE_gH 784
#define NOTE_gSH 830
#define NOTE_aH 880

void buzzer_led(int freq, int delay);
void star_wars_music();
void move_car_aviod();

#endif /* MAIN_BROGLISZ_FUNCTIONS_H_ */