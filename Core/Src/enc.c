#include "main.h"
#include "enc.h"
#include "tim.h"
#include <stdio.h>

unsigned int prev_val = 0;
unsigned int  current_diff = 0;
unsigned int val = 0;
unsigned int last_diff = 0;
int slt_cnt = 0;
unsigned int enc_cnt = 0;
unsigned int start_enc_cnt = 0;
unsigned int end_enc_cnt = 0;
unsigned int start_val = 0;
unsigned int end_val = 0;
unsigned int start = 0;
float rps = 15.0;
float integ = 0.0;

void enc_read() {

	val = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1);
	unsigned int diff =  val - prev_val;

	if(val < prev_val) {
		diff += 65536;
		enc_cnt++;
	}

	if(diff > 700 && diff < 800) {

		if(start == 0) {
			start_val = val;
			start = 1;
			start_enc_cnt = enc_cnt;
		}

		else {
			end_val = val;
			start = 0;
			end_enc_cnt = enc_cnt;
		}
	}

	 prev_val = val;
	 current_diff = diff;
}

void enc_calc() {
	if(current_diff != 0) {
		if(start == 0) {
			slt_cnt = end_val - start_val;
			slt_cnt += (end_enc_cnt - start_enc_cnt) * 65536;
			enc_cnt = 0;
		}
		if(slt_cnt != 0) {
			rps = 1000000.0 / slt_cnt;
		}

		printf("slt_cnt = %d   \t rps  = %.3f   \t dif = %.3f\n\n", slt_cnt, rps, rps - 15.0);
	}
}

void enc_speed() {

	float Kp = 30.0;
	float Ki = 4.0;
	float Kd = 170.00;
	float prev_diff = 0.0;

    float pulse = 2460.0;
    float ctrl_sig;
    float diff = 15.0 - rps;
    float deriv = (diff - prev_diff) / 0.01;
    integ += diff * 0.01;
    prev_diff = diff;

    ctrl_sig = (Kp * diff) + (Ki * integ) + (Kd * deriv);

	htim8.Instance->CCR1 = pulse + ctrl_sig * 0.01;
	pulse = htim8.Instance->CCR1;

}
