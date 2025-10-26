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
        printf("\nError opening the file.\n");
    }
    else {
        printf("\nFile opened successfully.\n");

        char c;

        do {
            c = fgetc(fptr);

            if (feof(fptr)) {
                break;
            }

            printf("%c", c);
        } while(1);

        printf("\n");
    }

    return 0;
}