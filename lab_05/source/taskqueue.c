#include "../include/taskqueue.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>


void task_init(tqueue_t *t)
{
    clock_t timer, time;
    int buf;

    lqueue_init(&t->sys.lq);
    aqueue_init(&t->sys.aq);

    t->aq = &t->sys.aq;
    t->lq = &t->sys.lq;

    t->second_gate_probability = 0.7;

    // TIME INIT 
    time = 0;
    for (int i = 0; i < AQUEUE_LEN; ++i)
    {
        timer = clock();
        aqueue_push(t->aq, i);
        timer = clock() - timer;
        time += timer;
    }
    t->aq_mean_push_time = ((double)time) / AQUEUE_LEN;

    time = 0;
    for (int i = 0; i < AQUEUE_LEN; ++i)
    {
        timer = clock();
        lqueue_push(t->lq, i);
        timer = clock() - timer;
        time += timer;
    }
    t->lq_mean_push_time = ((double)time) / AQUEUE_LEN;

    time = 0;
    for (int i = 0; i < AQUEUE_LEN; ++i)
    {
        timer = clock();
        aqueue_pop(t->aq, &buf);
        timer = clock() - timer;
        time += timer;
    }
    t->aq_mean_pop_time = ((double)time) / AQUEUE_LEN;

    time = 0;
    for (int i = 0; i < AQUEUE_LEN; ++i)
    {
        timer = clock();
        lqueue_pop(t->lq, &buf);
        timer = clock() - timer;
        time += timer;
    }
    t->lq_mean_pop_time = ((double)time) / AQUEUE_LEN;


    // MEMORY INIT
    t->aq_size = sizeof(aqueue_t);
    t->lq_size = sizeof(lqueue_t);

    // PREDICTION
    t->predicted_time = TIME_UNIT * SECOND_PASS * 10;

}

int task_lqpush(tqueue_t *t, const int elem)
{
    if (lqueue_push(t->lq, elem))
        return 1;
    
    t->lq_size += sizeof(struct list_node_t);
    return 0;
}

int task_aqpush(tqueue_t *t, const int elem)
{
    if (aqueue_push(t->aq, elem))
        return 1;
    return 0;
}

int go_to_second_prob()
{
    return (random() % 100 + 1) <= SECOND_PROB;
}

clock_t wait_time(int start, int end)
{
    return TIME_UNIT * (random() % (end - start) + start);
}

void system_init(system_t *sys)
{
    sys->second_passed = 0;

    sys->first_working = 0;
    sys->second_working = 0;
}

int task_task(tqueue_t *t)
{
    system_t *s = &t->sys;
    task_init(t);
    system_init(s);
    task_fill_first(t);

    t->lq_main_time = clock();

    task_first_to_a(t);
    while (t->sys.second_passed < SECOND_PASS)
    {
        if (t->sys.first_working && (clock() - t->sys.fstart) > t->sys.ftime)
        {
            if (go_to_second_prob())
                task_first_to_second(t);
            else 
                task_first_to_first(t);
        }
        if (t->sys.first_working && (clock() - t->sys.fstart) > t->sys.ftime)
        {
            if (t->sys.second_passed % SECOND_STEP)
                task_print_info(t);
            task_second_to_first(t);
        }
    }
    t->lq_main_time = clock() - t->lq_main_time;
    return 1;
}


void task_first_to_first(tqueue_t *t)
{
    return;
}

void task_first_to_second(tqueue_t *t)
{

    return;
}

void task_second_to_first(tqueue_t *t)
{
    return;
}


void task_first_to_a(tqueue_t *t)
{
    
    return;
}

void task_second_to_a(tqueue_t *t)
{
    return;
}

void task_print_info(tqueue_t *t)
{
    return;
}

void task_fill_first(tqueue_t *t)
{
    if (t->sys.state == 'a')
        for (int i = 0; i < QUEUE_SIZE; ++i)
            aqueue_push(t->aq, i + 1);
    else 
        for (int i = 0; i < QUEUE_SIZE; ++i)
            lqueue_push(t->lq, i + 1);
}

