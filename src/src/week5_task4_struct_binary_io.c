
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char   name[64];
    int    age;
    double gpa;
} Student;

int main(void) {
    const char *binfile = "student.bin";

    Student s = { "Alice", 21, 3.75 };

    printf("Saving student in binary format...\n");
    FILE *fpw = fopen(binfile, "wb");
    if (fpw == NULL) {
        perror("fopen write");
        return EXIT_FAILURE;
    }
    size_t w = fwrite(&s, sizeof(Student), 1, fpw);
    if (w != 1) {
        perror("fwrite");
        fclose(fpw);
        return EXIT_FAILURE;
    }
    if (fclose(fpw) == EOF) {
        perror("fclose write");
        return EXIT_FAILURE;
    }

    printf("Loading student from binary file...\n");
    FILE *fpr = fopen(binfile, "rb");
    if (fpr == NULL) {
        perror("fopen read");
        return EXIT_FAILURE;
    }
    Student loaded;
    size_t r = fread(&loaded, sizeof(Student), 1, fpr);
    if (r != 1) {
        perror("fread");
        fclose(fpr);
        return EXIT_FAILURE;
    }
    if (fclose(fpr) == EOF) {
        perror("fclose read");
        return EXIT_FAILURE;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);

    /* Optional: show binary file size */
    long size = 0L;
    FILE *fpsz = fopen(binfile, "rb");
    if (fpsz) {
        if (fseek(fpsz, 0, SEEK_END) == 0) {
            size = ftell(fpsz);
        }
        fclose(fpsz);
    }
    if (size > 0) {
        printf("Binary file size: %ld bytes\n", size);
    }

    return EXIT_SUCCESS;
}
