#include <ncurses.h>
#include <unistd.h>
#include <signal.h>

#define WIDTH 30
#define HEIGHT 10

int startx = 0;
int starty = 0;
int choice = 0;
WINDOW *menu_win;

char *choices[] = {
    "Usar TR automatica",
    "Usar TR por potenciometro",
    "Usar TR por terminal",
    "Sair",
};
int n_choices = sizeof(choices) / sizeof(char *);

void print_menu(WINDOW *menu_win, int highlight)
{
  int x, y, i;

  x = 2;
  y = 2;
  box(menu_win, 0, 0);
  for (i = 0; i < n_choices; ++i)
  {
    if (highlight == i + 1) /* High light the present choice */
    {
      wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, y, x, "%s", choices[i]);
      wattroff(menu_win, A_REVERSE);
    }
    else
      mvwprintw(menu_win, y, x, "%s", choices[i]);
    ++y;
  }
  wrefresh(menu_win);
}

int screen2()
{
  int c = 0;
  pthread_kill(controllerThread, choice);
  clear();
  mvprintw(0, 0, choices[choice - 1]);
  mvprintw(2, 0, "Aperte ESC para voltar");
  halfdelay(10);
  while (c != 27)
  {
    c = wgetch(menu_win);
    mvprintw(4, 0, "TI: %f", internalTemperature);
    mvprintw(5, 0, "TR: %f", referenceTemperature);
    mvprintw(6, 0, "TE: %f", externalTemperature);
    refresh();
  }
  cbreak();
  pthread_kill(controllerThread, 4);
}

int choose()
{
  choice = 0;
  int highlight = 1;
  int c;
  startx = (80 - WIDTH) / 2;
  starty = (24 - HEIGHT) / 2;

  menu_win = newwin(HEIGHT, WIDTH, starty, startx);
  keypad(menu_win, TRUE);
  mvprintw(0, 0, "Use setas para navegar e Enter para selecionar uma opcao.");
  refresh();
  print_menu(menu_win, highlight);
  while (1)
  {
    c = wgetch(menu_win);
    switch (c)
    {
    case KEY_UP:
      if (highlight == 1)
        highlight = n_choices;
      else
        --highlight;
      break;
    case KEY_DOWN:
      if (highlight == n_choices)
        highlight = 1;
      else
        ++highlight;
      break;
    case 10:
      choice = highlight;
      break;
    default:
      mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
      refresh();
      break;
    }
    print_menu(menu_win, highlight);
    if (choice != 0) /* User did a choice come out of the infinite loop */
      break;
  }
  return choice;
}

void doMenu()
{

  initscr();
  clear();
  noecho();
  cbreak(); /* Line buffering disabled. pass on everything */

  do
  {
    choose();
    if (choice != 4)
    {
      screen2();
      clear();
    }
  } while (choice != 4);
  pthread_kill(controllerThread, 9);
  clrtoeol();
  refresh();
  clear();
  endwin();
}