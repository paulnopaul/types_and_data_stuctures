#include "../include/menu.h"
#include "../include/taskqueue.h"
#include "../include/lqueue.h"

#include <stdio.h>
#include <stdlib.h>

int app()
{
    int ch, ch1, buf;
    system("clear");
    puts("1 - выполнить задание\n2 - тестировать операции очереди");
    puts("3 - сравнить время работы очередей (добавление и удаление 1000 элементов)");
    puts("4 - вывести результаты задания для разных очередей");

    printf("Выберите действие: ");
    if (scanf("%d", &ch) == 1 && (ch > 0))
    {
        if (ch == 1)
        {
            tqueue_t t;
            t.sys.state = 'a';
            task_init(&t);
            task_task(&t);
            t.sys.state = 'l';
            task_task(&t);
        }
        if (ch == 2)
        {
            lqueue_t q;
            lqueue_init(&q);
            system("clear");
            puts("1 - добавить элемент в очередь");
            puts("2 - удалить элемент из очереди");
            puts("0 - выйти из программы");
            printf("Выберите очередь: ");
            while (scanf("%d", &ch1) == 1 && (ch1 == 1 || ch1 == 2 || ch1 == 1))
            {
                if (ch1 == 1)
                {
                    printf("Введите элемент: ");
                    scanf("%d", &buf);
                    lqueue_push(&q, buf);
                }
                if (ch1 == 2)
                {
                    lqueue_pop(&q, &buf);
                }
                lqueue_print(&q);
                puts("1 - добавить элемент в очередь");
                puts("2 - удалить элемент из очереди");
                puts("0 - выйти из программы");
                printf("Выберите дейсвтие: ");
            }
            lqueue_delete(&q);
        }
        if (ch == 3)
        {
            aqueue_t a;
            lqueue_t l;
            int buf;
            int n = 10000;
            clock_t time1, time2;
            lqueue_init(&l);
            aqueue_init(&a);
            time1 = clock();
            for (int i = 0; i < n; ++i)
            {
                aqueue_push(&a, 10);
            }
            time1 = clock() - time1;
            time2 = clock();
            for (int i = 0; i < n; ++i)
            {
                aqueue_pop(&a, &buf);
            }
            time2 = clock() - time2;
            printf("Время добавления %d элементов в очередь массивом: %ld\n", n, time1);
            printf("Время удаления %d элементов из очереди массивом: %ld\n", n, time2);

            time1 = clock();
            for (int i = 0; i < n; ++i)
            {
                lqueue_push(&l, 10);
            }
            time1 = clock() - time1;
            time2 = clock();
            for (int i = 0; i < n; ++i)
            {
                lqueue_pop(&l, &buf);
            }
            time2 = clock() - time2;
            printf("Время добавления %d элементов в очередь списком: %ld\n", n, time1);
            printf("Время удаления %d элементов из очереди списком: %ld\n", n, time2);
        }
        if (ch == 4)
            task_real();
    }
    return 0;
}
