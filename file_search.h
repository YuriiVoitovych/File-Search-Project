// Developed by Yuriy Voytovych, Ukraine, 2024

#ifndef FILE_SEARCH_H
#define FILE_SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <pthread.h>

#define MAX_THREADS 8
#define FILENAME_MAX_LEN 256

// Structure for passing arguments to search threads
typedef struct
{
    char *root_dir;        // Root directory for the search
    char *filename;        // Filename to search for
    pthread_t *threads;    // Array of thread IDs
    int *running_threads;  // Array indicating whether threads are running
    char *found_file_path; // Path to the found file (not used in the current implementation)
} SearchArgs;

// Function declarations
void *search_directory(void *args);

#endif
