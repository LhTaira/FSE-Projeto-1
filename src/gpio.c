#include <wiringPi.h>
#include <softPwm.h>
#include <unistd.h>
#include "../inc/gpio.h"

void fan(int pid)
{
    softPwmWrite(5, pid);
    usleep(10000);
}

void resistor(int pid)
{
    softPwmWrite(4, pid);
    usleep(10000);
}