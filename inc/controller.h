#ifndef _CONTROLLER_
#define _CONTROLLER_

extern float erro_total;
extern float erro_anterior;
extern float max, min;

float getAutoReference();
void getBme();
int getPid(float internalTemperature, float referenceTemperature);
void programLoop(int ref);

#endif 