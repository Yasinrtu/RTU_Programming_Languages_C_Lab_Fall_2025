
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 1000
#define NAME_MAX_LEN 64
#define LINE_MAX_LEN 256
#define DATA_FILE "students.txt"

typedef struct {
    int    id;
    char   name[NAME_MAX_LEN];
    double gpa;
} Student;

typedef struct {
    Student arr[MAX_STUDENTS];
    size_t  count;
} StudentList;

/* --- Prototypes --- */
void trim_newline(char *s);
int  load_students(const char *path, StudentList *list);
int  save_students(const char *path, const StudentList *list);
int  add_student(StudentList *list, int id, const char *name, double gpa);
void list_students(const StudentList *list);
int  read_int(const char *prompt);
double read_double(const char *prompt);
void read_token(const char *prompt, char *out, size_t outsz);

int main(void) {
    StudentList list = { .count = 0 };

    /* Load existing data (gracefully handle empty/missing file) */
    (void)load_students(DATA_FILE, &list);

    for (;;) {
        printf("\n=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and Exit\n");
        printf("Select an option: ");

        int option = 0;
        if (scanf("%d", &option) != 1) {
            /* Clear invalid input */
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) { /* discard */ }
            puts("Invalid input. Try again.");
            continue;
        }
        /* Consume trailing newline */
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) { /* discard */ }

        if (option == 1) {
            list_students(&list);
        } else if (option == 2) {
            int    id   = read_int("Enter ID: ");
            char   name[NAME_MAX_LEN];
            read_token("Enter name (no spaces): ", name, sizeof name);
            double gpa  = read_double("Enter GPA: ");

            if (add_student(&list, id, name, gpa) == 0) {
                puts("Student added successfully!");
            } else {
                puts("Failed to add student (list full or duplicate ID).");
            }
        } else if (option == 3) {
            if (save_students(DATA_FILE, &list) == 0) {
                puts("Data saved. Goodbye!");
                break;
            } else {
                puts("Error saving data. Exiting anyway.");
                break;
            }
        } else {
            puts("Unknown option. Try 1-3.");
        }
    }

    return EXIT_SUCCESS;
}

/* --- Implementations --- */

void trim_newline(char *s) {
    if (!s) return;
    size_t n = strlen(s);
    if (n > 0 && (s[n-1] == '\n' || s[n-1] == '\r')) s[n-1] = '\0';
}

int load_students(const char *path, StudentList *list) {
    if (path == NULL || list == NULL) return -1;
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        /* No file yet is fine — treat as empty */
        return 0;
    }

    char line[LINE_MAX_LEN];
    size_t loaded = 0;

    while (fgets(line, (int)sizeof line, fp) != NULL) {
        if (loaded >= MAX_STUDENTS) {
            fprintf(stderr, "load_students: reached MAX_STUDENTS (%d)\n", MAX_STUDENTS);
            break;
        }
        /* Format: id name gpa */
        Student s;
        s.name[0] = '\0';
        int matched = 0;
        matched = sscanf(line, "%d %63s %lf", &s.id, s.name, &s.gpa);
        if (matched == 3) {
            list->arr[loaded++] = s;
        } else {
            /* Skip malformed line gracefully */
            continue;
        }
    }

    if (ferror(fp)) {
        perror("load_students: read error");
        fclose(fp);
        return -1;
    }
    if (fclose(fp) == EOF) {
        perror("load_students: fclose");
        return -1;
    }

    list->count = loaded;
    return 0;
}

int save_students(const char *path, const StudentList *list) {
    if (path == NULL || list == NULL) return -1;
    FILE *fp = fopen(path, "w");
    if (fp == NULL) {
        perror("save_students: fopen");
        return -1;
    }

    for (size_t i = 0; i < list->count; ++i) {
        const Student *s = &list->arr[i];
        if (fprintf(fp, "%d %s %.2f\n", s->id, s->name, s->gpa) < 0) {
            perror("save_students: fprintf");
            fclose(fp);
            return -1;
        }
    }

    if (fclose(fp) == EOF) {
        perror("save_students: fclose");
        return -1;
    }
    return 0;
}

int add_student(StudentList *list, int id, const char *name, double gpa) {
    if (list == NULL || name == NULL) return -1;
    if (list->count >= MAX_STUDENTS) return -1;

    /* Prevent duplicate IDs */
    for (size_t i = 0; i < list->count; ++i) {
        if (list->arr[i].id == id) {
            fprintf(stderr, "add_student: duplicate ID %d\n", id);
            return -1;
        }
    }

    Student s;
    s.id = id;
    /* Ensure name fits and is non-empty */
    if (snprintf(s.name, (int)sizeof s.name, "%s", name) <= 0) return -1;
    s.name[NAME_MAX_LEN - 1] = '\0';
    s.gpa = gpa;

    list->arr[list->count++] = s;
    return 0;
}

void list_students(const StudentList *list) {
    if (list == NULL) return;
    if (list->count == 0U) {
        puts("No students found.");
        return;
    }
    printf("%-6s %-20s %-6s\n", "ID", "Name", "GPA");
    for (size_t i = 0; i < list->count; ++i) {
        printf("%-6d %-20s %-6.2f\n",
               list->arr[i].id, list->arr[i].name, list->arr[i].gpa);
    }
}

/* Simple input helpers (robust against stray newlines) */
int read_int(const char *prompt) {
    for (;;) {
        printf("%s", prompt);
        char line[64];
        if (!fgets(line, (int)sizeof line, stdin)) return 0;
        int v;
        if (sscanf(line, "%d", &v) == 1) return v;
        puts("Please enter an integer value.");
    }
}

double read_double(const char *prompt) {
    for (;;) {
        printf("%s", prompt);
        char line[64];
        if (!fgets(line, (int)sizeof line, stdin)) return 0.0;
        double v;
        if (sscanf(line, "%lf", &v) == 1) return v;
        puts("Please enter a numeric value.");
    }
}

void read_token(const char *prompt, char *out, size_t outsz) {
    for (;;) {
        printf("%s", prompt);
        char line[128];
        if (!fgets(line, (int)sizeof line, stdin)) {
            if (outsz > 0) out[0] = '\0';
            return;
        }
        trim_newline(line);
        if (strchr(line, ' ') != NULL || line[0] == '\0') {
            puts("Name must be a single word (no spaces). Try again.");
            continue;
        }
        snprintf(out, (int)outsz, "%s", line);
        out[outsz - 1] = '\0';
        return;
    }
}
