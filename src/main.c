#include <pthread.h>
pthread_t controllerThread;
float referenceTemperature = 0;
float internalTemperature = 0;
float externalTemperature = 0;
int controllerShouldStop = 0;
#include <stdlib.h>
#include <ncurses.h>
#include <form.h>
#include "menu.h"
#include <sys/types.h>
#include <signal.h>
#include "uart.h"
#include "gpio.h"
#include "controller.h"

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
    if (wiringPiSetup() != 0)
    {
        printf("fukkk\n\n");
    }
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    softPwmCreate(4, 0, 100);
    pinMode(5, OUTPUT);
    digitalWrite(5, LOW);
    softPwmCreate(5, 0, 100);
    pthread_create(&controllerThread, NULL, &control, NULL);

    // pthread_kill(controllerThread, 1);
    // while(1) {
    //     // fanOn();
    //     pause();

    // }
    doMenu();

    pthread_kill(controllerThread, 9);

    return 0;
}
