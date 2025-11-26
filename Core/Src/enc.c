#include "main.h"
#include "enc.h"
#include "tim.h"
#include <stdio.h>

unsigned int prev_val = 0;
extern unsigned int g_diff;

void enc_read() {

	unsigned int val = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1);
	unsigned int diff =  val - prev_val;

	if(val < prev_val) {
		diff += 65536;
	}
//	else {
//		printf("Hz = %02f\n", 1000000.0f / (diff * 179.0f));
//	}

//	if(val < prev_val) {
//		printf("diff = %d\n", diff + 65535);
//	}
//	else {
//		printf("diff = %d\n", diff);
//	}
//	printf("rps=%.2f\n", 1000000.0f / (diff * 179.0f));

	 prev_val = val;
	 g_diff = diff;
//	if(val < prev_val) {
//		diff += 65535;
//		printf("diff = %d\n", diff);
//	}
//	else
//		printf("diff = %d\n", diff);
//    prev_val = val;
//    printf("diff = %d\n", diff);
//    float rps = 1000000.0f / (diff * 179.0f);
//    printf("rps=%.2f\n", rps);

}
