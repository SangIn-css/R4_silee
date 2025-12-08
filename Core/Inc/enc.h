#ifndef _ENC_H__
#define __ENC_H__

#ifdef __cplusplus
extern "C" {
#endif


#define Kp 400.0
#define Ki  700.0
#define Kd 900.0

void enc_read();
void enc_calc();
void enc_speed(float DT);

#ifdef __cplusplus
}
#endif

#endif
