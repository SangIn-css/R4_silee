#include "main.h"
#include "enc.h"
#include "tim.h"
#include <stdio.h>

uint16_t prev_val = 0;
uint16_t val = 0;
uint16_t start_val = 0;
uint16_t end_val = 0;
uint16_t read_done = 1;
uint16_t slt_val = 0;
uint32_t enc_cnt = 0;
uint32_t start_enc_cnt = 0;
uint32_t end_enc_cnt = 0;
float rps = 15.0;
float integ = 0.0;
float prev_diff = 0.0;

void enc_read() {

	val = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1);
	if(val < prev_val) {
		enc_cnt++;
	}

	if( (val - prev_val > 700) && (val - prev_val < 800) ) {
		if(read_done == 1) {				// standard slit
			start_val = val;
			read_done = 0;
			start_enc_cnt = enc_cnt;
		}
		else {								// next slit
			end_val = val;
			read_done = 1;
			end_enc_cnt = enc_cnt;
			printf("f\n");
		}
	}

	 prev_val = val;
}

void enc_calc() {
	if( (start_val != 0) && (end_val != 0) ) {		// after reading standard slits
		if(read_done == 1) {
			slt_val = (end_val - start_val) + (end_enc_cnt - start_enc_cnt) * 65536;
			start_val = end_val;
			start_enc_cnt = end_enc_cnt;
			read_done = 0;
			printf("a\n");
			if( (slt_val > 60000) && (slt_val < 70000) ) {	// except missing standard slit
				rps = 1000000.0 / slt_val;
				float dt = slt_val / 1000000.0;
				enc_speed(dt);
				printf("slt_val = %d   \t rps  = %.3f   \t diff = %.3f\n\n", slt_val, rps, rps - 15.0);
			}
		}
	}
}

void enc_speed(float DT) {

	float prev_diff = 0.0;

    float pulse = 2455.0;
    float diff = 15.0 - rps;
    float deriv = (diff - prev_diff) / DT;
    integ += diff * DT;
    prev_diff = diff;

    float ctrl_sig = (Kp * diff) + (Ki * integ) + (Kd * deriv);
    if(ctrl_sig > 500.0 / DT) {
    	ctrl_sig = 500 * DT;
    }
	htim8.Instance->CCR1 = pulse + ctrl_sig * DT;
	pulse = htim8.Instance->CCR1;

	printf("k\n");
}
