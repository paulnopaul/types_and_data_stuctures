#include "service_line.h"

#include <time.h>

int aqueue_line()
{
    clock_t a1, a2; 
    double a1_time = generate_time(0, 6), a2_time = generate_time(1, 8); // a1 from 0 to 6, a2 from 1 to 8
    aqueue q1, q2;
    // srand(time(NULL)); // TODO когда заработает
    int err = SUCCESS;
    int q1_request, q2_request;
    int a1_handling = 1, a2_handling = 0; // флаг работы обрабатывающих автоматов


    int q1_size = 99, q2_size = 0;
    int second_requests = 0;

    aqueue_line_start(&q1, &q2);

    puts("Source queue");
    aqueue_print(q1);
    puts("\n\nSTART\n\n");

    aqueue_pop(&q1, &q1_request);
    a1 = clock();
    while ((second_requests < SECOND_REQUEST_COUNT) && (a1_handling || a2_handling))
    {
        // проверка времени выполняется только в случае работы автомата
        // обработка действий первой очереди и автомата
        if (a1_handling)
        {
            if ((double)(clock() - a1) / CLOCKS_PER_SEC > a1_time)
            {
                // printf("----Handle %d; time = %lf\n", q1_request, (double)(clock() - a1) / CLOCKS_PER_SEC);
                // aqueue_print(q1);
                // aqueue_print(q2);

                // отправка запроса после его обработки автоматом
                switch (direction_choice(0.3, 0.7)) // выбор направления движения заявки
                {
                case 1:

                    a1_handling = 0; // прекращение работы автомата
                    
                    aqueue_push(&q2, q1_request);
                    ++q2_size;


                    if (!a2_handling && q2_size == 1) // если заявка добавилась в пустую очередь
                    {
                        aqueue_pop(&q2, &q2_request);
                        --q2_size;
                        a2_handling = 1;
                        a2_time = generate_time(1, 8);
                        a2 = clock();
                    }
                    break;
                case 2:

                    a1_handling = 0; // прекращение работы автомата

                    aqueue_push(&q1, q1_request);
                    ++q1_size;
                    break; 
                }
                
                // направление заявки из первой очереди в автомат
                if (q1_size > 0)
                {
                    a1_time = generate_time(0, 6);
                    aqueue_pop(&q1, &q1_request);
                    --q1_size;
                    a1_handling = 1;
                    a1_time = generate_time(0, 6);
                    a1 = clock();
                }
            }
        }


        // обработка действий второй очереди и автомата
        if (a2_handling)
        {
            if ((double)(clock() - a2) / CLOCKS_PER_SEC > a2_time)
            {
                // printf("++++Handle %d (second auto); time = %lf\n", q2_request, (double)(clock() - a2) / CLOCKS_PER_SEC);
                // aqueue_print(q1);
                // aqueue_print(q2);

                a2_handling = 0; // прекращение работы автомата

                ++second_requests; 
                // направление обработанной заявки в первую очередь
                aqueue_push(&q1, q2_request);

                if (second_requests % 100 == 0)
                {
                    printf("%d requests passed through second automat\n", second_requests);
                    puts("First queue");
                    aqueue_print(q1);
                    puts("Secon queue");
                    aqueue_print(q2);
                    puts("\n\n");
                }

                
                // направление заявки из второй очереди в автомат
                if (q2_size > 0)
                {
                    --q2_size;
                    aqueue_pop(&q2, &q2_request);
                    a2_time = generate_time(1, 8);
                    a2_handling = 1;
                    a2 = clock();
                }
            }
        }
    }
    return err;
}

int aqueue_line_start(aqueue_t q1, aqueue_t q2)
{
    aqueue_init(q1);
    aqueue_init(q2);
    for (int i = 0; i < REQUEST_COUNT; ++i)
        aqueue_push(q1, i + 100);
    return REQUEST_COUNT;
}

int aqueue_line_handle_line(aqueue_t q1, aqueue_t q2, int *second_requests)
{
    return SUCCESS;
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

double generate_time(int start_units, int end_units)
{
    return (double)((rand() % (end_units - start_units + 1)) + start_units) / TIME_UNIT;
}
