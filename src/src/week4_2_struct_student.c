#include <stdio.h>
#include <string.h>

// Define struct Student
struct Student {
    char name[50];
    int id;
    float grade;
};

int main() {
    struct Student s1, s2;

    // Assign values (can be from user input or manual)
    strcpy(s1.name, "Alice Johnson");
    s1.id = 1001;
    s1.grade = 9.1;

    strcpy(s2.name, "Bob Smith");
    s2.id = 1002;
    s2.grade = 8.7;

    // Print student information
    printf("Student 1: %s, ID: %d, Grade: %.1f\n", s1.name, s1.id, s1.grade);
    printf("Student 2: %s, ID: %d, Grade: %.1f\n", s2.name, s2.id, s2.grade);

    return 0;
}
