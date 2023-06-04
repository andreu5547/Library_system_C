#ifndef LIBSYSTEM_PARSE_CSV_H
#define LIBSYSTEM_PARSE_CSV_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "StructsAndMethods.h"
#include "config.h"

int parse_csv_books(char *file_name, LIBRARY *library);

int parse_csv_students(char *file_name, LIBRARY *library);

int parse_csv_users(char *file_name, LIBRARY *library);

int parse_csv_students_books(char *file_name, LIBRARY *library);

#endif //LIBSYSTEM_PARSE_CSV_H
