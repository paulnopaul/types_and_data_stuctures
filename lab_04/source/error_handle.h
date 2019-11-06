#ifndef _ERRHAND_H_
#define _ERRHAND_H_

// error codes

// no error
#define OK 0

// input errors

// memory errors

// stack errors
#define EMPTY_STACK 1

// menu errors
#define MENU_UNDEFINED_ACTION 2




void handle_error(const int err);

#endif