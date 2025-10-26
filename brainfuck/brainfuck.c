#include <stdio.h>

#define MAX_PATH_LENGTH 4096
#define ARRAY_SIZE 30000

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

        char character;
        short index = 0;
        char array[ARRAY_SIZE] = { 0 };

        do {
            character = fgetc(fptr);

            if (feof(fptr)) {
                break;
            }

            switch (character) {
                case '>':
                    index++;
                    if (index >= ARRAY_SIZE) {
                        index = 0;
                    }
                    break;
                case '<':
                    index--;
                    if (index < 0) {
                        index = ARRAY_SIZE-1;
                    }
                    break;
                case '+':
                    array[index]++;
                    break;
                case '-':
                    array[index]--;
                    break;
                case '.':
                    printf("%c", array[index]);
                    break;
                case ',':
                    break;
                case '[':
                    break;
                case ']':
                    break;
                default:
                    break;
            }
        } while(1);

        printf("\n");
    }

    return 0;
}