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

int screenForm()
{
  FIELD *field[3];
  FORM *my_form;
  int ch;

  keypad(stdscr, TRUE);
  field[0] = new_field(1, 10, 4, 18, 0, 0);
  field[1] = new_field(1, 10, 6, 18, 0, 0);
  field[2] = NULL;

  /* Set field options */
  set_field_back(field[0], A_UNDERLINE); /* Print a line for the option 	*/
  field_opts_off(field[0], O_AUTOSKIP);  /* Don't go to next field when this */
                                         /* Field is filled up 		*/
  set_field_back(field[1], A_UNDERLINE);
  field_opts_off(field[1], O_AUTOSKIP);

  /* Create the form and post it */
  my_form = new_form(field);
  post_form(my_form);
  refresh();

  mvprintw(4, 10, "Value 1:");
  mvprintw(6, 10, "Value 2:");
  refresh();

  /* Loop through to get user requests */
  while ((ch = getch()) != KEY_F(1))
  {
    switch (ch)
    {
    case KEY_DOWN:
      /* Go to next field */
      form_driver(my_form, REQ_NEXT_FIELD);
      /* Go to the end of the present buffer */
      /* Leaves nicely at the last character */
      form_driver(my_form, REQ_END_LINE);
      break;
    case KEY_UP:
      /* Go to previous field */
      form_driver(my_form, REQ_PREV_FIELD);
      form_driver(my_form, REQ_END_LINE);
      break;
    default:
      /* If this is a normal character, it gets */
      /* Printed				  */
      form_driver(my_form, ch);
      break;
    }
  }

  /* Un post form and free the memory */
  unpost_form(my_form);
  free_form(my_form);
  free_field(field[0]);
  free_field(field[1]);
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
    if (choice == 1)
    {
      screen2();
      clear();
    }
    if (choice == 3)
    {
      screenForm();
      clear();
    }

  } while (choice != 4);
  pthread_kill(controllerThread, 9);
  clrtoeol();
  refresh();
  clear();
  endwin();
}