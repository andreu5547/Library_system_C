#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse_csv.h"
#include "StructsAndMethods.h"
#include "HelpFunctions.h"
#include "output_csv.h"
#include "config.h"


int main() {
    LIBRARY *new_library = InitLib();

    parse_csv_books(books_file_name, new_library);
    parse_csv_students(students_file_name, new_library);
    parse_csv_users(users_file_name, new_library);
    parse_csv_students_books(students_books_file_name, new_library);

    int run = 1;
    char c, inp;
    int isbn, quantity;
    char author[MAX_DATA_SIZE] = "", title[MAX_DATA_SIZE] = "";
    USER *user = NULL;
    char login[MAX_DATA_SIZE] = "", password[MAX_DATA_SIZE] = "";
    int number_gradebook;
    char surname[MAX_DATA_SIZE] = "", name[MAX_DATA_SIZE] = "", patronymic[MAX_DATA_SIZE] = "", faculty[MAX_DATA_SIZE] = "", specialization[MAX_DATA_SIZE] = "";

    while (run) {
        if (user != NULL) {
            printhelp();
            while (user != NULL) {
                c = getchar();
                system("cls");
                fflush(stdin);
                switch (c) {
                    case '1':
                        if (user->edit_book == 1) {
                            puts("To add or update book enter 1, to delete book enter 2");
                            inp = getchar();
                            fflush(stdin);
                            switch (inp) {
                                case '1':
                                    puts("Enter data in format: isbn author title quantity");
                                    scanf("%d %s %s %d", &isbn, author, title, &quantity);
                                    fflush(stdin);
                                    AddBook(new_library, isbn, author, title, quantity, 0);
                                    break;
                                case '2':
                                    puts("Enter isbn book");
                                    scanf("%d", &isbn);
                                    fflush(stdin);
                                    DeleteBook(new_library, isbn);
                                    break;
                            }
                        } else puts("Error access denied!");
                        printhelp();
                        break;
                    case '2':
                        if (user->edit_student == 1) {
                            puts("To add or update student enter 1, to delete student enter 2");
                            inp = getchar();
                            fflush(stdin);
                            switch (inp) {
                                case '1':
                                    puts("Enter data in format: number_gradebook surname name patronymic faculty specialization");
                                    scanf("%d %s %s %s %s %s", &number_gradebook, surname, name, patronymic, faculty, specialization);
                                    fflush(stdin);
                                    AddStudent(new_library, number_gradebook, surname, name, patronymic, faculty, specialization);
                                    break;
                                case '2':
                                    puts("Enter number_gradebook to delete");
                                    scanf("%d", &number_gradebook);
                                    fflush(stdin);
                                    DeleteStudent(new_library, number_gradebook);
                                    break;
                            }
                        } else puts("Error access denied!");
                        printhelp();
                        break;
                    case '3':
                        puts("To give out a book enter 1, to pick up enter 2");
                        inp = getchar();
                        fflush(stdin);
                        switch (inp) {
                            case '1':
                                puts("Enter data in format: <number_gradebook student> <isbn book>");
                                scanf("%d %d", &number_gradebook, &isbn);
                                fflush(stdin);
                                GiveBook(new_library, number_gradebook, isbn, 1);
                                break;
                            case '2':
                                puts("Enter data in format: <number_gradebook student> <isbn book>");
                                scanf("%d %d", &number_gradebook, &isbn);
                                fflush(stdin);
                                PickUpBook(new_library, number_gradebook, isbn);
                                break;
                        }
                        printhelp();
                        break;
                    case '4':
                        PrintLibInfo(new_library);
                        printhelp();
                        break;
                    case '5':
                        out_csv_books(books_file_name, new_library);
                        out_csv_students(students_file_name, new_library);
                        out_csv_users(users_file_name, new_library);
                        out_csv_students_books(students_books_file_name, new_library);
                        puts("Data save!");
                        printhelp();
                        break;
                    case '6':
                        DestroyLib(new_library);
                        new_library = InitLib();

                        parse_csv_books(books_file_name, new_library);
                        parse_csv_students(students_file_name, new_library);
                        parse_csv_users(users_file_name, new_library);
                        parse_csv_students_books(students_books_file_name, new_library);
                        puts("Complete!");
                        printhelp();
                        break;
                    case '7':
                        user = NULL;
                        break;
                    default:
                        printhelp();
                }
            }
        }
        else {
            while (user == NULL) {
                printhelplog_ex();
                scanf("%s", login);
                fflush(stdin);
                if (strcmp(login, "exit") == 0) {
                    run = 0;
                    break;
                }
                if (strcmp(login, "login") == 0) {
                    printhelplogin();
                    scanf("%s %s", login, password);
                    fflush(stdin);
                    for (int i = 0; i < new_library->num_users; ++i)
                        if (strcmp(new_library->users[i]->login, login) == 0)
                            if (strcmp(new_library->users[i]->password, password) == 0) {
                                user = new_library->users[i];
                                break;
                            }
                    if (user != NULL) {
                        break;
                    }
                }
            }
        }
    }

    out_csv_books(books_file_name, new_library);
    out_csv_students(students_file_name, new_library);
    out_csv_users(users_file_name, new_library);
    out_csv_students_books(students_books_file_name, new_library);
    puts("Data save!");
    DestroyLib(new_library);
    return 0;
}
