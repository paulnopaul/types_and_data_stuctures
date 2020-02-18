#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include <time.h>

#include "../include/lqueue.h"
#include "../include/aqueue.h"


#define SECOND_PASS 1000
#define SECOND_STEP 100
#define QUEUE_SIZE 100
#define TIME_UNIT 100 // ticks
#define SECOND_PROB 50 // percent

typedef struct system_t
{
    lqueue_t flq, slq;
    aqueue_t faq, saq;
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

    double mean_fsize, mean_ssize;
    
} system_t;

typedef struct tqueue_t
{

    system_t sys;

    aqueue_t aq;
    lqueue_t lq;

    int aq_size, lq_size;


    double mean_push_time;

    double mean_pop_time;

    double predicted_time;

    long size; 

    // after task
    double downtime;
    double a_main_time;
    double l_main_time;

    int first_passed;

    double f_meansize, s_meansize;
    int f_meansize_m, s_meansize_m;

} tqueue_t;

void system_init(system_t *sys);

void task_init(tqueue_t *t);



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

void task_print_result(tqueue_t *t);


#endif
