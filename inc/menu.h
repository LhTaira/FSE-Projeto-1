#ifndef _MENU_
#define _MENU_

#include <ncurses.h>

#define WIDTH 30
#define HEIGHT 10

extern int startx ;
extern int starty;
extern int choice;
extern WINDOW *menu_win;
extern char *choices[];
extern int n_choices;

void refreshReferenceTemperature(char * fororonk);
void print_menu(WINDOW *menu_win, int highlight);
void screen2();
void screenForm();
int choose();
void doMenu();

#endif 