#include "mgen.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void filegen_menu()
{
    puts("Генерация матрицы");
    int rows, columns, elems, row_elems;
    printf("Введите количество строк и столцов, от 2 до 1000: ");
    while (scanf("%d%d", &rows, &columns) != 2 && (rows >= 2) && (rows <= 1000) &&
           (columns >= 2) && (columns <= 1000))
        printf("Неправильно, введите снова: ");

    printf("Введите количество ненулевых элементов в матрице: ");
    while (scanf("%d", &elems) != 1 && (elems >= 0) && (elems <= rows * columns))
        printf("Неправильно, введите снова: ");
    
    printf("Введите количество ненулевых элементов в векторе: ");
    while (scanf("%d", &row_elems) != 1 && (elems >= 0) && (elems <= columns))
        printf("Неправильно, введите снова: ");
    
    printf("%d\n", filegen(CACHE_MATRIX_FILENAME, rows, columns, elems, row_elems));
}

int filegen(const char *filename, int rows, int columns, int elems, int row_elems)
{
    FILE *f = fopen(filename, "w");
    int count = 0;
    double prob = (double)elems / (rows * columns);
    double rprob = (double)row_elems / (columns);

    srand(time(NULL));

    if (!f)
    {
        printf("Cant open %s\n", filename);
        return -1;
    }
    // printf("%lf %lf\n", prob, rprob);

    fprintf(f, "%d %d\n", rows, columns);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            // printf("%lf\n", generate_prob());
            if (generate_prob() > prob)
                fprintf(f, "%d ", 0);
            else
            {
                fprintf(f, "%d ", rand() % 100);
                ++count;
            }
        }
        fprintf(f, "\n");
    }

    for (int i = 0; i < columns; ++i)
    {
        if (generate_prob() > rprob)
            fprintf(f, "%d ", 0);
        else
            fprintf(f, "%d ", rand() % 10 + 1);
    }
    fprintf(f, "\n");

    fclose(f);
    return count;
}

double generate_prob()
{
    return (double)(rand() % 100) / 100;
}
