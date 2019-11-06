#include "error_handle.h"

void handle_error(const int err)
{
	switch (err)
	{
	case OK:
		break;
	case EMPTY_STACK:
		break;
	default:
		printf("Undefined error");
	}
}