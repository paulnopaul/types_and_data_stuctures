#include "student.h"

#include <stdio.h>
#include <string.h>

#include "errdef.h"


student make_house_student(house_type t, str_t n, sex s, int a, double mark, date dat, str_t strt, int num, int rn)
{
    student stud = {.type = DORMITORY, .gender = s, .age = a, .exam_mark = mark, .admission_date = dat,
            .house_number = num, .room_number = rn};
    strcpy(stud.name, n);
    strcpy(stud.street, strt);
    return stud;
}

student make_dormitory_student(house_type t, str_t n, sex s, int a, double mark, date dat, int num, int rn)
{
    student stud = {.type = DORMITORY, .gender = s, .age = a, .exam_mark = mark, .admission_date = dat,
            .house_number = num, .room_number = rn};
    strcpy(stud.name, n);
    strcpy(stud.street, "");
    return stud;
}

int my_getline(FILE *f, str_t s, char end_symbol)
{
    int c = end_symbol, i, error = OK;
    // clean buffer
    while (c == end_symbol)
        c = getc(f);
    if (c != end_symbol)
        ungetc(c, f);

    for (i = 0; (c = getc(f)) != end_symbol && c != '\0' && i <= STR_SIZE; ++i)
        s[i] = c;

    if (i > STR_SIZE)
        error = GETLINE_ERROR;
    else
        s[i] = '\0';

    return error;
}

int student_console_input(FILE *f, student *st)
{
    int error = 0;
    char buf = 0;
    printf("Input type (h or d): ");
    if ((buf = getc(f)) != '\n')
        ungetc(buf, f);
    if (((buf = getc(f)) == 'h') || (buf == 'd'))
    {
        st->type = (buf == 'h') ? HOUSE : DORMITORY;
        printf("Input student name (max 30 symbols): ");
    }
    else
        error = STUDENT_INPUT_ERROR;

    if (!error && my_getline(f, st->name, '\n') == OK)
        printf("Input gender (m or f or o): ");
    else
        error = STUDENT_INPUT_ERROR;


    if (!error && (((buf = getc(f)) == 'm') || (buf == 'f') || (buf == 'o')))
    {
        switch (buf)
        {
            case 'm':
                st->gender = MALE;
                break;
            case 'f':
                st->gender = FEMALE;
                break;
            default:
                st->gender = OTHER;
        }
        printf("Input age: ");
    }
    else
        error = STUDENT_INPUT_ERROR;

    if (!error && (fscanf(f, "%d", &st->age) == 1) && (st->age > 0) && (st->age < 130))
        printf("Input exam mark (from 0 to 5): ");
    else
        error = STUDENT_INPUT_ERROR;

    if (!error && (fscanf(f, "%lf", &st->exam_mark) == 1) && (st->exam_mark >= 0) && (st->exam_mark <= 5))
        printf("Input admission date (day.month.year): ");
    else
        error = STUDENT_INPUT_ERROR;

    if (!error && (date_input(f, &st->admission_date) == OK))
    {
        if (st->type == HOUSE)
        {
            printf("Input street (max 30 symbols): ");
            if (my_getline(f, st->street, '\n') != OK)
                error = STUDENT_INPUT_ERROR;
        }
        if (!error)
            printf("Input house/dormitory number (from 1, only numbers): ");

        if (!error && (fscanf(f, "%d", &st->house_number) == 1) && (st->house_number > 0))
            printf("Input room number (from 1, only numbers): ");
        else
            error = STUDENT_INPUT_ERROR;

        if (!error && (fscanf(f, "%d", &st->room_number) == 1) && (st->room_number > 0))
            puts("STUDENT INPUT SUCCESS");
    }
    else
        error = STUDENT_INPUT_ERROR;
    return error;
}

int student_file_input(FILE *f, student *st)
{
    int error = 0;
    int buf = 0;
    printf("type ");
    if (((buf = getc(f)) == 'h') || (buf == 'd'))
    {
        st->type = (buf == 'h') ? HOUSE : DORMITORY;
        if ((buf = getc(f)) == FILE_FORMAT_SEP)
            printf("name ");
        else
            error = FILE_FORMAT_ERROR;
    }
    else
        error = STUDENT_INPUT_ERROR;

    if (!error && my_getline(f, st->name, FILE_FORMAT_SEP) == OK)
        printf("gender ");
    else
        error = STUDENT_INPUT_ERROR;


    if (!error && (((buf = getc(f)) == 'm') || (buf == 'f') || (buf == 'o')))
    {
        switch (buf)
        {
            case 'm':
                st->gender = MALE;
                break;
            case 'f':
                st->gender = FEMALE;
                break;
            default:
                st->gender = OTHER;
        }
        if ((buf = getc(f)) == FILE_FORMAT_SEP)
            printf("age ");
        else
            error = FILE_FORMAT_ERROR;
    }
    else
        error = STUDENT_INPUT_ERROR;

    if (!error && (fscanf(f, "%d", &st->age) == 1) && (st->age > 0) && (st->age < 130) &&
        ((buf = getc(f)) == FILE_FORMAT_SEP))
        printf("mark ");
    else if (buf != FILE_FORMAT_SEP)
        error = FILE_FORMAT_ERROR;
    else
        error = STUDENT_INPUT_ERROR;

    if (!error && (fscanf(f, "%lf", &st->exam_mark) == 1) && (st->exam_mark >= 0) && (st->exam_mark <= 5) &&
        ((buf = getc(f)) == FILE_FORMAT_SEP))
        printf("admission_date ");
    else if (buf != FILE_FORMAT_SEP)
        error = FILE_FORMAT_ERROR;
    else
        error = STUDENT_INPUT_ERROR;

    if (!error && (date_input(f, &st->admission_date) == OK) && ((buf = getc(f)) == FILE_FORMAT_SEP))
    {
        if (st->type == HOUSE)
        {
            printf("street ");
            if (my_getline(f, st->street, FILE_FORMAT_SEP) != OK)
                error = STUDENT_INPUT_ERROR;
        }
        if (!error)
            printf("house_number ");

        if (!error && (fscanf(f, "%d", &st->house_number) == 1) && (st->house_number > 0) &&
            ((buf = getc(f)) == FILE_FORMAT_SEP))
            printf("room_number ");
        else if (buf != FILE_FORMAT_SEP)
            error = FILE_FORMAT_ERROR;
        else
            error = STUDENT_INPUT_ERROR;

        if (!error && (fscanf(f, "%d", &st->room_number) == 1) && (st->room_number > 0) &&
            ((buf = getc(f)) == EOF || buf == '\n'))
            puts("STUDENT INPUT SUCCESS");
        else if (buf != FILE_FORMAT_SEP)
            error = FILE_FORMAT_ERROR;
        else
            error = STUDENT_INPUT_ERROR;

    }
    else if (buf != FILE_FORMAT_SEP)
        error = FILE_FORMAT_ERROR;
    else
        error = STUDENT_INPUT_ERROR;

    return error;
}

void student_console_output(FILE *f, student st)
{
    // type output
    if (st.type == HOUSE)
        printf("house     ");
    else if (st.type == DORMITORY)
        printf("dormitory ");

    // name output
    fprintf(f, "%15s ", st.name);

    // gender output
    if (st.gender == MALE)
        fprintf(f, "male   ");
    else if (st.gender == FEMALE)
        fprintf(f, "female ");
    else if (st.gender == OTHER)
        fprintf(f, "other  ");

    // age output
    fprintf(f, "%3d y.o. ", st.age);

    // mean exam mark output
    fprintf(f, "%3.2lf ", st.exam_mark);

    // admission date output
    date_output(f, st.admission_date);

    // street output
    if (st.type == HOUSE)
        fprintf(f, " %20s", st.street);
    else
        fprintf(f, "%20s ", "");

    fprintf(f, " %3d ", st.house_number);

    fprintf(f, "%3d\n", st.room_number);
}

int student_file_output(FILE *f, student st)
{
    int error = OK;
    fprintf(f, "%c,%s,%c,%d,%.2lf,", (st.type == HOUSE ? 'h' : 'd'), st.name,
            (st.gender == MALE ? 'm' : (st.gender == FEMALE ? 'f' : 'o')), st.age, st.exam_mark);
    date_output(f, st.admission_date);
    fprintf(f, ",%d,%d\n", st.house_number, st.room_number);
    return error;
}

int student_key_cmp(const student *left, const student *right)
{
    return (int) (100000 * (left->exam_mark - right->exam_mark));
}