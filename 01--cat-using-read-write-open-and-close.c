#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      // for open()
#include <unistd.h>     // for read(), write(), close()
#include <errno.h>      // for errno
#include <string.h>     // for strerror()

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int fd;
    ssize_t bytesRead;
    char buffer[BUFFER_SIZE];

    if (argc != 2) {
        write(STDERR_FILENO, "Usage: ./cat <filename>\n", 25);
        exit(EXIT_FAILURE);
    }

    // Open the file for reading
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read from the file and write to stdout
    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buffer, bytesRead) != bytesRead) {
            perror("Error writing to stdout");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }

    if (bytesRead < 0) {
        perror("Error reading file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Close the file
    if (close(fd) < 0) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }

    return 0;
}
