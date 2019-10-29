#ifndef _ERRDEF_H_
#define _ERRDEF_H_

#define OK 0

// input errors
#define STUDENT_INPUT_ERROR 1
#define GETLINE_ERROR 2
#define DATE_INPUT_ERROR 3
#define INDEX_INPUT_ERROR 7


// file errors
#define FILE_OPEN_ERROR 8;

// student and student_database errors
#define FILE_FORMAT_ERROR 4
#define STUDENT_DB_OVERFILL 5
#define STUDENT_DB_ACTION_INPUT_ERROR -1
#define UNDEFINED_ACTION 6

void handle_error(int error);

#endif
