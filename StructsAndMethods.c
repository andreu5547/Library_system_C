#include "StructsAndMethods.h"


LIBRARY *InitLib() {
    LIBRARY *library = malloc(sizeof(LIBRARY));
    library->cap_books = INIT_MEM;
    library->num_books = 0;
    library->cap_users = INIT_MEM;
    library->num_users = 0;
    library->cap_studets = INIT_MEM;
    library->num_studets = 0;
    library->users = malloc(sizeof(USER*) * library->cap_users);
    library->books = malloc(sizeof(BOOK*) * library->cap_books);
    library->students = malloc(sizeof(STUDENT*) * library->cap_studets);
    return library;
}

void DestroyLib(LIBRARY *library) {
    for (int i = 0; i < library->num_studets; ++i) {
        free(library->students[i]->surname);
        free(library->students[i]->name);
        free(library->students[i]->patronymic);
        free(library->students[i]->faculty);
        free(library->students[i]->specialization);
        free(library->students[i]->books_isbn);
        free(library->students[i]);
    }
    free(library->students);

    for (int i = 0; i < library->num_books; ++i) {
        free(library->books[i]->fnauthor);
        free(library->books[i]->title);
        free(library->books[i]);
    }
    free(library->books);

    for (int i = 0; i < library->num_users; ++i) {
        free(library->users[i]->login);
        free(library->users[i]->password);
        free(library->users[i]);
    }
    free(library->users);

    free(library);
}


void AddUser(LIBRARY *library, char *login, char *password, int edit_student, int edit_book) {
    USER *new_user = malloc(sizeof(USER));
    new_user->login = malloc(sizeof(char) * strlen(login));
    new_user->password = malloc(sizeof(char) * strlen(password));
    strcpy(new_user->login, login);
    strcpy(new_user->password, password);
    new_user->edit_book = edit_book;
    new_user->edit_student = edit_student;

    if (library->num_users < library->cap_users) {
        library->users[library->num_users] = new_user;
        library->num_users++;
    } else {
        USER **temp = library->users;

        library->users = malloc(sizeof(USER*) * library->cap_users * COEF_MEM);
        for (int i = 0; i < library->cap_users; ++i)
            library->users[i] = temp[i];
        for (int i = library->cap_users; i < library->cap_users * COEF_MEM; ++i)
            library->users[i] = NULL;
        library->cap_users *= COEF_MEM;
        free(temp);
    }
}

void AddBook(LIBRARY *library, int isbn, char *fnauthor, char *title, int quantity, int quantity_in_stock) {
    BOOK *new_book = malloc(sizeof(BOOK));
    new_book->isbn = isbn;
    new_book->quantity = quantity;
    new_book->quantity_in_stock = quantity_in_stock;
    new_book->fnauthor = malloc(sizeof(char) * strlen(fnauthor));
    new_book->title = malloc(sizeof(char) * strlen(title));
    strcpy(new_book->fnauthor, fnauthor);
    strcpy(new_book->title, title);

    for (int i = 0; i < library->num_books; ++i)
        if (library->books[i]->isbn == new_book->isbn) {
            puts("Update book data!");
            new_book->quantity_in_stock = library->books[i]->quantity_in_stock;
            if (new_book->quantity < new_book->quantity_in_stock) {
                puts("Error update: quantity cannot be less than the quantity_in_stock");
                free(new_book);
                return;
            }
            free(library->books[i]);
            library->books[i] = new_book;
            return;
        }

    if (library->num_books < library->cap_books) {
        library->books[library->num_books] = new_book;
        library->num_books++;
    } else {
        BOOK **temp = library->books;

        library->books = malloc(sizeof(BOOK*) * library->cap_books * COEF_MEM);
        for (int i = 0; i < library->cap_books; ++i)
            library->books[i] = temp[i];
        for (int i = library->cap_books; i < library->cap_books * COEF_MEM; ++i)
            library->users[i] = NULL;
        library->cap_books *= COEF_MEM;
        free(temp);
    }
}

void DeleteBook(LIBRARY *library, int isbn) {
    for (int i = 0; i < library->num_books; ++i)
        if (library->books[i]->isbn == isbn) {
            if (library->books[i]->quantity_in_stock == 0) {
                free(library->books[i]);
                library->num_books--;
                for (int j = i; j < library->num_books; ++j)
                    library->books[j] = library->books[j + 1];
                puts("Book deleted!");
                return;
            }
            puts("Error: students have this book!");
            return;
        }
    puts("Book not found!");
}

void AddStudent(LIBRARY *library, int number_gradebook, char *surname, char *name, char *patronymic, char *faculty, char *specialization) {
    STUDENT *new_student = malloc(sizeof(STUDENT));
    new_student->number_gradebook = number_gradebook;
    new_student->surname = malloc(sizeof(char) * strlen(surname));
    strcpy(new_student->surname, surname);
    new_student->name = malloc(sizeof(char) * strlen(name));
    strcpy(new_student->name, name);
    new_student->patronymic = malloc(sizeof(char) * strlen(patronymic));
    strcpy(new_student->patronymic, patronymic);
    new_student->faculty = malloc(sizeof(char) * strlen(faculty));
    strcpy(new_student->faculty, faculty);
    new_student->specialization = malloc(sizeof(char) * strlen(specialization));
    strcpy(new_student->specialization, specialization);
    new_student->num_books = 0;
    new_student->cap_books = INIT_MEM;
    new_student->books_isbn = malloc(sizeof(int) * new_student->cap_books);

    for (int i = 0; i < library->num_studets; ++i)
        if (library->students[i]->number_gradebook == new_student->number_gradebook) {
            puts("Update student data!");
            free(library->students[i]);
            library->students[i] = new_student;
            return;
        }

    if (library->num_studets < library->cap_studets) {
        library->students[library->num_studets] = new_student;
        library->num_studets++;
    } else {
        STUDENT **temp = library->students;

        library->students = malloc(sizeof(STUDENT*) * library->cap_studets * COEF_MEM);
        for (int i = 0; i < library->cap_users; ++i)
            library->students[i] = temp[i];
        for (int i = library->cap_books; i < library->cap_books * COEF_MEM; ++i)
            library->students[i] = NULL;
        library->cap_studets *= COEF_MEM;
        free(temp);
    }
}

void DeleteStudent(LIBRARY *library, int number_gradebook) {
    for (int i = 0; i < library->num_studets; ++i)
        if (library->students[i]->number_gradebook == number_gradebook) {
            if (library->students[i]->num_books == 0) {
                free(library->books[i]);
                library->num_studets--;
                for (int j = i; j < library->num_studets; ++j)
                    library->students[j] = library->students[j + 1];
                puts("Student deleted!");
                return;
            }
            puts("Error: students have books!");
            return;
        }
    puts("Student not found!");
}

void GiveBook(LIBRARY *library, int number_gradebook, int isbn, int show_iss) {
    for (int i = 0; i < library->num_studets; ++i)
        if (library->students[i]->number_gradebook == number_gradebook) {
            for (int j = 0; j < library->num_books; ++j)
                if (library->books[j]->isbn == isbn) {
                    if (library->books[j]->quantity_in_stock < library->books[j]->quantity) {
                        for (int k = 0; k < library->students[i]->num_books; ++k)
                            if (library->students[i]->books_isbn[k] == library->books[j]->isbn) {
                                puts("Error: student already has this book!");
                                return;
                            }


                        if (library->students[i]->num_books < library->students[i]->cap_books) {
                            library->students[i]->books_isbn[library->students[i]->num_books] = isbn;
                            library->students[i]->num_books++;
                        } else {
                            int *isbn_temp = library->students[i]->books_isbn;

                            library->students[i]->books_isbn = malloc(sizeof(int) * library->students[i]->cap_books * COEF_MEM);
                            for (int k = 0; k < library->students[i]->cap_books; ++k)
                                library->students[i]->books_isbn[k] = isbn_temp[k];
                            for (int k = library->cap_books; k < library->cap_books * COEF_MEM; ++k)
                                library->students[k] = NULL;
                            library->students[i]->cap_books *= COEF_MEM;

                            free(isbn_temp);
                        }
                        library->books[j]->quantity_in_stock++;
                        if (show_iss == 1)
                            puts("Book is issued!");
                        return;
                    }
                    printf("Error: all this books (isbn: %d) have been issued!", isbn);
                    return;
                }
            puts("Book not found!");
            return;
        }
    puts("Student not found!");
}

void PickUpBook(LIBRARY *library, int number_gradebook, int isbn) {
    for (int i = 0; i < library->num_studets; ++i)
        if (library->students[i]->number_gradebook == number_gradebook) {
            for (int j = 0; j < library->num_books; ++j)
                if (library->books[j]->isbn == isbn) {
                    int book_pos = -1;
                    for (int k = 0; k < library->students[i]->num_books; ++k)
                        if (library->students[i]->books_isbn[k] == library->books[j]->isbn)
                            book_pos = k;
                    if (book_pos == -1) {
                        puts("Error: student does not have this book!");
                        return;
                    }

                    library->students[i]->num_books--;
                    for (int k = book_pos; k < library->students[i]->num_books; ++k)
                        library->students[i]->books_isbn[k] = library->students[i]->books_isbn[k + 1];

                    library->books[j]->quantity_in_stock--;
                    puts("Book has been returned!");
                    return;
                }
            puts("Book not found!");
            return;
        }
    puts("Student not found!");
}

void PrintLibInfo(LIBRARY *library) {
    puts("Books:");
    for (int i = 0; i < library->num_books; ++i) {
        printf("\tIsbn: %d, Author: %s, Title: %s, Quantity: %d, Quantity in stock: %d\n", library->books[i]->isbn, library->books[i]->fnauthor, library->books[i]->title, library->books[i]->quantity, library->books[i]->quantity_in_stock);
    }
    puts("Students:");
    for (int i = 0; i < library->num_studets; ++i) {
        printf("\tNumber gradebook: %d, Surname: %s, Name: %s, Patronymic: %s, Faculty: %s, Specialization: %s, Num books: %d\n", library->students[i]->number_gradebook, library->students[i]->surname, library->students[i]->name, library->students[i]->patronymic, library->students[i]->faculty, library->students[i]->specialization, library->students[i]->num_books);
        if (library->students[i]->num_books > 0) {
            printf("Books isbn: ");
            for (int j = 0; j < library->students[i]->num_books; ++j)
                printf("%d ", library->students[i]->books_isbn[j]);
            putchar('\n');
        }
    }
    /*puts("Users:");
    for (int i = 0; i < library->num_users; ++i) {
        printf("Login: %s, Password: %s\n", library->users[i]->login, library->users[i]->password);
    }*/
}