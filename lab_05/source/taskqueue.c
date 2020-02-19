#include "../include/taskqueue.h"

#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void task_init(tqueue_t *t)
{
    clock_t timer, time;
    int buf;

    lqueue_init(&t->lq);
    aqueue_init(&t->aq);

    t->first_passed = 0;

    // TIME INIT
    if (t->sys.state == 'a')
    {
        time = 0;
        for (int i = 0; i < AQUEUE_LEN; ++i)
        {
            timer = clock();
            aqueue_push(&t->aq, i);
            timer = clock() - timer;
            time += timer;
        }
        t->mean_push_time = ((double)time) / AQUEUE_LEN;

        time = 0;
        for (int i = 0; i < AQUEUE_LEN; ++i)
        {
            timer = clock();
            aqueue_pop(&t->aq, &buf);
            timer = clock() - timer;
            time += timer;
        }
        t->mean_pop_time = ((double)time) / AQUEUE_LEN;
    }

    if (t->sys.state == 'a')
    {
        time = 0;
        for (int i = 0; i < AQUEUE_LEN; ++i)
        {
            timer = clock();
            lqueue_push(&t->lq, i);
            timer = clock() - timer;
            time += timer;
        }
        t->mean_push_time = ((double)time) / AQUEUE_LEN;

        time = 0;
        for (int i = 0; i < AQUEUE_LEN; ++i)
        {
            timer = clock();
            lqueue_pop(&t->lq, &buf);
            timer = clock() - timer;
            time += timer;
        }
        t->mean_pop_time = ((double)time) / AQUEUE_LEN;
    }
    // MEMORY INIT

    t->lq_size = (int)(sizeof(lqueue_t) + sizeof(struct list_node_t) * QUEUE_SIZE);
    t->aq_size = (int)(sizeof(aqueue_t));
    // PREDICTION
    t->predicted_time = TIME_UNIT * SECOND_PASS * 10;

    t->first_passed = 0;
}

int go_to_second_prob()
{
    return (random() % 100 + 1) <= SECOND_PROB;
}

clock_t wait_time(int start, int end)
{
    return TIME_UNIT * (random() % (end - start + 1) + start);
}

void system_init(system_t *sys)
{
    sys->second_passed = 0;

    sys->first_working = 0;
    sys->second_working = 0;

    sys->second_passed = 0;

    sys->fa_buf = -1;
    sys->sa_buf = -1;

    if (sys->state == 'a')
    {
        aqueue_init(&sys->faq);
        aqueue_init(&sys->saq);
    }
    else
    {
        lqueue_init(&sys->flq);
        lqueue_init(&sys->slq);
    }
}

int task_task(tqueue_t *t)
{
    srand(time(NULL));
    system_t *s = &t->sys;
    task_init(t);
    system_init(s);
    task_fill_first(t);
    // aqueue_print(&s->faq);
    if (t->sys.state == 'a')
        t->a_main_time = t->sys.current_downtime = clock();
    else
        t->l_main_time = t->sys.current_downtime = clock();

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
        if (t->sys.second_working && (clock() - t->sys.sstart) > t->sys.stime)
        {
            task_second_to_first(t);
            if (t->sys.second_passed % SECOND_STEP == 0 && t->sys.state == 'a')
                task_print_info(t);
        }
    }
    if (t->sys.state == 'a')
        t->a_main_time = clock() - t->a_main_time;
    else
        t->l_main_time = clock() - t->a_main_time;

    // printf("LETTER %c\n", t->sys.state);
    if (t->sys.state == 'l')
    {
        task_print_result(t);
    }
    return 1;
}

void task_first_to_first(tqueue_t *t)
{
    if (t->sys.state == 'a')
        aqueue_push(&t->sys.faq, t->sys.fa_buf);
    else
        lqueue_push(&t->sys.flq, t->sys.fa_buf);

    // printf("Из первого автомата в первую очередь направляется %d\n", t->sys.fa_buf);
    //aqueue_print(&t->sys.faq);

    ++(t->sys.first_size);
    t->f_meansize = (double)((t->f_meansize * t->f_meansize_m) + t->sys.first_size) / (++t->f_meansize_m);

    t->sys.first_working = 0;

    t->sys.fa_buf = -1; // debug

    if (t->sys.first_size)
        task_first_to_a(t);
    return;
}

void task_first_to_second(tqueue_t *t)
{
    if (t->sys.state == 'a')
        aqueue_push(&t->sys.saq, t->sys.fa_buf);
    else
        lqueue_push(&t->sys.slq, t->sys.fa_buf);

    // printf("Из первого автомата во вторую очередь направляется %d\n", t->sys.fa_buf);
    // aqueue_print(&t->sys.saq);

    ++(t->sys.second_size);
    t->s_meansize = (double)((t->s_meansize * t->s_meansize_m) + t->sys.second_size) / (++t->s_meansize_m);

    t->sys.first_working = 0;

    // t->sys.fa_buf = -1; // debug

    if (t->sys.first_size)
        task_first_to_a(t);
    if (t->sys.second_size == 1 && !t->sys.second_working)
        task_second_to_a(t);
}

void task_second_to_first(tqueue_t *t)
{
    if (t->sys.state == 'a')
        aqueue_push(&t->sys.faq, t->sys.sa_buf);
    else
        lqueue_push(&t->sys.flq, t->sys.sa_buf);

    // printf("Из второго автомата в первую очередь направляется %d\n", t->sys.sa_buf);
    // aqueue_print(&t->sys.faq);

    ++(t->sys.first_size);
    t->f_meansize = (double)((t->f_meansize * t->f_meansize_m) + t->sys.first_size) / (++t->f_meansize_m);

    t->sys.second_working = 0;

    t->sys.sa_buf = -1; // debug;

    if (!t->sys.second_size)
        t->sys.current_downtime = clock();

    if (t->sys.first_size == 1)
        task_first_to_a(t);
    if (t->sys.second_size)
        task_second_to_a(t);

    ++(t->sys.second_passed);
    return;
}

void task_first_to_a(tqueue_t *t)
{
    if (t->sys.state == 'a')
        aqueue_pop(&t->sys.faq, &t->sys.fa_buf);
    else
        lqueue_pop(&t->sys.flq, &t->sys.fa_buf);

    // printf("%d отправляется из первой очереди в автомат\n", t->sys.fa_buf);
    // aqueue_print(&t->sys.faq);

    --(t->sys.first_size);
    t->f_meansize = (double)((t->f_meansize * t->f_meansize_m) + t->sys.first_size) / (++t->f_meansize_m);

    t->sys.ftime = wait_time(0, 6);
    t->sys.first_working = 1;

    ++(t->first_passed);

    t->sys.fstart = clock();
}

void task_second_to_a(tqueue_t *t)
{
    if (t->sys.state == 'a')
        aqueue_pop(&t->sys.saq, &t->sys.sa_buf);
    else
        lqueue_pop(&t->sys.slq, &t->sys.sa_buf);
    if (t->sys.current_downtime)
    {
        t->downtime += (clock() - t->sys.current_downtime);
        t->sys.current_downtime = 0;
    }

    // printf("%d отправляется из второй очереди в автомат\n", t->sys.sa_buf);
    // aqueue_print(&t->sys.saq);

    --(t->sys.second_size);
    t->s_meansize = (double)((t->s_meansize * t->s_meansize_m) + t->sys.second_size) / (++t->s_meansize_m);

    t->sys.second_working = 1;
    t->sys.stime = wait_time(1, 8);

    t->sys.sstart = clock();
    return;
}

void task_print_info(tqueue_t *t)
{
    printf("Через второй автомат прошло %d заявок\n", t->sys.second_passed);
    printf("Текущий размер первой очереди: %d\nТекущий размер второй очереди: %d\n",
           t->sys.first_size, t->sys.second_size);

    printf("Средний размер первой очереди: %.3lf\n", t->f_meansize);
    printf("Средний размер второй очереди: %.3lf\n", t->s_meansize);

    /*
    printf("Первая очередь: ");
    aqueue_print(&t->sys.faq);
    printf("Вторая очередь: ");
    aqueue_print(&t->sys.saq);
    printf("Элементы в автоматах: %d %d\n", t->sys.fa_buf, t->sys.sa_buf);
    */
    printf("\n");
}

void task_fill_first(tqueue_t *t)
{
    if (t->sys.state == 'a')
        for (int i = 0; i < QUEUE_SIZE; ++i)
            aqueue_push(&t->sys.faq, i + 1);
    else
        for (int i = 0; i < QUEUE_SIZE; ++i)
            lqueue_push(&t->sys.flq, i + 1);

    // aqueue_print(&t->sys.faq);
    // aqueue_print(&t->sys.saq);

    t->sys.first_size = QUEUE_SIZE;
    t->f_meansize = QUEUE_SIZE;
    t->s_meansize = 0;
    t->f_meansize_m = 1;
    t->s_meansize_m = 0;
    t->sys.second_size = 0;
}

void task_print_result(tqueue_t *t)
{
    printf("Ожидаемое время моделирования: %.1lf .\n", t->predicted_time / TIME_UNIT);
    printf("Время моделирования: %.1lf .\n", t->a_main_time / TIME_UNIT);
    printf("Погрешность: %.2lf%%\n", 100 * fabs(t->predicted_time - t->a_main_time) / t->predicted_time);
    printf("Средний размер первой очереди: %.0lf\n", t->f_meansize);
    printf("Средний размер второй очереди: %.0lf\n", t->s_meansize);
    printf("Через первый автомат прошло %d заявок\n", t->first_passed);
    printf("Время простоя второго: %.0lf\n", t->downtime / TIME_UNIT);

    printf("Очередь, реализованная массивом занимает %d байт памяти\n", t->aq_size);
    printf("Очередь, реализованная списком занимает %d байт памяти\n", t->lq_size);
}

int task_real()
{
    tqueue_t *t = (tqueue_t *)malloc(sizeof(tqueue_t));
    t->sys.state = 'a';

    srand(time(NULL));

    system_t *s = &t->sys;

    task_init(t);
    system_init(s);
    task_fill_first(t);
    // aqueue_print(&s->faq);

    t->a_main_time = t->sys.current_downtime = clock();

    aqueue_pop(&t->sys.faq, &t->sys.fa_buf);
    --(t->sys.first_size);
    t->sys.ftime = wait_time(0, 6);
    t->sys.first_working = 1;
    t->sys.fstart = clock();
    while (t->sys.second_passed < SECOND_PASS)
    {
        if (t->sys.first_working && (clock() - t->sys.fstart) > t->sys.ftime)
        {

            if (go_to_second_prob())
            {
                aqueue_push(&t->sys.saq, t->sys.fa_buf);
                ++(t->sys.second_size);
                t->sys.first_working = 0;

                if (t->sys.first_size)
                {
                    aqueue_pop(&t->sys.faq, &t->sys.fa_buf);
                    --(t->sys.first_size);
                    t->sys.ftime = wait_time(0, 6);
                    t->sys.first_working = 1;
                    t->sys.fstart = clock();
                    // task_first_to_a(t);
                }
                if (t->sys.second_size == 1 && !t->sys.second_working)
                {
                    aqueue_pop(&t->sys.saq, &t->sys.sa_buf);
                    --(t->sys.second_size);
                    t->sys.second_working = 1;
                    t->sys.stime = wait_time(1, 8);
                    t->sys.sstart = clock();
                    // task_second_to_a(t);
                }
                // task_first_to_second(t);
            }
            else
            {
                aqueue_push(&t->sys.faq, t->sys.fa_buf);
                ++(t->sys.first_size);
                t->sys.first_working = 0;
                if (t->sys.first_size)
                {
                    aqueue_pop(&t->sys.faq, &t->sys.fa_buf);
                    --(t->sys.first_size);
                    t->sys.ftime = wait_time(0, 6);
                    t->sys.first_working = 1;
                    t->sys.fstart = clock();
                    // task_first_to_a(t);
                }
                // task_first_to_first(t);
            }
        }
        if (t->sys.second_working && (clock() - t->sys.sstart) > t->sys.stime)
        {
            aqueue_push(&t->sys.faq, t->sys.sa_buf);
            ++(t->sys.first_size);
            t->sys.second_working = 0;

            if (t->sys.first_size == 1)
            {
                aqueue_pop(&t->sys.faq, &t->sys.fa_buf);
                --(t->sys.first_size);
                t->sys.ftime = wait_time(0, 6);
                t->sys.first_working = 1;
                t->sys.fstart = clock();
                task_first_to_a(t);
            }

            if (t->sys.second_size)
            {
                aqueue_pop(&t->sys.saq, &t->sys.sa_buf);
                --(t->sys.second_size);
                t->sys.second_working = 1;
                t->sys.stime = wait_time(1, 8);
                t->sys.sstart = clock();
                //task_second_to_a(t);
            }
            ++(t->sys.second_passed);
            // task_second_to_first(t);
        }
    }
    t->a_main_time = clock() - t->a_main_time;

    // ---------------------------------------------------------------

    t->sys.state = 'l';

    srand(time(NULL));

    s = &t->sys;

    task_init(t);
    system_init(s);
    task_fill_first(t);
    // aqueue_print(&s->faq);

    t->l_main_time = t->sys.current_downtime = clock();

    task_first_to_a(t);
    while (t->sys.second_passed < SECOND_PASS)
    {
        if (t->sys.first_working && (clock() - t->sys.fstart) > t->sys.ftime)
        {

            if (go_to_second_prob())
            {
                lqueue_push(&t->sys.slq, t->sys.fa_buf);
                ++(t->sys.second_size);
                t->sys.first_working = 0;

                if (t->sys.first_size)
                {
                    lqueue_pop(&t->sys.flq, &t->sys.fa_buf);
                    --(t->sys.first_size);
                    t->sys.ftime = wait_time(0, 6);
                    t->sys.first_working = 1;
                    t->sys.fstart = clock();
                    // task_first_to_a(t);
                }
                if (t->sys.second_size == 1 && !t->sys.second_working)
                {
                    lqueue_pop(&t->sys.slq, &t->sys.sa_buf);
                    --(t->sys.second_size);
                    t->sys.second_working = 1;
                    t->sys.stime = wait_time(1, 8);
                    t->sys.sstart = clock();
                    // task_second_to_a(t);
                }
                // task_first_to_second(t);
            }
            else
            {
                lqueue_push(&t->sys.flq, t->sys.fa_buf);
                ++(t->sys.first_size);
                t->sys.first_working = 0;
                if (t->sys.first_size)
                {
                    lqueue_pop(&t->sys.flq, &t->sys.fa_buf);
                    --(t->sys.first_size);
                    t->sys.ftime = wait_time(0, 6);
                    t->sys.first_working = 1;
                    t->sys.fstart = clock();
                    // task_first_to_a(t);
                }
                // task_first_to_first(t);
            }
        }
        if (t->sys.second_working && (clock() - t->sys.sstart) > t->sys.stime)
        {
            lqueue_push(&t->sys.flq, t->sys.sa_buf);
            ++(t->sys.first_size);
            t->sys.second_working = 0;

            if (t->sys.first_size == 1)
            {
                lqueue_pop(&t->sys.flq, &t->sys.fa_buf);
                --(t->sys.first_size);
                t->sys.ftime = wait_time(0, 6);
                t->sys.first_working = 1;
                t->sys.fstart = clock();
                // task_first_to_a(t);
            }

            if (t->sys.second_size)
            {
                lqueue_pop(&t->sys.slq, &t->sys.sa_buf);
                --(t->sys.second_size);
                t->sys.second_working = 1;
                t->sys.stime = wait_time(1, 8);
                t->sys.sstart = clock();
                //task_second_to_a(t);
            }
            ++(t->sys.second_passed);
            // task_second_to_first(t);
        }
    }
    t->l_main_time = clock() - t->l_main_time;
    printf("Единица времени равна %lf секунд\n\n", (double)TIME_UNIT / CLOCKS_PER_SEC);
    printf("Время выполнения с очередью массивом %lf сек\n", (double)t->a_main_time / CLOCKS_PER_SEC);
    printf("Время выполнения с очередью cписком  %lf сек\n", (double)t->l_main_time / CLOCKS_PER_SEC);
    free(t);
    return 1;
}
