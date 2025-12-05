#ifndef _ENC_H__
#define __ENC_H__

#ifdef __cplusplus
extern "C" {
#endif


//#define Kp = 100.0;
#define Kp 250.0
#define Ki 200.0
#define Kd 800.0
#define DT 0.01

void enc_read();
void enc_calc();
void enc_speed();

#ifdef __cplusplus
}
#endif

#endif
