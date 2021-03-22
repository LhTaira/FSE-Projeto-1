#include <stdlib.h>
#include <stdio.h>

#include "../inc/global.h"

void createTemperatureLog() {
    // printf("shit1\n");
    FILE *log;
    log = fopen("log.csv", "w");
    // printf("shit2\n");
    fseek(log, 0, SEEK_END);
    // printf("shit3\n");
    int size = ftell(log);
    // printf("shit4\n");
    if (size == 0) {
        fprintf(log,"d-m-yyyy h:m:s,TI,TE,TR,pidResistor,pidFan\n");
    }
    // printf("shit5\n");
    fclose(log);
    // printf("shit6\n");
}

void logTemperatures() {
    // printf("shit7\n");
    struct tm *dateTime;  
    time_t seconds;
    time(&seconds);
    // if(seconds % 2 == 1)
    // {
    //     return;
    // }
    FILE *log;
    dateTime = localtime(&seconds);
    log = fopen("log.csv", "a");

    fprintf(
        log,
        "%d-%d-%d %d:%d:%d,%.2f,%.2f,%.2f,%d,%d\n",
        dateTime->tm_mday,
        dateTime->tm_mon+1,
        dateTime->tm_year+1900,
        dateTime->tm_hour,
        dateTime->tm_min,
        dateTime->tm_sec,
        internalTemperature,
        externalTemperature,
        referenceTemperature,
        pidResistor,
        pidFan
    );
    // printf("shit8\n");
    fclose(log);
}
