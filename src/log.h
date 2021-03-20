#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void createTemperatureLog() {
    FILE *log;
    log = fopen("./log.csv", "rw");

    fseek(log, 0, SEEK_END);
    int size = ftell(log);

    if (size == 0) {
        fprintf(log,"d-m-yyyy h:m,TI,TE,TR,pidResistor,pidFan\n");
    }
    fclose(log);
}

void logTemperature() {
    struct tm *dateTime;  
    time_t seconds;
    time(&seconds);
    FILE *log;
    dateTime = localtime(&seconds);
    log = fopen("./log.csv", "rw");

    fprintf(
        log,
        "%d-%d-%d %d:%d,%.2f,%.2f,%.2f\n",
        dateTime->tm_mday,
        dateTime->tm_mon,
        dateTime->tm_year,
        dateTime->tm_hour,
        dateTime->tm_min,
        internalTemperature,
        externalTemperature,
        referenceTemperature,
        pidResistor,
        pidFan
    );
    fclose(log);
}