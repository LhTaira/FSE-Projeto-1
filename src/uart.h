#include <unistd.h>         //Used for UART
#include <fcntl.h>          //Used for UART
#include <termios.h>        //Used for UART
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include "crc.h"

int uart0_filestream = -1;\

int configureUart() {
    uart0_filestream = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);      //Open in non blocking read/write mode
    if (uart0_filestream == -1)
    {
        return 1;
    }
    
    struct termios options;
    tcgetattr(uart0_filestream, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;     //<Set baud rate
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);
    
    return 0;
}

float readUart(unsigned char mode) 
{   
    float fonk;
    unsigned char tx_buffer[20];
    unsigned char *p_tx_buffer;
    short crc;

    if(!configureUart() == 0) {
        return -1;
    }

    
    p_tx_buffer = &tx_buffer[0];
    *p_tx_buffer++ = 0x01;
    *p_tx_buffer++ = 0x23;
    *p_tx_buffer++ = mode;
    *p_tx_buffer++ = 0x09;
    *p_tx_buffer++ = 0x02;
    *p_tx_buffer++ = 0x00;
    *p_tx_buffer++ = 0x08;

    crc = calcula_CRC(&tx_buffer[0], 7);

    
    if (uart0_filestream != -1)
    {

        write(uart0_filestream, &tx_buffer[0], (p_tx_buffer - &tx_buffer[0]));
        write(uart0_filestream, &crc, sizeof(short));
        
    }

    sleep(1);

    if (uart0_filestream != -1)
    {
        unsigned char rx_buffer[256];
        int rx_length = read(uart0_filestream, (void*)rx_buffer, 255);  
        
        memcpy(&fonk,&rx_buffer[3],4);
        // printf("fonk %f\n", fonk);
        
    }

    close(uart0_filestream);

    return fonk;
}

