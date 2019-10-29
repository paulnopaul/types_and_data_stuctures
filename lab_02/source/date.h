#ifndef _DATE_H_
#define _DATE_H_

#include <stdio.h>

typedef struct _date
{
    int year;
    int month;
    int day;
} date;

date make_date(int year, int month, int day);

// date input from f
int date_input(FILE* f, date* d);

// date output to f
void date_output(FILE* f, date d);

#endif
