#include <stdio.h>

// custom strlen
int my_strlen(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// custom strcpy
void my_strcpy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0'; // add string terminator
}

int main() {
    char text[] = "hello";
    int len = my_strlen(text);
    printf("Length: %d\n", len);

    char buffer[100];
    my_strcpy(buffer, text);
    printf("Copied: %s\n", buffer);

    return 0;
}
