#ifndef _MENU_H_
#define _MENU_H_

#include "lstack.h"
#include "astack.h"

// menu codes (NOT ERROR CODES)
#define MENU_EXIT 100
#define ASTACK_MODE 101
#define LSTACK_MODE 102


// menu print actions

void menu_print_menu(int mode);

void menu_print_info();

// menu main actions

int menu_mainloop();

int menu_read_action(int* action);

int menu_handle_action(int action, lstack_t *lstack, astack_t *astack, int *mode);

/*
Structure of menu action function
1) Information output
2) Action
3) Error code
*/

// menu additional actoins

int menu_stack_chmode(int *mode);

int menu_info();

// stack actions 

int menu_input_lstack_element(lstack_t *lstack); // TODO

int menu_input_astack_element(astack_t *astack); // TODO

int menu_delete_lstack_element(lstack_t *lstack); // TODO

int menu_delete_astack_element(astack_t *astack); // TODO 

int menu_output_lstack_state(lstack_t *lstack); // TODO

int menu_output_astack_state(astack_t *astack); // TODO

int menu_output_lstack_decreasing(lstack_t *lstack); // TODO 

int menu_output_astack_decreasing(astack_t *astack); // TODO

int menu_output_lstack_freed(lstack_t *lstack); // TODO

#endif
