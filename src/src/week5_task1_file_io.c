
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    const char *filename = "data.txt";

    /* --- Write phase --- */
    printf("Writing lines to %s...\n", filename);
    FILE *fpw = fopen(filename, "w");
    if (fpw == NULL) {
        perror("Error opening file for writing");
        return EXIT_FAILURE;
    }

    /* You can optionally read from user; here we keep short sample lines */
    if (fprintf(fpw, "Hello, file I/O in C!\n") < 0 ||
        fprintf(fpw, "This is another line.\n") < 0) {
        perror("Error writing to file");
        fclose(fpw);
        return EXIT_FAILURE;
    }
    if (fclose(fpw) == EOF) {
        perror("Error closing file after writing");
        return EXIT_FAILURE;
    }

    /* --- Read phase --- */
    printf("Reading contents:\n");
    FILE *fpr = fopen(filename, "r");
    if (fpr == NULL) {
        perror("Error opening file for reading");
        return EXIT_FAILURE;
    }

    char buffer[256];
    while (fgets(buffer, (int)sizeof buffer, fpr) != NULL) {
        fputs(buffer, stdout);
    }

    if (ferror(fpr)) {
        perror("Error while reading file");
        fclose(fpr);
        return EXIT_FAILURE;
    }

    if (fclose(fpr) == EOF) {
        perror("Error closing file after reading");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
