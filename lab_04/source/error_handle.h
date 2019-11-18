#ifndef _ERRHAND_H_
#define _ERRHAND_H_

// error codes

// no error
#define OK 0

// input errors
#define ACTION_INPUT_ERROR 1
#define INT_INPUT_ERROR 2

// memory errors
#define MALLOC_ERROR 3
#define REALLOC_ERROR 7

// stack errors
#define EMPTY_STACK 4

// menu errors
#define MENU_UNDEFINED_ACTION 5
#define STACK_UNDEFINED_MODE 6




void handle_error(const int err);

#endif