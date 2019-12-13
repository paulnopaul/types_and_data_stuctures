#ifndef _SERVICE_LINE_H_
#define _SERVICE_LINE_H_

#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#include "lqueue.h"
#include "aqueue.h"
#include "err.h"

#define REQUEST_COUNT 10
#define SECOND_REQUEST_COUNT 100
#define SECOND_REQUEST_STEP 10
#define TIME_UNIT 1000 // 1 / TIME_UNIT seconds


// first handle 0-6 time units
int aqueue_line();

int aqueue_line_start(aqueue_t q1, aqueue_t q2);

int lqueue_line();

int lqueue_line_start(lqueue_t q1, lqueue_t q2);

// int lqueue_line();

// выбор направления заявки 
// 1 - при переходе во 2 очередь
// 2 - при переходе в 1 очередь
int direction_choice(double right_p, double down_p);

double generate_time(int start_units, int end_units);

void expected_time_print();

#endif