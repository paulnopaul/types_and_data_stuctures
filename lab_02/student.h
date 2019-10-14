/*
Чеклин Павел ИУ7-32Б
Типы и структуры данных лабораторная работа 2
Таблица
Данные:
имя, пол (м, ж), возраст, средний балл за сессию, дата поступления
адрес:
дом : (улица, №дома, №кв );
общежитие : (№общ., №комн.);
Ввести общий список студентов группы.
Вывести список студентов, живущих в общежитии указанного года поступления.

Input example (console)
h
Paul
m
13
4.4
03.09.2000
Street Street
12
13

Input example(file)
h,Paul,m,19,4.40,03.09.2000,Tverskaya,12,13

*/
#ifndef _TABLE_H_
#define _TABLE_H_

#include "date.h"

#include <stdio.h>

#define FILE_FORMAT_SEP ','

#define STR_SIZE 30

// строка длиной 100
typedef char str_t[STR_SIZE + 1];

// тип дома
typedef enum _house_type
{
    HOUSE, DORMITORY
} house_type;

// пол
typedef enum _sex
{
    MALE, FEMALE, OTHER
} sex;

// тип студент
typedef struct _student
{
    house_type type;
    str_t name;
    sex gender;
    int age;
    double exam_mark;
    date admission_date;
    str_t street; // if type is HOUSE
    int house_number;
    int room_number;
} student;

int my_getline(FILE *f, str_t s, char end_symbol);

// конструтор студента, живущего в доме
student make_house_student(house_type t, str_t n, sex s, int a, double mark, date dat, str_t strt, int num, int rn);

// конструктор студента, живущего в общежитии
student make_dormitory_student(house_type t, str_t n, sex s, int a, double mark, date dat, int num, int rn);

// ввод студента из f (вариант для консоли)
int student_console_input(FILE* f, student *st);

// ввод стдудента из f (вариант для файла)
int student_file_input(FILE* f, student *st);

int student_file_output(FILE* f, student st);

// вывод студента в f
void student_console_output(FILE* f, student st);

// сравнение студентов по ключу (средней оценке) (для сортировки)
int student_key_cmp(const student *left, const student *right);



#endif