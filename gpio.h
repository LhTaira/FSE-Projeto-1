#include <wiringPi.h>
#include <softPwm.h>


void fanOn()
{
    softPwmWrite(5, 99);
    usleep(10000);
}

void fanOff()
{
    softPwmWrite(5, 0);
    usleep(10000);
}

void resistorOn()
{
    softPwmWrite(4, 99);
    usleep(10000);
}

void resistorOff()
{
    softPwmWrite(4, 0);
    usleep(10000);
}