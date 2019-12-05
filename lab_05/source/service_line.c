#include "service_line.h"

#include <time.h>

int aqueue_line()
{
    clock_t a1, a2;
    aqueue q1, q2;
    srand(time(NULL));
    int err = SUCCESS;
    int second_requests = 0;

    aqueue_line_start(&q1, &q2);

    while (second_requests < SECOND_REQUEST_COUNT)
    {
        
    }
    return err;
}

int aqueue_line_start(aqueue_t q1, aqueue_t q2)
{
    aqueue_init(q1);
    aqueue_init(q2);
    for (int i = 0; i < REQUEST_COUNT; ++i)
        aqueue_push(q1, i);
    return REQUEST_COUNT;
}

int aqueue_line_round(aqueue_t q1, aqueue_t q2, int *second_requests)
{
    int request;
    int auto_1[] = {0, 6}, auto_2[] = {1, 8};

    aqueue_pop(q1, &request);

    handle_request(request, auto_1[0], auto_2[1]);

    switch (direction_choice(0.3, 0.7))
    {
        case 1:
            aqueue_push(q2, request);
            aqueue_pop(q2, &request);
            handle_request(request, auto_2[0], auto_2[1]);
            ++(*second_requests);

            if (*second_requests % 100 == 0)
            {
                printf("%d passed through\n", *second_requests);
                puts("Q1:");
                aqueue_print(*q1);
            }
        case 2:
            aqueue_push(q1, request);
            break;
        default:
            puts("WHAT");
    }
    return SUCCESS;
}

int lqueue_line()
{
    lqueue q1, q2;
    srand(time(NULL));
    int err = SUCCESS;
    int second_requests = 0;
    lqueue_init(&q1);
    lqueue_init(&q2);

    for(int i = 0; !err && i < REQUEST_COUNT; ++i)
        err = lqueue_push(&q1, i);
    if (!err)
    {
        puts("Q1 start");
        lqueue_print(q1);
        while (second_requests < SECOND_REQUEST_COUNT)
            err = lqueue_line_round(&q1, &q2, &second_requests);
        lqueue_delete(&q1);
        lqueue_delete(&q2);
    }
    return err;
}

int lqueue_line_round(lqueue_t q1, lqueue_t q2, int *second_requests)
{
    int err = SUCCESS;
    int request;
    int auto_1[] = {0, 6}, auto_2[] = {1, 8};

    lqueue_pop(q1, &request);

    handle_request(request, auto_1[0], auto_2[1]);

    switch (direction_choice(0.3, 0.7))
    {
        case 1:
            err = lqueue_push(q2, request);
            if (!err)
            {
                lqueue_pop(q2, &request);
                handle_request(request, auto_2[0], auto_2[1]);
                ++(*second_requests);

                if (*second_requests % 100 == 0)
                {
                    printf("%d passed through\n", *second_requests);
                    puts("Q1:");
                    lqueue_print(*q1);
                }
            }
        case 2:
            if (!err)
                lqueue_push(q1, request);
            break;
        default:
            puts("WHAT");
    }
    return err;
}


int direction_choice(double right_p, double down_p)
{
    double elem = (double)rand() / 100;
    elem = elem - (long)elem;
    if (elem < right_p)
        return 1;
    else
        return 2;
}
