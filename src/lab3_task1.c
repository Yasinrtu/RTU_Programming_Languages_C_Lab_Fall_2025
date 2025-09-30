#include <stdio.h>

// find minimum value
int array_min(int arr[], int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

// find maximum value
int array_max(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// calculate sum
int array_sum(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// calculate average
float array_avg(int arr[], int size) {
    int sum = array_sum(arr, size);
    return (float)sum / size;
}

int main() {
    int arr[] = {10, 20, 5, 30, 15};
    int n = 5;

    printf("Min: %d\n", array_min(arr, n));
    printf("Max: %d\n", array_max(arr, n));
    printf("Sum: %d\n", array_sum(arr, n));
    printf("Avg: %.2f\n", array_avg(arr, n));

    return 0;
}
