float getAutoReference()
{
    return readUart(0xc2);
}

int getPid(float internalTemperature, float referenceTemperature) {
    float error = referenceTemperature - internalTemperature;
    return (int)((error*5) + (error*1) + (error*5));
}

void programLoop(int ref)
{
    int pid;
    
    while (controllerShouldStop != 1)
    {

        switch (ref)
        {
        case 1:
            referenceTemperature = getAutoReference();
            break;
        case 2:
            break;
        }
        internalTemperature = readUart(0xc1);

        pid = getPid(internalTemperature, referenceTemperature);

        if(pid <= -40) {
            pidResistor = 0;
            resistor(pidResistor);
            pidFan = pid*-1;
            fan(pidFan);
        } else if(pid > 0) {
            pidFan = 0;
            fan(pidFan);
            pidResistor = pid;
            resistor(pidResistor);
        }

        logTemperatures()

        sleep(1);
    }
    fan(0);
    fan(0);
}