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
#include <time.h>

#include "aqueue.h"
#include "lqueue.h"
#include "service_line.h"
#include "menu.h"


void aqueue_test()
{
    aqueue a;
    int buf;
    aqueue_init(&a);
    for (int i = 0; i < QUEUE_SIZE * 2; ++i)
    {
        printf("%d %d\n", a.pin, a.pout);
        aqueue_push(&a, 123);
        aqueue_print(a);
        aqueue_pop(&a, &buf);
        aqueue_print(a);
        puts("");
    }
}

void lqueue_test()
{
    puts("List queue test");
    lqueue a;
    int buf;
    lqueue_init(&a);
    for (int i = 0; i < 10; ++i)
    {
        puts("PUSH");
        lqueue_push(&a, i);
        puts("POP");
        lqueue_pop(&a, &buf);
    }
    lqueue_print(a);
    lqueue_delete(&a);
}

void test_direction_choice()
{
    int p1c = 0, p2c = 0;
    srand(time(NULL));
    for (int i = 0; i < 100000; ++i)
        if (direction_choice(0.3, 0.7) == 1)
            p1c++;
        else
            p2c++;
    printf("%f %f\n", (float)p1c / (float)(p1c + p2c), (float)p2c / (float)(p1c + p2c));
}

void test_line()
{
    // aqueue_line();
    lqueue_line();
}

void rand_test()
{
    double time_sum = 0;
    srand(time(NULL));
    int time_count = 2000;
    for (int i = 0; i < time_count; ++i)
        time_sum += generate_time(1, 10);
    printf("%lf", time_sum / time_count);
}

int main()
{
    lqueue_line();
    // menu_mainloop();
    return 0;
}
