#include "main.h"
#include "enc.h"
#include "tim.h"
#include <stdio.h>

unsigned int prev_val = 0;
unsigned int val = 0;
unsigned int enc_cnt = 0;
unsigned int start_enc_cnt = 0;
unsigned int end_enc_cnt = 0;
unsigned int start_val = 0;
unsigned int end_val = 0;
unsigned int start = 0;
int slt_val = 0;
float rps = 15.0;
float integ = 0.0;
float prev_diff = 0.0;

void enc_read() {

	val = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1);

	if(val < prev_val) {
		enc_cnt++;
	}

	if( (val - prev_val > 700) && (val - prev_val < 800) ) {
		if(start == 0) {				// standard slit
			start_val = val;
			start = 1;
			start_enc_cnt = enc_cnt;
		}
		else {								// next slit
			end_val = val;
			start = 0;
			end_enc_cnt = enc_cnt;
		}
	}

	 prev_val = val;
}

void enc_calc() {
	if( (val != 0) && (prev_val != 0) ) {		// after first enc_read
		if(start == 0) {
			slt_val = end_val - start_val;
			slt_val += (end_enc_cnt - start_enc_cnt) * 65536;
			enc_cnt = 0;
		}

		if( (slt_val > 60000) && (slt_val < 70000) ) {
			rps = 1000000.0 / slt_val;
			printf("slt_val = %d   \t rps  = %.3f   \t diff = %.3f\n\n", slt_val, rps, rps - 15.0);
			prev_slt_val = slt_val;
		}

	}
}

void enc_speed() {

	float Kp = 1.00;
//	float Kp = 10.0;
	float Ki = 0.007;
	float Kd = 400.00;

    float pulse = 2455.0;
    float diff = 15.0 - rps;
    float deriv = diff - prev_diff;
    prev_diff = diff;

    integ += diff;
    if (integ > INTEG_MAX)      integ = INTEG_MAX;
    else if (integ < -INTEG_MAX) integ = -INTEG_MAX;

    float ctrl_sig = (Kp * diff) + (Ki * integ) + (Kd * deriv);

	htim8.Instance->CCR1 = pulse + ctrl_sig;
	pulse = htim8.Instance->CCR1;

}
