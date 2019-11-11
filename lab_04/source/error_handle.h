#ifndef _ERRHAND_H_
#define _ERRHAND_H_

// error codes

// no error
#define OK 0

// input errors
#define ACTION_INPUT_ERROR 3
#define INT_INPUT_ERROR 4

// memory errors

// stack errors
#define EMPTY_STACK 1

// menu errors
#define MENU_UNDEFINED_ACTION 2
#define STACK_UNDEFINED_MODE 4




void handle_error(const int err);

#endif