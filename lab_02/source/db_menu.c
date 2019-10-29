//
// Created by Павел Чеклин on 07/10/2019.
//

#include "db_menu.h"

#include <stdio.h>

#include "errdef.h"

void menu_output()
{
    printf("------------------------------------------------------------------------------------------\n"
           "Программа для работы с таблицей студентов\n"
           "Максимальный размер таблицы - 100 строк \n"
           "Действия:\n"
           "2 - Считать таблицу из файла file.student\n"
           "3 - Считать таблицу из файла (по адресу)\n"
           "4 - Записать таблицу в файл\n"
           "5 - Добавить студента в конец таблицы\n"
           "6 - Удалить студента из таблицы (по индексу)\n"
           "7 - Отсортировать таблицу по средней оценке (сортировка выбором)\n"
           "8 - Отсортировать массив ключей (сортировка выбором)\n"
           "9 - Вывести таблицу в соотвествии с массивом ключей\n"
           "10 - Вывести различное время сортировок таблицы (не меняет таблицу и таблицу ключей)\n"
           "11 - Сортировка таблицы (системная быстрая сортировка)\n"
           "12 - Сортировка массива ключей (системная быстрая сортировка)\n"
           "13 - Вывести студентов указанного года постуления, живущих в общежитии\n"
           "*****************************************************\n\n"
           "1 - Вывести таблицу\n"
           "0 - Выход из программы (без сохранения в файл)\n"
           "------------------------------------------------------------------------------------------\n"
           "Введите действие: ");
}

int menu_act(student_database *db, int action)
{
    int error = OK;
    switch (action)
    {
        case 0:
            // выход из программы
            error = MENU_EXIT;
            break;
        case 1:
            // вывод базы данных
            student_db_console_output(stdout, *db);
            break;
        case 2:
            // считать из файла (дла лабораторной)
            error = student_db_lab_file_read(db);
            break;
        case 3:
            // Считать из пользовательского файла
            error = student_db_read_from_file_input(db);
            break;
        case 4:
            // Записать базу данных в файл
            error = student_db_file_output_input(*db);
            break;
        case 5:
            // Добавить студента в конец базы данных
            error = student_db_add_input(db);
            break;
        case 6:
            // Удалить студента по индексу
            error = student_db_delete_input(db);
            break;
        case 7:
            // Отсортировать базу данных по средней оценке
            printf("Время сортировки = %lf\n", student_db_sort(db));
            break;
        case 8:
            // Отсортировать массив ключей
            printf("Время сортировки = %lf\n", student_db_key_sort(db));
            break;
        case 9:
            // Вывод таблицы в соотвествии с массивом ключей
            student_db_key_output(*db);
            break;
        case 10:
            // вывод времени сортировки для различных алгоритмов
            student_db_sort_output(*db);
            break;
        case 11:
            // сортировка таблицы быстрой сортировкой
            printf("Время сортировки = %lf\n", student_db_sys_qsort(db));
            break;
        case 12:
            printf("Время сортировки = %lf\n", student_db_key_sys_qsort(db));
            // сортировка массива ключей быстрой сортировкой
            break;
        case 13:
            // вывести студентов указаного года поступления, живущих в общежитии
            student_db_dormitory_year_output(*db);
            break;
        default:
            error = UNDEFINED_ACTION;
    }
    return error;
}

int menu_input_action()
{
    int action;
    if (scanf("%d", &action) == 1 && action >= 0 && action <= MAX_ACTION)
        return action;
    return STUDENT_DB_ACTION_INPUT_ERROR;
}

int menu_start(student_database *db)
{
    int action = 1000;
    int error = OK;
    while (action != MENU_EXIT && action != STUDENT_DB_ACTION_INPUT_ERROR)
    {
        menu_output();
        action = menu_input_action();
        if (action != STUDENT_DB_ACTION_INPUT_ERROR)
            error = menu_act(db, action);
        if (error)
            handle_error(error);
    }
    return 0;
}

void menu_main()
{
    student_database db;
    db.size = 0;
    menu_start(&db);
}
