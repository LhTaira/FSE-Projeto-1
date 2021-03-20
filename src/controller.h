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
            resistor(0);
            fan(pid*-1);
        } else if(pid > 0) {
            fan(0);
            resistor(pid);
        }



        sleep(1);
    }
    fan(0);
    fan(0);
}