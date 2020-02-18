/*
Чеклин Павел ИУ7-32Б

Типы и структуры данных

Лабораторная работа 6 
Деревья и хэш-таблицы

Вариант 2 

В текстовом файле содержатся целые числа. Построить ДДП из чисел файла. 
Вывести его на экран в виде дерева. 
Сбалансировать полученное дерево и вывести его на экран.

Построить хеш-таблицу из чисел файла. Использовать 
закрытое хеширование для устранения коллизий. 

Осуществить добавление введенного целого числа, если его там нет, 
в ДДП, в сбалансированное дерево, в хеш-таблицу и в файл. 

Сравнить время добавления, объем памяти и количество 
сравнений при использовании различных (4-х) структур данных.
Если количество сравнений в хеш-таблице больше 
указанного (вводить), то произвести реструктуризацию таблицы, выбрав другую функцию.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/dtree.h"
#include "../include/btree.h"
#include "../include/hashtable.h"


void file_add(const char *filename, int to_add);

int main(int argc, char **argv)
{
    dtree_t raw;
    int err = 0;
    dtree_t balanced;
    hashtable ht;
    int to_add, maxcol;

    // timers
    clock_t bstt, bbstt, hasht, filet;

    dtree_init(&raw);
    btree_init(&balanced);
    
    if (argc != 2)
    {
        puts("Wrong arg");
        return 1;
    }

    printf("Введите размер хеш таблицы, рекомендуется простое число, например 977: ");
    if (scanf("%d", &ht.size) == 1 && ht.size > 0 && ht.size < 1000)
        puts("");
    else 
    {
        puts("Hashtable size input error: ");
        return 1;
    }

    printf("Введите максимальное число коллизий: ");
    if (scanf("%d", &maxcol) == 1 && maxcol >= 0 && maxcol <= 10000)
        hashtable_init(&ht, ht.size);
    else 
    {
        puts("Input error");
        return 1;
    }

    // getting tree
    if (dtree_get(&raw, argv[1]))
    {
        puts("File input error");
        return 1;
    }

    dtree_put(&raw, "raw1");

    // balancing tree
    dtree_create_balanced(&raw, &balanced);
    dtree_put(&balanced, "balanced1");

    // getting hashtable
    if (hashtable_get(&ht, argv[1]))
    {
        dtree_delete(&raw);
        dtree_delete(&balanced);
        hashtable_delete(&ht);
        return 1;
    }
    system("clear");
    if (ht.max_collisions > maxcol)
    {
        printf("Для метода вычисления остатка превышено максимальное число коллизий (%d), будет использован метод умножения\n", ht.max_collisions);
        puts("Старая таблица: ");
        hashtable_put(ht);

        hashtable_delete(&ht);
        hashtable_init(&ht, ht.size);

        ht.hashfunc = hash_prod;
        err = hashtable_get(&ht, argv[1]);
        if (err)
        {
            dtree_delete(&raw);
            dtree_delete(&balanced);
            hashtable_delete(&ht);
            return 1;
        }
        puts("Новая таблица");
    }

    hashtable_put(ht);


    // ************** Adding elements **************

    printf("Введите число: ");
    while (scanf("%d", &to_add) != 1)
        printf ("Ошибка, попробуйте еще раз: ");

    bstt = clock();
    dtree_add_node(&raw, to_add);
    bstt = clock() - bstt;
    dtree_put(&raw, "raw2");

    bbstt = clock();
    btree_insert(&balanced, to_add);
    bbstt = clock() - bbstt;
    dtree_put(&balanced, "balanced2");

    hasht = clock();
    err = hashtable_add(&ht, to_add);
    hasht = clock() - hasht;
    if (err)
    {
        dtree_delete(&raw);
        dtree_delete(&balanced);
        hashtable_delete(&ht);
        return 1;
    }
    hashtable_put(ht);

    filet = clock();
    file_add(argv[1], to_add);
    filet = clock() - filet;

    printf("Время добавления в обычное дерево:          %ld\n", bstt);
    printf("Время добавления в сбалансированное дерево: %ld\n", bbstt);
    printf("Время добавления в хэш таблицу:             %ld\n", hasht);
    printf("Время добавления в файл:                    %ld\n", filet);

    dtree_delete(&raw);
    dtree_delete(&balanced);
    hashtable_delete(&ht);
    // system("rm -f ../cache/*");
    return 0;
}

/*
int mainbtree()
{
    dtree_t balanced;
    btree_init(&balanced);
    char buf[100];

    for (int i = 0; i < 10; ++i)
    {
        printf("Insert %d\n---\n", i);
        btree_insert(&balanced, i);
        snprintf(buf, 100, "balanced%d", i);
        dtree_put(&balanced, buf);
        printf("---\n");
    }

    dtree_delete(&balanced);
}
*/

int hashtablemain()
{
    hashtable h;
    hashtable_init(&h, 1001);
    for (int i = 0; i < 100; ++i)
        hashtable_add(&h, random());
    printf("%d\n", h.max_collisions);
    hashtable_put(h);
    hashtable_delete(&h);
    return 0;
}

void file_add(const char *filename, int to_add)
{
    FILE *f = fopen(filename, "a");
    if (f)
    {
        fprintf(f, "\n%d", to_add);
        fclose(f);
    }
    return;
}
