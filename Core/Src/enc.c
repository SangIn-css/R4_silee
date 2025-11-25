#include "main.h"
#include "enc.h"
#include "tim.h"
#include <stdio.h>

unsigned int prev_val = 0;

void enc_read() {

	unsigned int val = (unsigned int)HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1);
	unsigned int diff =  val - prev_val;
	if(val < prev_val) {
		printf("enc = %d\n", diff + 65535);
	}
	else {
		printf("enc = %d\n", diff);
	}

    prev_val = val;
//
//    float freq = 1000000.0f / (float)diff;
//    float rps  = freq / 179.0f;
//
//    printf("freq=%.2f Hz, rpm=%.2f\n", freq, rps);

}
