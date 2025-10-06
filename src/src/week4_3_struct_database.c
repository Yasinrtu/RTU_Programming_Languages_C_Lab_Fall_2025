#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Reuse struct definition
struct Student {
    char name[50];
    int id;
    float grade;
};

int main() {
    int n, i;
    struct Student *students;

    printf("Enter number of students: ");
    scanf("%d", &n);

    // Allocate memory for n students
    students = (struct Student *)malloc(n * sizeof(struct Student));
    if (students == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Read student data
    for (i = 0; i < n; i++) {
        printf("Enter data for student %d: ", i + 1);
        scanf("%s %d %f", students[i].name, &students[i].id, &students[i].grade);
    }

    // Print all records
    printf("\n%-6s %-12s %-6s\n", "ID", "Name", "Grade");
    for (i = 0; i < n; i++) {
        printf("%-6d %-12s %.1f\n", students[i].id, students[i].name, students[i].grade);
    }

    // Free memory
    free(students);
    return 0;
}
