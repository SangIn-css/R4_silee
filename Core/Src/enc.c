#include "main.h"
#include "enc.h"
#include "tim.h"
#include <stdio.h>

unsigned int prev_val = 0;
unsigned int g_diff = 0;
unsigned int last_diff = 0;
float rps = 0;

void enc_read() {

	unsigned int val = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1);
	unsigned int diff =  val - prev_val;

	if(val < prev_val) {
		diff += 65536;
	}

	 prev_val = val;
	 g_diff = diff;

}

void enc_calc() {
	if(g_diff != last_diff) {
		  last_diff = g_diff;
		  rps = 1000000.0f / (g_diff * 180.0f);
//		  printf("diff = %d\n", g_diff);
		 if((rps > 14) && (rps < 16)){
			  printf("rps = %.4f     diff = %.4f\n", rps, rps - 15);
		}
	}
}

void enc_speed() {
	htim3.Instance->CCR1 = 1225;
}
