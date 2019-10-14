#include "errdef.h"

#include <stdio.h>

void handle_error(int error)
{
    switch (error)
    {
        case 0:
            break;
        case 1:
            puts("Student input error");
            break;
        case 2:
            puts("Getline error");
            break;
        case 3:
            puts("Date input error");
            break;
        case 4:
            puts("File format error");
            break;
        case 5:
            puts("Student db overfill");
            break;
        case 6:
            puts("Undefined action");
            break;
        case 7:
            puts("Index input error");
            break;
        case 8:
            puts("File open error");
            break;
        default:
            puts("Undefined error");
    }
}