#include "menu.h"

#include <stdio.h>
#include <time.h>

#include "lqueue.h"
#include "aqueue.h"
#include "service_line.h"

void menu_print_menu()
{
    printf("Cheklin Pavel"
           "Program for list and array queues analysis\n"
           "Actions:\n"
           "1 - Check linked list queue memory fragmentation\n"
           "2 - Run service system with linked list queue\n"
           "3 - Run service system with array queue\n"
           "4 - Run both systems\n"
           "\n\n\n0 - Exit program\n");
    printf("Input command: ");
}

int read_action(int *action)
{
    if (scanf("%d", action) == 1 && *action >= 0 && *action <= 4)
        return 1;
    return 0;
}
/*
Смоделировать процесс обслуживания до выхода из ОА2 первых 1000 заявок. Выдавать на экран после обслуживания в 
ОА2 каждых 100 заявок информацию о текущей и средней длине каждой очереди, а в конце процесса - общее время моделирования, 
пользователя выдачу на экран адресов элементов очереди при удалении и добавлении элементов. Проследить, возникает ли 
ри этом фрагментация памяти.
*/

int handle_action(int action)
{
    switch (action)
    {
    case 0:
        return MENU_EXIT;
        break;
    case 1:
        lqueue_check_memory();
        break;
    case 2:
        lqueue_line();
        break;
    case 3:
        aqueue_line();
        break;
    case 4:
        lqueue_line();
        aqueue_line();
        break;
    }
    return 1;
}

void put_error(const char *errname)
{
    printf("Error: %s", errname);
}

void wait_to_clean()
{
    for (; getchar() == '\n';)
        ;
    puts("Press Enter to continue:");
    for (; getchar() == '\n';)
        ;
}

int menu_mainloop()
{
    int code = 0;
    int action;
    while (code != MENU_EXIT)
    {
        system("clear");
        menu_print_menu();
        if (read_action(&action))
        {
            system("clear");
            handle_action(action);
        }
        else
            put_error("Wrong action");
        wait_to_clean();
    }
    return code;
}
