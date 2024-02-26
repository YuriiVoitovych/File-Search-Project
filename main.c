// Developed by Yuriy Voytovych, Ukraine, 2024

#include <stdio.h>
#include <pthread.h>
#include "file_search.h"

int main(int argc, char *argv[])
{
    // Check if the correct number of arguments is provided
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename.txt>\n", argv[0]);
        return 1;
    }

    // Extract the filename from the command line arguments
    char *filename = argv[1];

    // Initialize arrays for threads and running thread flags
    pthread_t threads[MAX_THREADS] = {0};
    int running_threads[MAX_THREADS] = {1}; // At least one thread is running

    // Start the search from the root directory ("/" or "C:/" in Windows)
    pthread_t tid;
    SearchArgs args = {
        .root_dir = "C:/",
        .filename = filename,
        .threads = threads,
        .running_threads = running_threads,
        .found_file_path = NULL};
    pthread_create(&tid, NULL, search_directory, (void *)&args);
    threads[0] = tid;

    // Wait for the search to complete
    pthread_join(tid, NULL);

    return 0;
}
