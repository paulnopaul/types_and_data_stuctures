//
// Created by Павел Чеклин on 21.10.2019.
//

#ifndef LAB_03_MENU_H
#define LAB_03_MENU_H

#include "smatrix.h"
#include "linked_list.h"
#include "err.h"

int menu_mainloop();

// information ouput actions
void print_menu();

void print_info();

// main actions
int handle_action(int action);

int input_action(int *action);

#endif //LAB_03_MENU_H
