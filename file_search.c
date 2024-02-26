// Developed by Yuriy Voytovych, Ukraine, 2024

#include "file_search.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

// Function to search for files in a directory recursively
void *search_directory(void *args)
{
    // Cast the arguments to the SearchArgs structure
    SearchArgs *search_args = (SearchArgs *)args;
    char full_path[FILENAME_MAX_LEN];

    // Open the directory for searching
    DIR *dir = opendir(search_args->root_dir);
    if (dir == NULL)
    {
        perror("opendir");
        return NULL;
    }

    // Print the current directory being searched
    printf("Searching in directory: %s\n", search_args->root_dir);

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        // Check if the entry is a directory
        if (entry->d_name[0] == '.' || entry->d_name[0] == '\0')
        {
            continue; // Skip current and parent directory entries
        }

        // Construct the full path of the entry
        snprintf(full_path, FILENAME_MAX_LEN, "%s/%s", search_args->root_dir, entry->d_name);

        // Check if the entry is a directory
        struct stat statbuf;
        if (stat(full_path, &statbuf) != -1 && S_ISDIR(statbuf.st_mode))
        {
            // Recursively search subdirectories
            pthread_t tid;
            search_args->running_threads[0] = 1; // Set flag indicating thread is running
            pthread_create(&tid, NULL, search_directory, (void *)(&(SearchArgs){.root_dir = strdup(full_path), .filename = search_args->filename, .threads = search_args->threads, .running_threads = search_args->running_threads, .found_file_path = search_args->found_file_path}));
            pthread_join(tid, NULL); // Wait for the subdirectory search to complete
        }
        else
        {
            // Found a file
            char *filename_without_extension = strdup(entry->d_name);
            char *dot = strrchr(filename_without_extension, '.');
            if (dot != NULL)
            {
                *dot = '\0'; // Remove the extension
            }

            // Check if the filename matches the search criteria
            if (strstr(filename_without_extension, search_args->filename) != NULL)
            {
                // Print the full path to the found file
                printf("Found file: %s\n", full_path);

                // Print the path to the found file
                printf("Path: %s\n", full_path);

                // Notify other threads to stop searching
                search_args->running_threads[0] = 0; // Set flag indicating search should stop
            }
            free(filename_without_extension);
        }

        // Check if search should be stopped
        if (search_args->running_threads[0] == 0)
        {
            break; // Stop searching if requested
        }
    }

    // Close the directory
    closedir(dir);
    return NULL;
}