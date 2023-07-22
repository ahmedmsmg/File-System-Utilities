#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFSIZE 1024
// Function to print the last 'n' lines of a file
void print_last_lines(const char *filename, int n) {
    // Open the file read-only
    int fd = open(filename, O_RDONLY);
    if (fd == -1) { // If open fails
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFSIZE];
    off_t file_offset = 0;
    int total_lines = 0;

    // Loop until 'n' lines are found
    while (total_lines <= n) {
        // Move the file offset back by one each time
        file_offset--;
        if(lseek(fd, file_offset, SEEK_END) == (off_t)-1) {
            lseek(fd, 0, SEEK_SET); //Seek to start of file
            break;
        }

        // Read a character from the file
        if (read(fd, buffer, 1) != 1) { // If read fails
            perror("read");
            exit(EXIT_FAILURE);
        }

        // If the character is a newline, increment the line count
        if (buffer[0] == '\n') {
            total_lines++;
        }

    }
    printf("These are the last %d lines of %s :\n", n, filename);
     // Print out the last 'n' lines
    while (read(fd, buffer, 1) == 1) {
        write(STDOUT_FILENO, buffer, 1);
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    // Check the command line arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s num filename\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Get the number of lines and filename from the command line arguments
    int n = atoi(argv[1]);
    const char *filename = argv[2];

    // Print the last 'n' lines of the file
    print_last_lines(filename, n);
    printf("\n");
    return 0;
}
