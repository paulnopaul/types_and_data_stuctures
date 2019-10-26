/*
Чеклин Павел ИУ7-32Б
Типы и структуры данных. Лабораторная работа 2
Вариант 3
Создать таблицу, содержащую не менее 40-ка записей (тип – запись с вариантами).
Упорядочить данные в ней по возрастанию ключей, где ключ – любое невариантное поле (по выбору программиста), используя:
а) саму таблицу, б) массив ключей (возможность добавления и удаления записей в ручном режиме обязательна)
Имеются описания:
Type жилье = (дом, общежитие);
Данные:
имя, пол (м, ж), возраст, средний балл за сессию, дата поступления
адрес:
дом : (улица, №дома, №кв );
общежитие : (№общ., №комн.);
Ввести общий список студентов группы.
Вывести список студентов, живущих в общежитии указанного года поступления.

*/

#include <stdio.h>

#include "db_menu.h"
#include "errdef.h"

#include <time.h>

void test_file_output()
{
    student_database bmstu_iu;
    FILE *in = fopen("../file.student", "r");
    if (in)
    {
        if (student_db_read_from_file(in, &bmstu_iu) == OK)
            student_db_console_output(stdout, bmstu_iu);
    }
    else
        puts("Wrong file");
    fclose(in);
}

void clock_check()
{
    clock_t t1 = clock(), t2;
    for (long i = 0; i < 10000000000; ++i);
    t2 = clock();
    printf("%lf", (double) (t2 - t1) / CLOCKS_PER_SEC);
}

void test_student_file_output()
{
    student st;
    FILE *f = fopen("../f.student", "r");
    if (f)
    {
        printf("%d\n", student_file_input(f, &st));
        student_console_output(stdout, st);
        student_file_output(stdout, st);
    }
    fclose(f);
}

void test_student_db_file_output()
{
    student_database bmstu_iu;
    FILE *in = fopen("../file.student", "r");
    if (in)
    {
        if (student_db_read_from_file(in, &bmstu_iu) == OK)
            student_db_console_output(stdout, bmstu_iu);
        fclose(in);
        student_db_file_output_input(bmstu_iu);
    }
    else
        puts("Wrong file");
}

int main()
{
    menu_main();
    return 0;
}