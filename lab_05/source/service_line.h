#ifndef _SERVICE_LINE_H_
#define _SERVICE_LINE_H_

#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#include "lqueue.h"
#include "aqueue.h"
#include "err.h"

#define REQUEST_COUNT 100
#define SECOND_REQUEST_COUNT 1000
#define TIME_UNIT 1000 // 1 / TIME_UNIT seconds


// first handle 0-6 time units
int aqueue_line();

int aqueue_line_start(aqueue_t q1, aqueue_t q2);

int aqueue_line_handle_line(aqueue_t q1, aqueue_t q2, int *second_requests);

// int lqueue_line();

// выбор направления заявки 
// 1 - при переходе во 2 очередь
// 2 - при переходе в 1 очередь
int direction_choice(double right_p, double down_p);

double generate_time(int start_units, int end_units);

#endif