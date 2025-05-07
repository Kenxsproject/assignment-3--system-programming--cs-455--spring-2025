#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[]) {
    FILE *file1, *file2;
    char line1[MAX_LINE_LENGTH], line2[MAX_LINE_LENGTH];

    if (argc != 3) {
        fprintf(stderr, "Usage: ./compare file1.txt file2.txt\n");
        return EXIT_FAILURE;
    }

    file1 = fopen(argv[1], "r");
    file2 = fopen(argv[2], "r");

    if (!file1 || !file2) {
        perror("Error opening one of the files");
        return EXIT_FAILURE;
    }

    while (fgets(line1, MAX_LINE_LENGTH, file1) && fgets(line2, MAX_LINE_LENGTH, file2)) {
        if (strcmp(line1, line2) != 0) {
            printf("File1: %s", line1);
            printf("File2: %s", line2);
            fclose(file1);
            fclose(file2);
            return EXIT_SUCCESS;
        }
    }

    // Check for one file having extra lines
    if (fgets(line1, MAX_LINE_LENGTH, file1)) {
        printf("File1: %s", line1);
        printf("File2: (no line)\n");
    } else if (fgets(line2, MAX_LINE_LENGTH, file2)) {
        printf("File1: (no line)\n");
        printf("File2: %s", line2);
    }

    fclose(file1);
    fclose(file2);
    return EXIT_SUCCESS;
}
