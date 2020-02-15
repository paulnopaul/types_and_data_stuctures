#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include <time.h>

#include "../include/lqueue.h"
#include "../include/aqueue.h"


#define SECOND_PASS 1000
#define SECOND_STEP 100
#define QUEUE_SIZE 100
#define TIME_UNIT 10 // ticks
#define SECOND_PROB 30 // percent

typedef struct system_t
{
    lqueue_t lq;
    aqueue_t aq; 

    char state; // 'a' or 'l'
    int fa_buf, sa_buf;

    int first_size;
    int second_size;

    int first_working; 
    int second_working;

    clock_t current_downtime;
    int second_passed;

    clock_t fstart, sstart;
    clock_t ftime, stime;
    
} system_t;

typedef struct tqueue_t
{

    system_t sys;

    aqueue_t *aq;
    lqueue_t *lq;

    double second_gate_probability;

    double aq_mean_push_time;
    double lq_mean_push_time;

    double aq_mean_pop_time;
    double lq_mean_pop_time;

    double predicted_time;

    long aq_size; 
    long lq_size;

    // after task
    double lq_downtime;
    double lq_main_time;

    double aq_main_time;
    double aq_downtime;

    int aq_first_passed;
    int lq_first_passed;

} tqueue_t;

void system_init(system_t *sys);

void task_init(tqueue_t *t);

int task_lqpush(tqueue_t *t, const int elem);

int task_aqpush(tqueue_t *t, const int elem);



void task_first_to_first(tqueue_t *t);

void task_first_to_second(tqueue_t *t);

void task_second_to_first(tqueue_t *t);


void task_first_to_a(tqueue_t *t);

void task_second_to_a(tqueue_t *t);

void task_print_info(tqueue_t *t);

void task_fill_first(tqueue_t *t);


int go_to_second_prob();

clock_t wait_time(int start, int end);


int task_task(tqueue_t *t);


#endif
