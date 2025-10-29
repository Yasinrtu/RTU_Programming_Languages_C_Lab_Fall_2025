
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char   name[64];
    int    age;
    double gpa;
} Student;

int save_student(const char *path, const Student *s) {
    if (path == NULL || s == NULL) return -1;
    FILE *fp = fopen(path, "w");
    if (fp == NULL) {
        perror("save_student: fopen");
        return -1;
    }
    /* Simple text format: name age gpa (name must not contain spaces) */
    if (fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa) < 0) {
        perror("save_student: fprintf");
        fclose(fp);
        return -1;
    }
    if (fclose(fp) == EOF) {
        perror("save_student: fclose");
        return -1;
    }
    return 0;
}

int load_student(const char *path, Student *out) {
    if (path == NULL || out == NULL) return -1;
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        perror("load_student: fopen");
        return -1;
    }
    /* Read back the same format */
    int matched = fscanf(fp, "%63s %d %lf", out->name, &out->age, &out->gpa);
    if (matched != 3) {
        fprintf(stderr, "load_student: invalid file format\n");
        fclose(fp);
        return -1;
    }
    if (fclose(fp) == EOF) {
        perror("load_student: fclose");
        return -1;
    }
    return 0;
}

int main(void) {
    const char *file = "student.txt";

    Student s = { "Alice", 21, 3.75 };
    printf("Saving student to file...\n");
    if (save_student(file, &s) != 0) {
        return EXIT_FAILURE;
    }

    printf("Loading student from file...\n");
    Student loaded;
    if (load_student(file, &loaded) != 0) {
        return EXIT_FAILURE;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);
    return EXIT_SUCCESS;
}
