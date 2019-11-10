#include "error_handle.h"

#include <stdio.h>

void handle_error(const int err)
{
	switch (err)
	{
	case OK:
		break;
	case EMPTY_STACK:
		break;
	case STACK_UNDEFINED_MODE:
		puts("Undefined mode");

	default:
		break;
	}
}