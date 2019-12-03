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
#define TIME_UNIT 1000 // microseconds (1 milisecond)


// first handle 0-6 time units
int line(aqueue_t q1, aqueue_t q2);

void handle_request(int request, int time_min, int time_max);

// выбор направления заявки 
// 1 - при переходе во 2 очередь
// 2 - при переходе в 1 очередь
int direction_choice(double right_p, double down_p);

#endif