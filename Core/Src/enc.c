#include "main.h"
#include "enc.h"
#include "tim.h"
#include <stdio.h>

unsigned int prev_val = 0;
unsigned int current_diff = 0;
unsigned int last_diff = 0;
float rps = 15.0;
float integ = 0.0;

void enc_read() {

	unsigned int val = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1);
	unsigned int diff =  val - prev_val;

	if(val < prev_val) {
		diff += 65536;
	}

	 prev_val = val;
	 current_diff = diff;
}

void enc_calc() {
	if(current_diff != last_diff) {
		  last_diff = current_diff;
		  rps = 1000000.0 / (current_diff * 180.0);
//		  printf("enc_diff = %d\n", g_diff);
		 if((rps > 12) && (rps < 18)){
			  printf("Hz = %.4f\tdiff = %.4f\n", rps, rps - 15.0);
		}
	}
}

void enc_speed() {

	float Kp = 200.0;
	float Ki = 100.0;
	float Kd = 100.00;
	float prev_diff = 0.0;

    float pulse = 1225.0;
    float ctrl_sig;
    float diff = 15.0 - rps;
    float deriv = (diff - prev_diff) / 0.01;
    integ += diff * 0.01;
    prev_diff = diff;

    ctrl_sig = (Kp * diff) + (Ki * integ) + (Kd * deriv);

	htim3.Instance->CCR1 = pulse + ctrl_sig * 0.01;
	pulse = htim3.Instance->CCR1;

}

