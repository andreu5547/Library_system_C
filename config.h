#ifndef LIBSYSTEM_CONFIG_H
#define LIBSYSTEM_CONFIG_H

// Файлы для хранения информации о книгах/студентах/пользователях/выданных_книгах
#define books_file_name "books.csv"
#define students_file_name "students.csv"
#define users_file_name "users.csv"
#define students_books_file_name "student_books.csv"
// Константы определяющие максимальный размер строк и ключей в csv файлах
#define MAX_DATA_SIZE 1024
#define MAX_KEYS_SIZE 128
#define DELIMITER ";" // Разделитель, используемый с csv файлах
// Коэффициент увеличения памяти и память выделяющаяся по умолчанию
#define COEF_MEM 2
#define INIT_MEM 10

#endif //LIBSYSTEM_CONFIG_H
