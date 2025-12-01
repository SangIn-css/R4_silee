#include "main.h"
#include "enc.h"
#include "tim.h"
#include <stdio.h>

unsigned int prev_val = 0;
unsigned int true_diff = 0;
unsigned int last_diff = 0;
float rps = 15.0;

void enc_read() {

	unsigned int val = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1);
	unsigned int diff =  val - prev_val;

	if(val < prev_val) {
		diff += 65536;
	}

	 prev_val = val;
	 true_diff = diff;
}

void enc_calc() {
	if(true_diff != last_diff) {
		  last_diff = true_diff;
		  rps = 1000000.0 / (true_diff * 180.0);
//		  printf("enc_diff = %d\n", g_diff);
		 if((rps > 12) && (rps < 18)){
			  printf("Hz = %.4f\tdiff = %.4f\n", rps, rps - 15.0);
		}
	}
}

void enc_speed() {

	float diff = 0.0;
	unsigned int k = 50;
	unsigned int pulse = 1224;

	if (rps > 15) {
		diff = rps - 15;
		htim3.Instance->CCR1 = pulse - (k * diff);
	}
	else if (rps < 15) {
		diff = 15  - rps;
		htim3.Instance->CCR1 = pulse + (k * diff);
	}
}
