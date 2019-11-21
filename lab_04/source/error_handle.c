#include "error_handle.h"

#include <stdio.h>

void handle_error(const int err)
{
	switch (err)
	{
	case OK:
		break;
	case EMPTY_STACK:
		puts("Пустой стек");
		break;
	case STACK_UNDEFINED_MODE:
		puts("Неизвестный режим");
		break;
	case MALLOC_ERROR:
		puts("Ошибка выделения памяти");
		break;
	case REALLOC_ERROR:
		puts("Ошибка переопределения памяти");
		break;
	case MENU_UNDEFINED_ACTION:
		puts("Неизвестное действие в меню");
		break;
	case INT_INPUT_ERROR: 
		puts("Ошибка ввода числа");
		break;
	case STACK_OVERFLOW:
		puts("Переполнение стека");
		break;
	case ACTION_INPUT_ERROR:
		puts("Ошибка ввода действия");
	default:
		break;
	}
}