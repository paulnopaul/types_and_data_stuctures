#ifndef _MENU_H_
#define _MENU_H_

#define MENU_EXIT 10

void menu_print_menu();

int read_action(int *action);

int handle_action(int action);

void put_error(const char *errname);

void wait_to_clean();

int menu_mainloop();

#endif