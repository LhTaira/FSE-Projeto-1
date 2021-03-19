#include <pthread.h>
pthread_t controllerThread;
float referenceTemperature = 0;
float internalTemperature = 0;
float externalTemperature = 0;
int controllerShouldStop = 0;
#include <ncurses.h>
#include <form.h>
#include <stdio.h>
#include "menu.h"
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include "uart.h"
#include "controller.h"
// #include "gpio.h"

void autoReference()
{
    controllerShouldStop = 0;
    // printf("starting loop\n");
    // programLoop(1);
}

void potentiometerReference()
{
    programLoop(2);
}

void terminalReference()
{
    programLoop(3);
}

void stop()
{
    controllerShouldStop = 1;
}

void *control()
{
    signal(1, autoReference);
    signal(2, potentiometerReference);
    signal(3, terminalReference);
    signal(4, stop);
    while (1)
    {
        pause();
    }
}

int main(int argc, const char *argv[])
{
    // if(wiringPiSetup() != 0) {
    //     printf("fukkk\n\n");
    // }
    // pinMode(0, OUTPUT);
    // pinMode(4, OUTPUT);
    // digitalWrite(4, LOW);
    // softPwmCreate(4, 0, 100);
    // pinMode(5, OUTPUT);
    // digitalWrite(5, LOW);
    // softPwmCreate(5, 0, 100);
    // pthread_create(&controllerThread, NULL, &control, NULL);

    // pthread_kill(controllerThread, 1);
    // while(1) {
    //     // fanOn();
    //     pause();

    // }
    doMenu();

    // pthread_kill(controllerThread, int sig);

    return 0;
}
