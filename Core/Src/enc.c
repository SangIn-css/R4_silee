#include "main.h"
#include "enc.h"
#include "tim.h"
#include <stdio.h>

unsigned int prev_val = 0;
unsigned int  current_diff = 0;
unsigned int val = 0;
unsigned int last_diff = 0.0;
float rps = 15.0;
float integ = 0.0;

void enc_read() {

	val = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1);
	unsigned int diff =  val - prev_val;

	if(val < prev_val) {
		diff += 65536;
	}

	 prev_val = val;
	 current_diff = diff;
}

void enc_calc() {
	if(current_diff != 0) {
		  rps = 1000000.0 / (current_diff * 180.0);
		  printf("val  = %d\t   enc_diff = %d\n", val, current_diff);
//		 if((rps > 14) && (rps < 16)) {
//			  printf("Hz = %.3f\tdiff = %.3f\n", rps, rps - 15.0);
		}
//	}
}

void enc_speed() {

	float Kp = 30.0;
	float Ki = 4.0;
	float Kd = 170.00;
	float prev_diff = 0.0;

    float pulse = 2445.0;
    float ctrl_sig;
    float diff = 15.0 - rps;
    float deriv = (diff - prev_diff) / 0.01;
    integ += diff * 0.01;
    prev_diff = diff;

    ctrl_sig = (Kp * diff) + (Ki * integ) + (Kd * deriv);

	htim8.Instance->CCR1 = pulse + ctrl_sig * 0.01;
	pulse = htim8.Instance->CCR1;

}

