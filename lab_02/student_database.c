//
// Created by Павел Чеклин on 29/09/2019.
//

#include "student_database.h"

#include <time.h>
#include <stdlib.h>

#include "errdef.h"


int student_db_read_from_file(FILE *f, student_database *db)
{
    int error = OK, count = 0;
    while (!error && !feof(f))
    {
        error = student_file_input(f, &db->db[count]);
        ++count;
    }
    if (!error)
        db->size = count;
    return error;
}

// создание массива ключей (в считанной таблице)
void student_db_create_key_array(student_database *db)
{
    for (int i = 0; i < db->size; ++i)
    {
        db->keys[i].index = i;
        db->keys[i].value = db->db[i].exam_mark;
    }
}


// создание таблицы из фалй
int student_db_create_file(FILE *f, student_database *db)
{
    int error = OK;
    if ((error = student_db_read_from_file(f, db)) == OK)
        student_db_create_key_array(db);
    return error;
}

void student_db_console_output(FILE *f, student_database db)
{
    printf("Output format: index, type, name, gender, age, exam_mark, admission_date, street (if house),"
           " house_number, room_number\n");
    printf("------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < db.size; ++i)
    {
        printf("%-3d ", i);
        student_console_output(f, db.db[i]);
    }
    printf("------------------------------------------------------------------------------------------\n\n");
}

int student_db_add(student_database *db, student to_add)
{
    int error = (db->size >= MAX_DB_SIZE) * STUDENT_DB_OVERFILL;
    if (!error)
    {
        student st;
        db->db[db->size] = to_add;
        db->keys[db->size].index = db->size;
        db->keys[db->size].value = to_add.exam_mark;
        ++(db->size);
    }
    return error;
}

int student_db_delete(student_database *db, int delete_index)
{
    for (int i = delete_index; i < db->size - 1; ++i)
    {
        db->db[i] = db->db[i + 1];
        db->keys[i].value = db->keys[i + 1].value;
    }
    --(db->size);
    return OK;
}

int student_db_swap(student_database *db, int index_1, int index_2)
{
    student temp = db->db[index_1];
    db->db[index_1] = db->db[index_2];
    db->db[index_2] = temp;

    key tmp = db->keys[index_1];
    db->keys[index_1].value = db->keys[index_2].value;
    db->keys[index_2].value = tmp.value;

    return OK;
}


int student_db_lab_file_read(student_database *db)
{
    int error = OK;
    FILE *f = fopen("../file.student", "r");
    error = student_db_create_file(f, db);
    fclose(f);
    return error;
}

void key_swap(key *k1, key *k2)
{
    key temp = *k1;
    *k1 = *k2;
    *k2 = temp;
}

double student_db_key_sort(student_database *db)
{
    key min;
    int min_i;
    clock_t start_sort, end_sort;
    int i = 0, j = 0;
    start_sort = clock();
    for (i = 0; i < db->size; ++i)
    {
        min = db->keys[i];
        min_i = i;
        for (j = i + 1; j < db->size; ++j)
            if (db->keys[j].value < min.value)
            {
                min = db->keys[j];
                min_i = j;
            }
        key_swap(&db->keys[i], &db->keys[min_i]);
    }
    end_sort = clock();
    return (double) (end_sort - start_sort) / CLOCKS_PER_SEC;
}

double student_db_sort(student_database *db)
{
    student min;
    int min_i;
    clock_t start_sort, end_sort;
    int i = 0, j = 0;
    start_sort = clock();
    for (i = 0; i < db->size; ++i)
    {
        min = db->db[i];
        min_i = i;
        for (j = i + 1; j < db->size; ++j)
            if (db->db[j].exam_mark < min.exam_mark)
            {
                min = db->db[j];
                min_i = j;
            }
        student_db_swap(db, i, min_i);
    }
    end_sort = clock();
    student_db_create_key_array(db);
    return (double) (end_sort - start_sort) / CLOCKS_PER_SEC;
}

void student_db_key_output(student_database db)
{
    printf("Output format: index, type, name, gender, age, exam_mark, admission_date, street (if house),"
           " house_number, room_number\n");
    printf("------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < db.size; ++i)
    {
        printf("%-3d", db.keys[i].index);
        student_console_output(stdout, db.db[db.keys[i].index]);
    }
    printf("------------------------------------------------------------------------------------------\n\n");
}

int student_db_delete_input(student_database *db)
{
    int index;
    printf("Input delete_index: ");
    if (scanf("%d", &index) == 1 && ( index >= 0) && (index < db->size))
    {
        student_db_delete(db, index);
        return OK;
    }
    return INDEX_INPUT_ERROR;
}

int student_db_add_input(student_database *db)
{
    int error = OK;
    student st;
    puts("Student input");
    error = student_console_input(stdin, &st);
    if (!error)
        student_db_add(db, st);
    return error;
}

int student_db_file_output(FILE *f, student_database db)
{
    int error = OK;
    for (int i = 0; i < db.size; ++i)
        student_file_output(f, db.db[i]);
    return error;
}

int student_db_file_output_input(student_database db)
{
    char s[100];
    FILE *f;
    printf("Input filename: ");
    scanf("%s", s);
    puts(s);
    f = fopen(s, "w");
    if (f)
    {
        student_db_file_output(f, db);
        fclose(f);
        return OK;
    }
    return FILE_OPEN_ERROR;
}

int student_db_read_from_file_input(student_database *db)
{
    int error = OK;
    char s[100];
    FILE *f;
    printf("Input filename: ");
    scanf("%s", s);
    f = fopen(s, "r");
    if (f)
    {
        error = student_db_read_from_file(f, db);
        fclose(f);
    }
    return error;
}





