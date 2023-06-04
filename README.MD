# A library system based on the C language
## Project Description
The project is a C-based system designed for storing information about books and students in a library. It provides functionalities for adding, modifying, and deleting students and books, as well as issuing and returning books. The system also allows for displaying information about both books and students. Additionally, it incorporates a user authentication system and supports the storage and import of data in CSV files.

The main features of the system include:

* Student Management: The system enables the addition, modification, and deletion of student records. It allows administrators to store relevant information about students, such as their names, IDs, contact details, and other details.

* Book Management: The system supports the management of books in the library. Administrators can add, modify, or remove book records, including information like the book title, author, and availability status.

* Book Issuing and Returning: The system facilitates the process of issuing books to students and their subsequent return. It keeps track of the books borrowed by each student.

* Information Retrieval: The system offers the ability to retrieve and display information about both books and students. Student information, including borrowed books, can be accessed and displayed.

* User Authentication: The system incorporates a user authentication mechanism to ensure secure access. It provides different levels of access privileges, such as administrators and library staff, with appropriate authorization to perform specific tasks within the system.

* Data Storage and Import: The system supports the storage of data in CSV files. This functionality enables administrators to save the library's information and import it back into the system when needed. It ensures data persistence and allows for easy data exchange with other applications.

Overall, this C-based library management system provides a comprehensive solution for managing student and book records, issuing and returning books, and facilitating information retrieval. Its user authentication system and support for CSV file storage make it a robust and flexible tool for library administration.

## Dependencies

To build the project, you need to install the following dependencies:
* CMake
* C Compiler (e.g. GCC)

## Cloning the Repository

Before starting the build process, you need to clone the repository to your local computer

``` git clone https://github.com/andreu5547/Library_system_C.git ```

## Building the Project with CMake
1. Navigate to the root directory of the project:
   ```cd Library_system_C```
2. Create a "build" directory:
   ```mkdir build```
3. Navigate to the "build" directory:
   ```cd build```
4. Generate the project files with CMake:
   ```cmake ..```
5. Build the project:
   ```cmake --build .```
6. Profit