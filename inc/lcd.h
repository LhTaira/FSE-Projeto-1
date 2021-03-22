#ifndef _LCD_
#define _LCD_

#include <wiringPi.h>
#include <wiringPiI2C.h>

#define LCD_CHR  1
#define LCD_CMD  0
#define LINE1  0x80
#define LINE2  0xC0
#define LCD_BACKLIGHT   0x08
#define ENABLE  0b00000100

extern int fd;

void typeln(const char *s);
void lcd_init(void);
void lcd_byte(int bits, int mode);
void ClrLcd(void);
void lcd_toggle_enable(int bits);
void typeInt(int i);
void lcdLoc(int line);
void typeChar(char val);
void typeFloat(float myFloat);

#endif 