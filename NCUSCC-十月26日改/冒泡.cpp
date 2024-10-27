#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DATASETSIZE 100000

void exchange(int *number1, int *number2) {
    int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

void maopao(int numbers[], int size) {
    if (size < 3) {
        puts("������3���������֡�");
        exit(1);
    }
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                exchange(&numbers[j], &numbers[j + 1]);
            }
        }
    }
}

void writeToFile(const char *filename, int *arr, int n) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file '%s'!\n", filename);
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        if (fprintf(file, "%d\n", arr[i]) < 0) {
            printf("Error writing to file '%s'!\n", filename);
            fclose(file);
            exit(1);
        }
    }
    fclose(file);
}

int main() {
    int *numbers = (int*)malloc(DATASETSIZE * sizeof(int));
    if (numbers == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Generate random data
    for (int i = 0; i < DATASETSIZE; i++) {
        scanf("%d",numbers[i])
    }

    // Sort the data
    maopao(numbers, DATASETSIZE);

    // Write sorted data to file
    printf("Writing to file...\n");
    writeToFile("test.txt", numbers, DATASETSIZE);
    printf("Writing complete.\n");

    // Free the allocated memory
    free(numbers);

    return 0;
}

