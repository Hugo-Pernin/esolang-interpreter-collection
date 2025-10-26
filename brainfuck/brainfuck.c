#include <stdio.h>

const int MAX_PATH_LENGTH = 4096;

int main() {
    printf("----- Brainfuck interpreter -----\n");
    printf("Please enter your file path: ");
    
    char path[MAX_PATH_LENGTH];
    scanf("%s", path);

    FILE* fptr;
    fptr = fopen(path, "r");

    if (fptr == NULL) {
        printf("Error opening the file.\n");
    }
    else {
        printf("File opened successfully.\n");
    }

    return 0;
}