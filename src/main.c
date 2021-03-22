#include <pthread.h>
#include <stdlib.h>
#include <ncurses.h>
#include <form.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <softPwm.h>


#include "../inc/log.h" 
#include "../inc/lcd.h" 
#include "../inc/menu.h"
#include "../inc/gpio.h"
#include "../inc/uart.h"
#include "../inc/bme280.h"
#include "../inc/global.h"
#include "../inc/controller.h"

pthread_t controllerThread;
float referenceTemperature = 0;
float internalTemperature = 0;
float externalTemperature = 0;
float humidity = 0;
float pressure = 0;
int controllerShouldStop = 0;
int pidResistor = 0, pidFan = 0;

void autoReference()
{
    controllerShouldStop = 0;
    // printf("starting loop\n");
    programLoop(1);
}

void terminalReference()
{
    controllerShouldStop = 0;
    programLoop(2);
}

void stop()
{
    controllerShouldStop = 1;
}

void *control()
{
    signal(1, autoReference);
    signal(2, terminalReference);
    signal(4, stop);
    while (1)
    {
        pause();
    }
}

int main(int argc, const char *argv[])
{   
    bme280Init(1, 0x76);
    if (wiringPiSetup() != 0)
    {
        exit(1);
    }
    fd = wiringPiI2CSetup(I2C_ADDR);

    lcdLoc(LINE1);
    typeln("Olar");

    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    softPwmCreate(4, 0, 100);
    pinMode(5, OUTPUT);
    digitalWrite(5, LOW);
    softPwmCreate(5, 0, 100);
    pthread_create(&controllerThread, NULL, &control, NULL);
    createTemperatureLog();
    doMenu();

    pthread_kill(controllerThread, 9);

    return 0;
}
