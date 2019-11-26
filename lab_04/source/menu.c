#include "menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lstack.h"
#include "astack.h"
#include "error_handle.h"
#include "pointer_array.h"


void menu_print_menu(int mode)
{
	printf("Программа для работы со стеком \n\n"
		   "Информация о формате ввода находится в информации о программе\n\n"
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
		   "6 - Вывести убывающие серии последовательности целых чисел в обратном порядке\n"
		   "7 - Очистить стек\n"
		   "8 - Проверить время выполнения действий со стеком\n\n");
		   
	if (mode == LSTACK_MODE)
		printf("9 - Вывести список освобожденных адресов\n\n");
	printf("0 - Выход из программы\n"
		   "1 - Вывести информацию о программе\n\n"
		   "Введите действие: ");
}

void menu_print_info()
{
	printf("Программа для работы со стеком\n"
		   "Автор - Чеклин Павел, ИУ7-32Б\n\n"
		   "Данная программа производит операции со стеком целых чисел, такие как: добавление,\n"
		   "удаление элементов, вывод серий убывающих последовательностей и текущего состояния стека\n\n"
		   "Формат ввода (при добавлении элемента): целое число от −1 000 000 000  до 1 000 000 000\n");
	puts("Максимальный размер стека - 1000 элементов\n\n");
}

int menu_mainloop()
{
	// VARIALBLES
	int err = OK, action;

	lstack_t lstack = NULL;
	astack_t astack = NULL;

	size_t lstack_size = 0, astack_size = 0;

	int stack_mode = LSTACK_MODE;

	size_t p_arr_size = 0;
	void **p_arr = NULL;

	// MAINLOOP
	while (err != MENU_EXIT)
	{
		system("clear");
		menu_print_menu(stack_mode);
		// fflush(stdin);
		err = menu_read_action(&action);
		system("clear");
		if (err == OK)
			err = menu_handle_action(action, &lstack, &astack, 
									 &stack_mode, &p_arr, &p_arr_size,
									 &lstack_size, &astack_size);
		// TODO size check
		if (err && err != MENU_EXIT)
		{
			handle_error(err);
			menu_wait_for_enter();
		}
		fflush(stdin);
	}

	astack_clean(&astack);
	lstack_delete(&lstack);
	return err;
}

int menu_handle_action(int action, lstack_t *lstack, astack_t *astack, 
                       int *mode, void ***p_arr, size_t *p_arr_size,
					   size_t *lstack_size, size_t *astack_size)
{
	int err = OK;
	switch (action)
	{
	case 0:
		err = MENU_EXIT;
		break;
	case 1:
		err = menu_info();
		if (!err)
			menu_wait_for_enter();
		break;
	case 2: // Смена типа стека
		err = menu_stack_chmode(mode);
		break;
	case 3: // Добавление элемента
		if (*mode == ASTACK_MODE)
		{
			if (*lstack_size < 1000)
				err = menu_input_astack_element(astack);
			else 
				err = STACK_OVERFLOW;

			if (!err)
				++(*astack_size);
				
		}
		else if (*mode == LSTACK_MODE)
		{
			if (*lstack_size < 1000)
				err = menu_input_lstack_element(lstack);
			else
				err = STACK_OVERFLOW;
			
			if (!err)
				++(*lstack_size);
		}
		if (!err)
			menu_wait_for_enter();
		break;
	case 4:
		if (*mode == ASTACK_MODE)
		{
			err = menu_delete_astack_element(astack);
			if (!err)
				--(*astack_size);
		}
		else if (*mode == LSTACK_MODE)
		{
			err = menu_delete_lstack_element(lstack, p_arr, p_arr_size);
			if (!err)
				--(*lstack_size);
		}
		if (!err)
			menu_wait_for_enter();
		break;
	case 5:
		if (*mode == ASTACK_MODE)
			err = menu_output_astack_state(astack);
		else if (*mode == LSTACK_MODE)
			err = menu_output_lstack_state(lstack);
		if (!err)
			menu_wait_for_enter();
		break;
	case 6:
		if (*mode == ASTACK_MODE)
			err = menu_output_astack_decreasing(astack);
		else if (*mode == LSTACK_MODE)
			err = menu_output_lstack_decreasing(lstack);
		if (!err)
			menu_wait_for_enter();
		break;
	case 9: // ONLY LIST STACK
		if (*mode == LSTACK_MODE)
		{
			err = menu_output_lstack_freed((lstack_t *) *p_arr, *p_arr_size);
			menu_wait_for_enter();
		}
		break;
	case 7:
		if (*mode == LSTACK_MODE)
		{
			err = menu_delete_lstack(lstack, p_arr, p_arr_size);
			if (!err)
				menu_wait_for_enter();
		}
		else if (*mode == ASTACK_MODE)
		{
			err = menu_delete_astack(astack);
			if (!err)
				menu_wait_for_enter();
		}
		break;
	case 8: // BOTH STACKS
		err = menu_test_time();
		if (!err)
			menu_wait_for_enter();
	break;
	default:
		err = ACTION_INPUT_ERROR;
	}
	return err;
}

int menu_read_action(int *action)
{
	if (scanf("%d", action) == 1)
		return OK;
	else
	{
		getchar();
		return ACTION_INPUT_ERROR;
	}
}

void menu_wait_for_enter()
{
	printf("\nНажмите любую Enter\n");
	getchar();
	getchar();
}


// menu additional actoins

int menu_stack_chmode(int *mode)
{
	int temp = 0;
	printf("Текущий стек: ");
	if (*mode == ASTACK_MODE)
		printf("стек, хранящийся в массиве");
	else 
		printf("стек, хранящийся в списке\n\n");
	printf("Варианты:\n"
		   "1 - список\n"
		   "2 - массив\n\n"
		   "Выберите режим: ");
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
	menu_print_info();
	return OK;
}

// stack actions

// stack actions 

int menu_input_lstack_element(lstack_t *lstack)
{
	long buf;
	int err = OK;
	puts("Добавление элемента в стек\n");
	printf("Введите целое число: ");
	if (scanf("%ld", &buf) == 1)
	{
		if (buf >= -1000000000 && buf <= 1000000000)
			err =  lstack_push(lstack, buf);
		else 
			err = INT_INPUT_ERROR;
	}
	else
	{
		for (; getchar() != '\n';)
		err = INT_INPUT_ERROR;
	}

	if (!err)
		printf("\nБыл добавлен элемент %ld\n", buf);

	return err;
}


int menu_input_astack_element(astack_t *astack)
{
	long buf;
	int err = OK;
	puts("Добавление элемента в стек");
	printf("Введите целое число: ");
	if (scanf("%ld", &buf) == 1)
	{
		if (buf >= -1000000000 && buf <= 1000000000)
			err =  astack_push(astack, buf);
		else 
			err = INT_INPUT_ERROR;
	}
	else
	{
		for (; getchar() != '\n';)
		err = INT_INPUT_ERROR;
	}

	if (!err)
		printf("\nБыл добавлен элемент %ld\n", buf);
	return err;
}

int menu_delete_lstack_element(lstack_t *lstack, void ***p_arr, size_t *size)
{
	int err = OK;
	long elem;
	lstack_t freed;
	puts("Удаление элемента");
	if (!(err = lstack_pop(lstack, &elem, &freed)))
	{
		printf("\nБыл удален элемент %p со значением %ld\n", (void *) freed, elem);
		err = p_arr_push_back(p_arr, size, (void *) freed);
	}
	return err;
}

int menu_delete_astack_element(astack_t *astack)
{
	int err = OK;
	long elem;
	puts("Удаление элемента");
	if (!(err = astack_pop(astack, &elem)))
		printf("\nБыл удален элемент со значением %ld\n", elem);
	return err;
}

int menu_output_lstack_state(lstack_t *lstack)
{
	puts("Вывод стека\n");
	return lstack_print(lstack);
}

int menu_output_astack_state(astack_t *astack)
{
	puts("Вывод стека\n");
	return astack_print(astack);
}

int menu_output_lstack_decreasing(lstack_t *lstack)
{
	puts("Вывод убывающих подпоследовательностей стека в обратном порядке\n");
	return lstack_print_decreasing(lstack);
}

int menu_output_astack_decreasing(astack_t *astack)
{
	puts("Вывод убывающих подпоследовательностей стека\n");
	return astack_print_decreasing(astack);
}

int menu_output_lstack_freed(lstack_t *freed_arr, size_t size)
{
	puts("Вывод освобожденных адресов\n");
	if (size == 0)
		puts("Адреса не освобождались");
	else 
		p_arr_output((void **)freed_arr, size);
	puts("");
	return OK;
}

int menu_delete_lstack(lstack_t *lstack, void ***p_arr, size_t *p_arr_size)
{
	int err;
	long buf;
	lstack_t freed;

	puts("Удаление стека");
	err = lstack_pop(lstack, &buf, &freed);
	if (!err)
	{
		err = p_arr_push_back(p_arr, p_arr_size, freed);
		while (!err && !(err = lstack_pop(lstack, &buf, &freed)))
			err = p_arr_push_back(p_arr, p_arr_size, freed);
		if (err == EMPTY_STACK)
			err = OK;
	}

	if (!err)
		puts("Стек успешно удален");
	return err;
}

int menu_delete_astack(astack_t *astack)
{
	puts("Удаление стека");
	int err = OK;
	err = astack_clean(astack);
	if (!err)
		puts("Стек успешно удален");
	return err;
}

int menu_test_time()
{
	puts("Проверка времени добавления и удаления элементов из стеков разных реализаций");

	// error code
	int err = OK;

	// stacks
	lstack_t lstack = NULL;
	astack_t astack = NULL;

	// buf values;
	long buf;
	lstack_t lbuf;

	// variables for time count
	double time;
	clock_t start, end;

	// number of stack elements;
	long elem_count;
	printf("Введите количество элементов: ");
	if (!(scanf("%ld", &elem_count) == 1 && elem_count > 0 && elem_count < 100000))
		err = INT_INPUT_ERROR;
	
	if (!err)
	{
		start = clock();
		for (long i = 0; !err && i < elem_count; ++i)
			err = lstack_push(&lstack, i);
		end = clock();
		time = (double)(end - start) / CLOCKS_PER_SEC;
	}

	if (!err)
	{
		printf("Время добавления %ld элементов в стек (список): %lf сек\n", elem_count, time);
		start = clock();
		for (long i = 0; !err && i < elem_count; ++i)
			err = astack_push(&astack, i);
		end = clock();
		time = (double)(end - start) / CLOCKS_PER_SEC;
	}

	if (!err)
	{
		printf("Время добавления %ld элементов в стек (массив): %lf сек\n", elem_count, time);
		start = clock();
		for (long i = 0; !err && i < elem_count; ++i)
			err = lstack_pop(&lstack, &buf, &lbuf);
		end = clock();
		time = (double)(end - start) / CLOCKS_PER_SEC;
	}

	if (!err)
	{
		printf("Время удаления %ld элементов из стека (список): %lf сек\n", elem_count, time);
		start = clock();
		for (long i = 0; !err && i < elem_count; ++i)
			err = astack_pop(&astack, &buf);
		end = clock();
		time = (double) (end - start) / CLOCKS_PER_SEC;
	}

	if (!err)
		printf("Время удаления %ld элементов из стека (массив): %lf сек\n", elem_count, time);
	
	free(lstack);
	free(astack);

	return err;
}
