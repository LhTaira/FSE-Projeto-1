#ifndef _GLOBAL_
#define _GLOBAL_

#include <pthread.h>

#define I2C_ADDR   0x27

extern pthread_t controllerThread;
extern float referenceTemperature;
extern float internalTemperature;
extern float externalTemperature;
extern float humidity;
extern float pressure;
extern int controllerShouldStop;
extern int pidResistor, pidFan;

#endif 