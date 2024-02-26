# File Search Project

## Description
This project is a file search utility implemented in C that allows users to search for a specified file in the directories
of a file system. The program uses multithreading to improve performance by searching multiple directories simultaneously.
It recursively traverses directories starting from the root directory ("/" in Unix-like systems or "C:/" in Windows) to find the file.

## Features
- Recursively searches directories for a specified file
- Uses multiple threads for parallel searching
- Displays the full path of the found file

## How to Use
1. **Compile the Project:**
   - Use the provided Makefile to compile the project. Run `make` command in the terminal.

2. **Run the Executable:**
   - Execute the compiled executable with the name of the file you want to search for as an argument. For example:
     ```
     ./main.exe filename.txt
     ```

3. **View the Results:**
   - The program will display the full path to the found file if it exists in any of the searched directories.

## Requirements
- GCC compiler
- pthread library for multithreading support
- dirent.h library for directory operations
- sys/stat.h library for file status information

## Project Structure
- `file_search.c`: Contains the implementation of the file search algorithm.
- `file_search.h`: Header file containing function declarations and structures.
- `main.c`: Entry point of the program with the `main` function.
- `Makefile`: Makefile for building the project.
- `README.md`: This file, containing information about the project.

## Author
Developed by Yuriy Voytovych, Ukraine, 2024
