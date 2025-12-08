#include "main.h"
#include "enc.h"
#include "tim.h"
#include <stdio.h>

int prev_val = 0;
int val = 0;
int start_val = 0;
int end_val = 0;
int read_done = 1;
int slt_val = 0;
int enc_cnt = 0;
int start_enc_cnt = 0;
int end_enc_cnt = 0;
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
		}
	}

	 prev_val = val;
}

void enc_calc() {
	if( (start_val != 0) && (end_val != 0) ) {		// after reading  first standard slits
		if(read_done == 1) {
			slt_val = (end_val - start_val) + (end_enc_cnt - start_enc_cnt) * 65536;
			start_val = end_val;
			start_enc_cnt = end_enc_cnt;
			read_done = 0;
			if( (slt_val > 60000) && (slt_val < 70000) ) {	// except missing standard slit
				rps = 1000000.0 / slt_val;
				float dt = slt_val / 1000000.0;
				printf("rps  = %.3f   \t diff = %.3f\n\n", rps, rps - 15.0);
				enc_speed(dt);
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

}
