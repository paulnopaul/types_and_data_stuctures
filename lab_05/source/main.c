/*
Чеклин Павел ИУ7-32Б
Программа для работы с очередями

Очередь - последовательный сисок переменной длины, выключение в
который идет с одной стороны (с хвоста), а исключение - с другой 
стороны (с головы). Принципе рабKоты очереди: первым пришел - первым
вышел.

Моделировать простейшую линейную очередь можно на основе вектора
или на основе списка
В один и тот же момент одна заявка может придти в очередь, а 
другая - начать обрабатываться или выйти из системы.
Процент расхождения расчтного времени и времени, получившегося
при работа программы должен быть не больше 2-3 процентов
Расчетное время моделирования (по входу) = среднее время
прихода заявки * количество вошедших заявокю.

Если есть 2 очереди, то расчет идет для каждой из очередей.

Расчетное время моделирования (по выходу) = 
среднее время обработки заявки * количество обработанных заявок.

Если есть 2 очереди и один аппарат, то время моделирования будет 
суммой времен обслуживаний заявок каждого типа.

Если время обработки больше времени прихода, то 
очередь будет расти и время модерования будет определяться временем обработки, 
а количество вошедших заявок будет = времени
моделирования / среднее время прихода заявки. 

Если время прихода больше верени обработки, то очереди не будет, 
и время моделирования будет определяться временем прихода 
заявок




Вариант 2

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/aqueue.h"
#include "../include/lqueue.h"
#include "../include/taskqueue.h"
#include "../include/menu.h"

void aqueue_test();

void lqueue_test();

void task_test();

void lapp();

int main()
{
    puts("Main");
    system("clear");
    // aqueue_test();
    // lqueue_test();
    // task_test();
    // lapp();
    app();
    return 0;
}

void lapp()
{
    tqueue_t t;
    t.sys.state = 'a';
    task_init(&t);
    task_task(&t);
    t.sys.state = 'l';
    task_task(&t);
}

void aqueue_test()
{
    aqueue_t q;
    int buf;
    aqueue_init(&q);
    aqueue_print(&q);
    for (int i = 0; i < 10; ++i)
    {
        if (aqueue_push(&q, i + 1) == 0)
            aqueue_print(&q);
        else
            puts("OVERFILLED");
    }

    for (int i = 0; i < 5; ++i)
    {
        if (aqueue_pop(&q, &buf) == 0)
        {
            aqueue_print(&q);
        }
        else
            puts("OVERFILLED");
    }
    for (int i = 0; i < 5; ++i)
    {
        if (aqueue_push(&q, i + 1) == 0)
            aqueue_print(&q);
        else
            puts("OVERFILLED");
    }

    for (int i = 0; i < 3; ++i)
    {
        if (aqueue_pop(&q, &buf) == 0)
        {
            aqueue_print(&q);
        }
        else
            puts("OVERFILLED");
    }
    for (int i = 0; i < 3; ++i)
    {
        if (aqueue_push(&q, i + 1) == 0)
            aqueue_print(&q);
        else
            puts("OVERFILLED");
    }

    for (int i = 0; i < 4; ++i)
    {
        if (aqueue_pop(&q, &buf) == 0)
        {
            aqueue_print(&q);
        }
        else
            puts("OVERFILLED");
    }
    for (int i = 0; i < 4; ++i)
    {
        if (aqueue_push(&q, i + 1) == 0)
            aqueue_print(&q);
        else
            puts("OVERFILLED");
    }
}

void lqueue_test()
{
    lqueue_t q;
    int buf;
    lqueue_init(&q);
    lqueue_print(&q);
    for (int i = 0; i < 10; ++i)
    {
        if (lqueue_push(&q, i + 1) == 0)
            lqueue_print(&q);
        else
            puts("OVERFILLED");
    }

    for (int i = 0; i < 5; ++i)
    {
        if (lqueue_pop(&q, &buf) == 0)
        {
            lqueue_print(&q);
        }
        else
            puts("OVERFILLED");
    }
    for (int i = 0; i < 5; ++i)
    {
        if (lqueue_push(&q, i + 1) == 0)
            lqueue_print(&q);
        else
            puts("OVERFILLED");
    }

    for (int i = 0; i < 3; ++i)
    {
        if (lqueue_pop(&q, &buf) == 0)
        {
            lqueue_print(&q);
        }
        else
            puts("OVERFILLED");
    }
    for (int i = 0; i < 3; ++i)
    {
        if (lqueue_push(&q, i + 1) == 0)
            lqueue_print(&q);
        else
            puts("OVERFILLED");
    }

    for (int i = 0; i < 4; ++i)
    {
        if (lqueue_pop(&q, &buf) == 0)
        {
            lqueue_print(&q);
        }
        else
            puts("OVERFILLED");
    }
    for (int i = 0; i < 4; ++i)
    {
        if (lqueue_push(&q, i + 1) == 0)
            lqueue_print(&q);
        else
            puts("OVERFILLED");
    }
    lqueue_delete(&q);
}
