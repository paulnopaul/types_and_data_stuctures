#ifndef _ERR_H_
#define _ERR_H_

#define SUCCESS 0

#define MALLOC_ERROR 1
#define REALLOC_ERROR 2

#define INT_INPUT_ERROR 3

#define EMPTY_QUEUE 4

#define QUEUE_OVERFLOW 5

#define EMPTY_LIST 6

void err_out(int err_code);

#endif 