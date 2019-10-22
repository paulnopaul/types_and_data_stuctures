#include "errdef.h"

#include <stdio.h>

void handle_error(int error)
{
    switch (error)
    {
        case 0:
            break;
        case 1:
            puts("\nStudent input error");
            break;
        case 2:
            puts("\nGetline error");
            break;
        case 3:
            puts("\nDate input error");
            break;
        case 4:
            puts("\nFile format error");
            break;
        case 5:
            puts("\nStudent db overfill");
            break;
        case 6:
            puts("\nUndefined action");
            break;
        case 7:
            puts("\nIndex input error");
            break;
        case 8:
            puts("\nFile open error");
            break;
        default:
            puts("\nUndefined error");
    }
}