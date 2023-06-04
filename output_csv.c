#include "output_csv.h"

int out_csv_books(char *file_name, LIBRARY *library) {
    // Открываем файл, переданный пользователем
    FILE *outputFile = fopen(file_name, "w");

    // Проверяем открылся ли
    if (outputFile == NULL) {
        printf("Error opening %s file.", file_name);
        return 1;
    }

    fprintf(outputFile, "isbn%sfnauthor%stitle%squantity\n", DELIMITER, DELIMITER, DELIMITER);

    for (int i = 0; i < library->num_books; ++i) {
        fprintf(outputFile, "%d%s%s%s%s%s%d\n", library->books[i]->isbn, DELIMITER, library->books[i]->fnauthor,
                DELIMITER,
                library->books[i]->title, DELIMITER, library->books[i]->quantity);
    }
    fclose(outputFile);
    return 0;
}

int out_csv_students(char *file_name, LIBRARY *library) {
    // Открываем файл, переданный пользователем
    FILE *outputFile = fopen(file_name, "w");

    // Проверяем открылся ли
    if (outputFile == NULL) {
        printf("Error opening %s file.", file_name);
        return 1;
    }

    fprintf(outputFile, "number_gradebook%ssurname%sname%spatronymic%sfaculty%sspecialization\n", DELIMITER, DELIMITER,
            DELIMITER, DELIMITER, DELIMITER);

    for (int i = 0; i < library->num_studets; ++i) {
        fprintf(outputFile, "%d%s%s%s%s%s%s%s%s%s%s\n", library->students[i]->number_gradebook, DELIMITER,
                library->students[i]->surname, DELIMITER, library->students[i]->name, DELIMITER,
                library->students[i]->patronymic, DELIMITER,
                library->students[i]->faculty, DELIMITER, library->students[i]->specialization);
    }
    fclose(outputFile);
    return 0;
}

int out_csv_users(char *file_name, LIBRARY *library) {
    // Открываем файл, переданный пользователем
    FILE *outputFile = fopen(file_name, "w");

    // Проверяем открылся ли
    if (outputFile == NULL) {
        printf("Error opening %s file.", file_name);
        return 1;
    }

    fprintf(outputFile, "login%spassword%sedit_student%sedit_book\n", DELIMITER, DELIMITER, DELIMITER);

    for (int i = 0; i < library->num_users; ++i) {
        fprintf(outputFile, "%s%s%s%s%d%s%d\n", library->users[i]->login, DELIMITER, library->users[i]->password, DELIMITER,
                library->users[i]->edit_student, DELIMITER, library->users[i]->edit_book);
    }
    fclose(outputFile);
    return 0;
}

int out_csv_students_books(char *file_name, LIBRARY *library) {
    // Открываем файл, переданный пользователем
    FILE *outputFile = fopen(file_name, "w");

    // Проверяем открылся ли
    if (outputFile == NULL) {
        printf("Error opening %s file.", file_name);
        return 1;
    }

    fprintf(outputFile, "number_gradebook%sisbn\n", DELIMITER);

    for (int i = 0; i < library->num_studets; ++i) {
        for (int j = 0; j < library->students[i]->num_books; ++j) {
            fprintf(outputFile, "%d%s%d\n", library->students[i]->number_gradebook, DELIMITER, library->students[i]->books_isbn[j]);
        }
    }
    fclose(outputFile);
    return 0;
}
