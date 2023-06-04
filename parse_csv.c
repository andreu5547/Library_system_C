#include "parse_csv.h"

void strip(char *Str) {
    for (int i = 0; Str[i] != '\0'; ++i) {
        if (Str[i] == '\n') {
            Str[i] = '\0';
            return;
        }
    }
}

int parse_csv_books(char *file_name, LIBRARY *library) {
    FILE *inputFile = fopen(file_name, "r");

    // Проверяем открылся ли
    if (inputFile == NULL) {
        printf("Error opening %s file.", file_name);
        return 1;
    }

    char *keys[MAX_KEYS_SIZE];
    int keycnt = 0;

    char *data[MAX_KEYS_SIZE];
    int datacnt = 0;

    char line[MAX_DATA_SIZE];
    int linecnt = 0;

    char *token;

    int isbn = 0, quantity = 0;
    char author[MAX_DATA_SIZE] = "", title[MAX_DATA_SIZE] = "";
    int ok[4] = {0};

    // Получаем строку с ключами и проверяем, что получили
    char keys_line[MAX_DATA_SIZE];
    if (fgets(keys_line, MAX_DATA_SIZE, inputFile) == NULL) {
        puts("Error read keys from input file");
        fclose(inputFile);
        return 1;
    }
    // Разбиваем ключи по разделителю
    token = strtok(keys_line, DELIMITER);
    while (token != NULL) {
        keys[keycnt] = strdup(token);
        strip(keys[keycnt]);
        keycnt++;
        token = strtok(NULL, DELIMITER);
    }

    while (fgets(line, MAX_DATA_SIZE, inputFile) != NULL) {
        token = strtok(line, DELIMITER);
        while (token != NULL) {
            data[datacnt] = strdup(token);
            datacnt++;
            token = strtok(NULL, DELIMITER);
        }
        for (int i = 0; i < 4; ++i) ok[i] = 0;
        for (int i = 0; i < keycnt; ++i) {
            strip(data[i]);
            if (strcmp(keys[i], "isbn") == 0) {
                isbn = atoi(data[i]);
                ok[0] = 1;
            }
            else if (strcmp(keys[i], "fnauthor") == 0) {
                strcpy(author, data[i]);
                ok[1] = 1;
            }
            else if (strcmp(keys[i], "title") == 0) {
                strcpy(title, data[i]);
                ok[2] = 1;
            }
            else if (strcmp(keys[i], "quantity") == 0) {
                quantity = atoi(data[i]);
                ok[3] = 1;
            }
        }
        if (ok[0] == 1 && ok[1] == 1 && ok[2] == 1 && ok[3] == 1) {
            AddBook(library, isbn, author, title, quantity, 0);
        }
        else printf("Error in books_file in string %d!", linecnt);
        linecnt++;
        datacnt = 0;
    }

    //Закрываем файл && очищаем память
    fclose(inputFile);
    for (int i = 0; i < keycnt; i++) {
        free(keys[i]);
        free(data[i]);
    }
    puts("Books imported.");

    return 0;
}


int parse_csv_students(char *file_name, LIBRARY *library) {
    // Открываем файл, переданный пользователем
    FILE *inputFile = fopen(file_name, "r");

    // Проверяем открылся ли
    if (inputFile == NULL) {
        printf("Error opening %s file.", file_name);
        return 1;
    }

    char *keys[MAX_KEYS_SIZE];
    int keycnt = 0;

    char *data[MAX_KEYS_SIZE];
    int datacnt = 0;

    char line[MAX_DATA_SIZE];
    int linecnt = 0;

    char *token;

    int number_gradebook;
    char surname[MAX_DATA_SIZE] = "", name[MAX_DATA_SIZE] = "", patronymic[MAX_DATA_SIZE] = "", faculty[MAX_DATA_SIZE] = "", specialization[MAX_DATA_SIZE] = "";
    int ok[6] = {0};

    // Получаем строку с ключами и проверяем, что получили
    char keys_line[MAX_DATA_SIZE];
    if (fgets(keys_line, MAX_DATA_SIZE, inputFile) == NULL) {
        puts("Error read keys from input file");
        fclose(inputFile);
        return 1;
    }
    // Разбиваем ключи по разделителю
    token = strtok(keys_line, DELIMITER);
    while (token != NULL) {
        keys[keycnt] = strdup(token);
        strip(keys[keycnt]);
        keycnt++;
        token = strtok(NULL, DELIMITER);
    }

    while (fgets(line, MAX_DATA_SIZE, inputFile) != NULL) {
        token = strtok(line, DELIMITER);
        while (token != NULL) {
            data[datacnt] = strdup(token);
            datacnt++;
            token = strtok(NULL, DELIMITER);
        }
        for (int i = 0; i < 6; ++i) ok[i] = 0;
        for (int i = 0; i < keycnt; ++i) {
            strip(data[i]);
            if (strcmp(keys[i], "number_gradebook") == 0) {
                number_gradebook = atoi(data[i]);
                ok[0] = 1;
            }
            else if (strcmp(keys[i], "surname") == 0) {
                strcpy(surname, data[i]);
                ok[1] = 1;
            }
            else if (strcmp(keys[i], "name") == 0) {
                strcpy(name, data[i]);
                ok[2] = 1;
            }
            else if (strcmp(keys[i], "patronymic") == 0) {
                strcpy(patronymic, data[i]);
                ok[3] = 1;
            }
            else if (strcmp(keys[i], "faculty") == 0) {
                strcpy(faculty, data[i]);
                ok[4] = 1;
            }
            else if (strcmp(keys[i], "specialization") == 0) {
                strcpy(specialization, data[i]);
                ok[5] = 1;
            }
        }
        if (ok[0] == 1 && ok[1] == 1 && ok[2] == 1 && ok[3] == 1 && ok[4] == 1 && ok[5] == 1) {
            AddStudent(library, number_gradebook, surname, name, patronymic, faculty, specialization);
        }
        else printf("Error in students_file in string %d!", linecnt);
        linecnt++;
        datacnt = 0;
    }

    //Закрываем файл && очищаем память
    fclose(inputFile);
    for (int i = 0; i < keycnt; i++) {
        free(keys[i]);
        free(data[i]);
    }
    puts("Students imported.");

    return 0;
}

int parse_csv_users(char *file_name, LIBRARY *library) {
    // Открываем файл, переданный пользователем
    FILE *inputFile = fopen(file_name, "r");

    // Проверяем открылся ли
    if (inputFile == NULL) {
        printf("Error opening %s file.", file_name);
        return 1;
    }

    char *keys[MAX_KEYS_SIZE];
    int keycnt = 0;

    char *data[MAX_KEYS_SIZE];
    int datacnt = 0;

    char line[MAX_DATA_SIZE];
    int linecnt = 0;

    char *token;

    int edit_student = 0, edit_book = 0;
    char login[MAX_DATA_SIZE] = "", password[MAX_DATA_SIZE] = "";
    int ok[4] = {0};

    // Получаем строку с ключами и проверяем, что получили
    char keys_line[MAX_DATA_SIZE];
    if (fgets(keys_line, MAX_DATA_SIZE, inputFile) == NULL) {
        puts("Error read keys from input file");
        fclose(inputFile);
        return 1;
    }
    // Разбиваем ключи по разделителю
    token = strtok(keys_line, DELIMITER);
    while (token != NULL) {
        keys[keycnt] = strdup(token);
        strip(keys[keycnt]);
        keycnt++;
        token = strtok(NULL, DELIMITER);
    }

    while (fgets(line, MAX_DATA_SIZE, inputFile) != NULL) {
        token = strtok(line, DELIMITER);
        while (token != NULL) {
            data[datacnt] = strdup(token);
            datacnt++;
            token = strtok(NULL, DELIMITER);
        }
        for (int i = 0; i < 4; ++i) ok[i] = 0;
        for (int i = 0; i < keycnt; ++i) {
            strip(data[i]);
            if (strcmp(keys[i], "login") == 0) {
                strcpy(login, data[i]);
                ok[0] = 1;
            }
            else if (strcmp(keys[i], "password") == 0) {
                strcpy(password, data[i]);
                ok[1] = 1;
            }
            else if (strcmp(keys[i], "edit_student") == 0) {
                edit_student = atoi(data[i]);
                ok[2] = 1;
            }
            else if (strcmp(keys[i], "edit_book") == 0) {
                edit_book = atoi(data[i]);
                ok[3] = 1;
            }
        }
        if (ok[0] == 1 && ok[1] == 1 && ok[2] == 1 && ok[3] == 1) {
            AddUser(library, login, password, edit_student, edit_book);
        }
        else printf("Error in users_file in string %d!", linecnt);
        linecnt++;
        datacnt = 0;
    }

    //Закрываем файл && очищаем память
    fclose(inputFile);
    for (int i = 0; i < keycnt; i++) {
        free(keys[i]);
        free(data[i]);
    }
    puts("Users imported.");

    return 0;
}

int parse_csv_students_books(char *file_name, LIBRARY *library) {
    // Открываем файл, переданный пользователем
    FILE *inputFile = fopen(file_name, "r");

    // Проверяем открылся ли
    if (inputFile == NULL) {
        printf("Error opening %s file.", file_name);
        return 1;
    }

    char *keys[MAX_KEYS_SIZE];
    int keycnt = 0;

    char *data[MAX_KEYS_SIZE];
    int datacnt = 0;

    char line[MAX_DATA_SIZE];
    int linecnt = 0;

    char *token;

    int number_gradebook = 0, isbn = 0;
    int ok[2] = {0};

    // Получаем строку с ключами и проверяем, что получили
    char keys_line[MAX_DATA_SIZE];
    if (fgets(keys_line, MAX_DATA_SIZE, inputFile) == NULL) {
        puts("Error read keys from input file");
        fclose(inputFile);
        return 1;
    }
    // Разбиваем ключи по разделителю
    token = strtok(keys_line, DELIMITER);
    while (token != NULL) {
        keys[keycnt] = strdup(token);
        strip(keys[keycnt]);
        keycnt++;
        token = strtok(NULL, DELIMITER);
    }

    while (fgets(line, MAX_DATA_SIZE, inputFile) != NULL) {
        token = strtok(line, DELIMITER);
        while (token != NULL) {
            data[datacnt] = strdup(token);
            datacnt++;
            token = strtok(NULL, DELIMITER);
        }
        for (int i = 0; i < 2; ++i) ok[i] = 0;
        for (int i = 0; i < keycnt; ++i) {
            strip(data[i]);
            if (strcmp(keys[i], "number_gradebook") == 0) {
                number_gradebook = atoi(data[i]);
                ok[0] = 1;
            }
            else if (strcmp(keys[i], "isbn") == 0) {
                isbn = atoi(data[i]);
                ok[1] = 1;
            }
        }
        if (ok[0] == 1 && ok[1] == 1) {
            GiveBook(library, number_gradebook, isbn, 0);
        }
        else printf("Error in students_books_file in string %d!", linecnt);
        linecnt++;
        datacnt = 0;
    }

    //Закрываем файл && очищаем память
    fclose(inputFile);
    for (int i = 0; i < keycnt ; i++) {
        free(keys[i]);
        free(data[i]);
    }
    puts("Books of students students imported.");

    return 0;
}