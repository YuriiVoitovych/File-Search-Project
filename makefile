# Specify the compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -pthread -static

# Source files
SOURCES = file_search.c main.c

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Static library name
LIBRARY = libsearch.a

# Executable name
EXECUTABLE = main.exe

# Default target (build the executable)
all: $(EXECUTABLE) message clean_objects

# Build the static library
$(LIBRARY): $(OBJECTS)
	ar rcs $@ $^

# Link object files to create the executable
$(EXECUTABLE): $(LIBRARY) main.o
	$(CC) $(CFLAGS) -o $@ main.o -L. -lsearch

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(EXECUTABLE) $(LIBRARY)

# Clean up object files
clean_objects:
	@if exist file_search.o del file_search.o
	@if exist main.o del main.o

# Display a message for the user
message:
	@echo "To search for a file, type > .\$(EXECUTABLE) \"The name of the file you want to search for.\""
