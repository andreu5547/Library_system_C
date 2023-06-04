#ifndef LIBSYSTEM_STRUCTSANDMETHODS_H
#define LIBSYSTEM_STRUCTSANDMETHODS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "config.h"

typedef struct BOOK {
    int isbn;
    char *fnauthor;
    char *title;
    int quantity;
    int quantity_in_stock;
} BOOK;

typedef struct STUDENT {
    int number_gradebook;
    char *surname;
    char *name;
    char *patronymic;
    char *faculty;
    char *specialization;
    int *books_isbn;
    int num_books;
    int cap_books;
} STUDENT;

typedef struct USER {
    char *login;
    char *password;
    int edit_student;
    int edit_book;
} USER;

typedef struct LIBRARY {
    USER **users;
    int num_users;
    int cap_users;
    STUDENT **students;
    int num_studets;
    int cap_studets;
    BOOK **books;
    int num_books;
    int cap_books;
} LIBRARY;

LIBRARY *InitLib();

void DestroyLib(LIBRARY *library);

void AddUser(LIBRARY *library, char *login, char *password, int edit_student, int edit_book);

void AddBook(LIBRARY *library, int isbn, char *fnauthor, char *title, int quantity, int quantity_in_stock);

void DeleteBook(LIBRARY *library, int isbn);

void AddStudent(LIBRARY *library, int number_gradebook, char *surname, char *name, char *patronymic, char *faculty,
                char *specialization);

void GiveBook(LIBRARY *library, int number_gradebook, int isbn, int show_iss);

void PickUpBook(LIBRARY *library, int number_gradebook, int isbn);

void DeleteStudent(LIBRARY *library, int number_gradebook);

void PrintLibInfo(LIBRARY *library);

#endif //LIBSYSTEM_STRUCTSANDMETHODS_H
