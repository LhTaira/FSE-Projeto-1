#include <stdlib.h>
#include "../inc/lcdDriver.h"
#include "../inc/global.h"

void setupLcd()
{
    fd = wiringPiI2CSetup(I2C_ADDR);
    lcd_init();
}

void writeLcd() {
    ClrLcd();
    lcdLoc(LINE1);
    typeln("TI:");
    typeFloat(internalTemperature);
    typeln(" TE:");
    typeFloat(externalTemperature);
    lcdLoc(LINE2);
    typeln("TR:");
    typeFloat(referenceTemperature);
    typeln(" (:");
}

void clearLcd() 
{
    ClrLcd();
}