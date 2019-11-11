#include "menu.h"

#include <stdio.h>
#include <stdlib.h>

#include "lstack.h"
#include "astack.h"
#include "error_handle.h"

void menu_print_menu(int mode)
{
	printf("\n\n\n**********************************************************************************\n\n"
		   "Программа для работы со стеком\n\n"
		   "Текущий стек: ");
	if (mode == ASTACK_MODE)
		puts("cтек, хранящийся в массиве\n");
	if (mode == LSTACK_MODE)
		puts("стек, хранящийся в списке\n");
	printf("Возможные действия:\n\n"
		   "2 - Выбрать тип стека\n" // ввод
		   "3 - Добавить элемент\n"
		   "4 - Удалить элемент\n\n"
		   "5 - Вывести текущее состояние\n" // вывод
		   "6 - Вывести убывающие серии последовательности целых чисел\n"
		   "7 - Вывести список освобожденных адресов\n\n"
		   "**********************************************************************************\n\n"
		   "0 - Выход из программы\n"
		   "1 - Вывести информацию о программе\n\n"
		   "**********************************************************************************\n\n"
		   "Введите действие: ");
}

void menu_print_info()
{
	printf("\n\n\n**********************************************************************************\n\n"
		   "Программа для работы со стеком\n"
		   "Автор - Чеклин Павел, ИУ7-32Б\n"
		   "Данная программа производит операции со стеком целых чисел, такие как: добавление,\n"
		   "удаление элементов, вывод серий убывающих последовательностей и текущего состояния стека\n"
		   "Формат ввода (при добавлении элемента): целое число от −1 000 000 000  до 1 000 000 000\n"
		   "Максимальный размер стека - 1000 элементов\n\n"
		   "****************************************************\n\n"
		   "Enter - выход в главное меню: ");
}

int menu_mainloop()
{
	int err = OK, action;
	lstack_t lstack = NULL;
	astack_t astack = NULL;
	int stack_mode = LSTACK_MODE;
	while (err != MENU_EXIT)
	{
		menu_print_menu(stack_mode);
		fflush(stdin);
		err = menu_read_action(&action);
		if (err == OK)
			err = menu_handle_action(action, &lstack, &astack, &stack_mode);
		handle_error(err);
	}
	return err;
}

int menu_handle_action(int action, lstack_t *lstack, astack_t *astack, int *mode)
{
	int err = OK;
	switch (action)
	{
	case 0:
		err = MENU_EXIT;
		break;
	case 1:
		err = menu_info();
		break;
	case 2: // Смена типа стека
		err = menu_stack_chmode(mode);
		break;
	case 3: // Добавление элемента
		if (*mode == ASTACK_MODE)
			err = menu_input_astack_element(astack);
		else if (*mode == LSTACK_MODE)
			err = menu_input_lstack_element(lstack);
		break;
	case 4:
		if (*mode == ASTACK_MODE)
			err = menu_delete_astack_element(astack);
		else if (*mode == LSTACK_MODE)
			err = menu_delete_lstack_element(lstack);
		break;
	case 5:
		if (*mode == ASTACK_MODE)
			err = menu_output_astack_state(astack);
		else if (*mode == LSTACK_MODE)
			err = menu_output_lstack_state(lstack);
		break;
	case 6:
		if (*mode == ASTACK_MODE)
			err = menu_output_astack_decreasing(astack);
		else if (*mode == LSTACK_MODE)
			err = menu_output_lstack_decreasing(lstack);
		break;
	case 7: 
		err = menu_output_lstack_freed(lstack);
		break;
	default:
		err = MENU_UNDEFINED_ACTION;
	}
	return err;
}

int menu_read_action(int *action)
{
	if (scanf("%d", action) == 1)
		return OK;
	else
		return ACTION_INPUT_ERROR;
}


// menu additional actoins

int menu_stack_chmode(int *mode)
{
	int temp = 0;
	printf("Current stack: ");
	if (*mode == ASTACK_MODE)
		printf("array stack");
	else 
		printf("linked list stack");
	printf("\n\n***********************************************"
		   "Stack variants:\n"
		   "1 - list stack\n"
		   "2 - array stack\n\n"
		   "Choose stack: ");
	if (scanf("%d", &temp) == 1 && temp == 1)
		*mode = LSTACK_MODE;
	else if (temp == 2)
		*mode = ASTACK_MODE;
	else
		return INT_INPUT_ERROR;
	return OK;
} 

int menu_info()
{
	int temp;
	menu_print_info();
	for(;getchar() != '\n';);
	return OK;
}r

// stack actions 
// TODO Correct gn
int menu_input_lstack_element(lstack_t *lstack)
{
	long temp;
	printf("Input element: ");
	if (scanf("%ld", &temp) == 1)
	{
		*lstack = lstack_push(*lstack, temp);
		if (!(*lstack))
			return STACK_ELEM_ALLOCATION_ERROR;
	}
	return OK; // TODO 
}

int menu_input_astack_element(astack_t *astack); // TODO

int menu_delete_lstack_element(lstack_t *lstack); // TODO

int menu_delete_astack_element(astack_t *astack); // TODO 

int menu_output_lstack_state(lstack_t *lstack); // TODO

int menu_output_astack_state(astack_t *astack); // TODO

int menu_output_lstack_decreasing(lstack_t *lstack); // TODO 

int menu_output_astack_decreasing(astack_t *astack); // TODO

int menu_output_lstack_freed(lstack_t *lstack); // TODO
