#include <unistd.h>
#include <time.h>
#include "log.h"
#include "global.h"
#include "../inc/controller.h"
#include "../inc/gpio.h"
#include "../inc/uart.h"
#include "../inc/bme280.h"
#include "../inc/lcd.h"

float erro_total = 0;
float erro_anterior = 0;
float max = 100, min = -100;

float getAutoReference()
{
    return readUart(0xc2);
}

void getBme()
{
    int teInt, pressureInt, humidityInt;
    bme280ReadValues(&teInt, &pressureInt, &humidityInt);
    externalTemperature = ((float)teInt) / 100.0;
    pressure = pressureInt / 100;
    humidity = humidityInt / 100;
}

int getPid(float internalTemperature, float referenceTemperature)
{
    float error = referenceTemperature - internalTemperature;
    erro_total += error;

    if (erro_total > max)
    {
        erro_total = max;
    }
    else if (erro_total < min)
    {
        erro_total = min;
    }

    float delta = error - erro_anterior;

    float pid = 5 * error + erro_total + 35 * delta;
    if (pid > max)
    {
        pid = max;
    }
    else if (pid < min)
    {
        pid = min;
    }
    erro_anterior = error;
    return pid;
}

void programLoop(int ref)
{
    int pid;
    time_t loopStart, loopEnd;

    while (controllerShouldStop != 1)
    {
        time(&loopStart);

        switch (ref)
        {
        case 1:
            referenceTemperature = getAutoReference();
            break;
        case 2:
            break;
        }
        getBme();
        internalTemperature = readUart(0xc1);
        writeLcd();

        pid = getPid(internalTemperature, referenceTemperature);

        if (pid <= -40)
        {
            pidResistor = 0;
            resistor(pidResistor);
            pidFan = pid * -1;
            fan(pidFan);
        }
        else if (pid > 0)
        {
            pidFan = 0;
            fan(pidFan);
            pidResistor = pid;
            resistor(pidResistor);
        }

        logTemperatures();

        time(&loopEnd);
        while (loopEnd == loopStart)
        {
            usleep(100);
            time(&loopEnd);
        }
    }
    resistor(0);
    fan(0);
}