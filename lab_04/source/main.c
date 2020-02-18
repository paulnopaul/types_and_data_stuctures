/*
Чеклин Павел ИУ7-32Б 2019 
tscheklin@gmail.com

Лабораторная работа 4 по типам и структурным данным 
Создать программу работы со стеком, выполняющую
1) операцию добавления
2) операцию удаления элементов 
3) вывод текущего состояния стека. 

Реализовать стек: а) массивом; б) списком. 

Примечания
- Все стандартные операции со стеком должны быть оформлены подпрограммами.

- При реализации стека списком в вывод текущего состояния стека добавить просмотр адресов 
элементов стека и создать свой список или массив свободных областей 
(адресов освобождаемых элементов) с выводом его на экран.
*/


#include "menu.h"
#include "error_handle.h"
#include "astack.h"

#include "pointer_array.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int err;
	err = menu_mainloop();
	handle_error(err);
	return 0;
}

int m()
{
	astack_t a = NULL;
	puts("PUSH 1000");
	for (int i = 0; i < 1000; ++i)
	{	
		if (a)
			printf("%ld %d\n",a->size, i);
		else 
			printf("0 %d\n", i);
		astack_push(&a, i);
	}
	puts("CLEAN");
	astack_clean(&a);
	return 0;
}
