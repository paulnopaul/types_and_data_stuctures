#ifndef _MENU_H_
#define _MENU_H_

#include "lstack.h"
#include "astack.h"

#define MENU_EXIT 100
#define ASTACK_MODE 101
#define LSTACK_MODE 102

int menu_mainloop();

// print actons
void menu_print_menu(int mode);

void menu_print_info();

// stack actions output



// main_actions
int menu_read_action(int* action);

int menu_hanlde_action(int action, lstack_t *lstack, astack_t *astack, int *mode);

// 




#endif
