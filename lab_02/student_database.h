/*
Чеклин Павел ИУ7-32Б
Таблица студентов

Ключ - средний балл

 */

#ifndef _STUDENT_DATABASE_H_
#define _STUDENT_DATABASE_H_

#include "student.h"

#include <stdio.h>

#define MAX_DB_SIZE 100


typedef struct key
{
    int index;
    double value;
} key;

typedef key key_arr_t[MAX_DB_SIZE];

typedef struct student_database
{
    int size;
    key_arr_t keys;
    student db[MAX_DB_SIZE];
} student_database;


void key_swap(key *k1, key *k2);

// чтение таблицы из файла (файл должен быть открыт в режиме чтения)
int student_db_read_from_file(FILE *f, student_database *db);

// чтение таблицы из файла (с вводом имени файла)
int student_db_read_from_file_input(student_database *db);

// создание массива ключей (в считанной таблице)
void student_db_create_key_array(student_database *db);

// создание таблицы из файла (файл должен быть открыт в режиме чтения)
int student_db_create_file(FILE *f, student_database *db);

// вывод таблицы студентов в консоль
void student_db_console_output(FILE *f, student_database db);

// вывод таблицы в файл (файл должен быть открыт в режиме записи)
int student_db_file_output(FILE *f, student_database db);

// вывод таблицы в файл (с вводом имени файла)
int student_db_file_output_input(student_database db);

// добавление элемента в конец таблицы
int student_db_add(student_database *db, student to_add);

// добавление элемента в конец таблицы с вводом элемента
int student_db_add_input(student_database *db);

// удаление элемента из таблицы по индексу
int student_db_delete(student_database *db, int delete_index);

// удаление элемента из таблицы по индексу с вводом индекса
int student_db_delete_input(student_database *db);

// перемена элементов местами
int student_db_swap(student_database *db, int index_1, int index_2);

// сортировка массива ключей
double student_db_key_sort(student_database *db);

// сортировка таблицы
double student_db_sort(student_database *db);

// считываение таблицы из файла file.student
int student_db_lab_file_read(student_database *db);

// вывод таблицы по массиву ключей
void student_db_key_output(student_database db);

// сортировка массива студентов системной сортировкой
double student_db_sys_qsort(student_database *db);


int key_cmp(key* left, key* right);

// сортировка массива ключей таблицы системной быстрой сортировкой
double student_db_key_sys_qsort(student_database *db);

// проверка времени сортировки таблицы системной быстрой сортировкой
double student_db_system_qsort_check_time(student_database db);

// проверка времени сортировки массива ключей системной быстрой сортировко
double student_db_key_system_qsort_check_time(student_database db);

// проверка времени сортировки таблицы сортировкой выбором
double student_db_selection_check_time(student_database db);

// проверка времени сортировки массива ключей сортировкой выбором
double student_db_key_selection_check_time(student_database db);

// функция вывода времени различных сортировок
void student_db_sort_output(student_database db);

#endif