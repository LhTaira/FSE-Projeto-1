float getAutoReference()
{
    return readUart(0xc2);
}

float getpotentiometerReference()
{
}

float geterminalReference()
{
}

void programLoop(int ref)
{
    
    while (controllerShouldStop != 1)
    {

        switch (ref)
        {
        case 1:
            // referenceTemperature++;
            // printf("Reading auto\n");
            referenceTemperature = getAutoReference();
            break;

        case 2:
            referenceTemperature = getpotentiometerReference();
            break;

        case 3:
            referenceTemperature = geterminalReference();
            break;
        }
        // internalTemperature++,;
        // printf("Reading internal\n");
        internalTemperature = readUart(0xc1);

        sleep(1);
        // fanOn();
        // fanOff();
    }
}