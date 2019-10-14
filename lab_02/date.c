#include "date.h"

#include <stdio.h>

#include "errdef.h"

date make_date(int year, int month, int day)
{
    date d = {.year = year, .month = month, .day = day};
    return d;
}

int date_input(FILE* f, date* d)
{
    if (fscanf(f, "%d.%d.%d", &d->day, &d->month, &d->year) == 3 &&
        (d->day <= 31) && (d->day >= 1) && (d->month <= 12) && (d->month >= 1) &&
        (d->year >= 0) && (d->year <= 2019))
        return OK;
    return DATE_INPUT_ERROR;
}

void date_output(FILE* f, date d)
{
    fprintf(f, "%d.%02d.%02d", d.year, d.month, d.day);
}