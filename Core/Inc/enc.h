#ifndef _ENC_H__
#define __ENC_H__

#ifdef __cplusplus
extern "C" {
#endif

#define INTEG_MAX 50000
#define DT 0.01

void enc_read();
void enc_calc();
void enc_speed();

#ifdef __cplusplus
}
#endif

#endif
