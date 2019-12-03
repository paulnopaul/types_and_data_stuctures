#include "service_line.h"

#include <time.h>
#include <unistd.h>

int line(aqueue_t q1, aqueue_t q2)
{
    int err = SUCCESS;
    int auto_1[] = {0, 6}, auto_2[] = {1, 8};
    int second_requests = 0, request;
    aqueue_init(q1);
    aqueue_init(q2);

    for(int i = 0; i < REQUEST_COUNT; ++i)
        aqueue_push(q1, i);
    puts("Start: First queue");
    aqueue_print(*q1);
    puts("Second");
    aqueue_print(*q2);
    while (second_requests < SECOND_REQUEST_COUNT)
    {
        aqueue_pop(q1, &request);

        handle_request(request, auto_1[0], auto_2[1]);

        switch (direction_choice(0.3, 0.7))
        {
            case 1:
                aqueue_push(q2, request);
                aqueue_pop(q2, &request);
                handle_request(request, auto_2[0], auto_2[1]);
                ++second_requests;

                if (second_requests % 100 == 0)
                {
                    printf("%d passed through\n", second_requests);
                    puts("First queue");
                    aqueue_print(*q1);
                    puts("Second queue");
                    aqueue_print(*q2);
                }
            case 2:
                aqueue_push(q1, request);
                break;
            default:
                puts("WHAT");
        }
    }
    return err;
}

void handle_request(int request, int time_min, int time_max)
{
    usleep((rand() % (time_max - time_min + 1) + time_min) * TIME_UNIT);
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
