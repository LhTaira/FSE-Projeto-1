
#ifndef __BME280__
#define __BME280__

extern int file_i2c;
extern int calT1, calT2, calT3;
extern int calP1, calP2, calP3, calP4, calP5, calP6, calP7, calP8, calP9;
extern int calH1, calH2, calH3, calH4, calH5, calH6;

int bme280Init(int iChannel, int iAddr);
int bme280ReadValues(int *T, int *P, int *H);

#endif