//
// Created by Павел Чеклин on 07/10/2019.
//

#ifndef _DB_MENU_H_
#define _DB_MENU_H_

#include "student_database.h"

#define MENU_EXIT 0
#define MAX_ACTION 12

void menu_output();

int menu_act(student_database *db, int action);

int menu_input_action();

int menu_start(student_database *db);

void menu_main();

#endif
