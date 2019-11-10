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
		   "Любой символ + Enter - выход в главное меню: ");
}

int menu_mainloop()
{
	int err = OK, action;
	lstack_t lstack = NULL;
	astack_t astack = NULL;
	int stack_mode = LSTACK_MODE;
	while (err == OK)
	{
		menu_print_menu(stack_mode);
		err = menu_read_action(&action);
		if (err == OK)
			err = menu_handle_action(action, &lstack, &astack, &stack_mode);
	}
	return err;
}

int menu_handle_action(int action, lstack_t *lstack, astack_t *astack, int *mode)
{
	int err = OK;
	int type;
	switch (action)
	{
	case 0:
		err = MENU_EXIT;
		break;
	case 1: 
		// Вывод меню
		menu_print_info();
		fflush(stdin);
		for (; getchar() != '\n';);
		break;
	case 2:
		// Смена типа стека
		if (scanf("%d", &type) == 1)
		{
			if (type == 1)
				*mode = ASTACK_MODE;
			else if (type == 2)
				*mode = LSTACK_MODE;
		}
		break;
	case 3:
		break;
	case 4:
		// TODO
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	default:
		err = MENU_UNDEFINED_ACTION;
	}
	return err;
}

int menu_read_action(int* action)
{
	if (scanf("%d", action) == 1)
		return OK;
	else 
		return ACTION_INPUT_ERROR;
}