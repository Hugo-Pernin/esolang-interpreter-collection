#include <stdio.h>
#include <stdlib.h>

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
        unsigned char array[ARRAY_SIZE] = { 0 };
        long* openingBrackets = NULL;
        int openingBracketsLastIndex = -1;

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
                    scanf(" %c", &array[index]);
                    break;
                case '[':
                    if (array[index] == 0) {
                        while (1) {
                            character = fgetc(fptr);
                            if (character == ']') {
                                break;
                            }
                        }
                    }
                    else {
                        openingBracketsLastIndex++;
                        openingBrackets = realloc(openingBrackets, (openingBracketsLastIndex + 1) * sizeof(long));
                        openingBrackets[openingBracketsLastIndex] = ftell(fptr);
                    }
                    break;
                case ']':
                    if (array[index] != 0) {
                        fseek(fptr, openingBrackets[openingBracketsLastIndex], SEEK_SET);
                    }
                    else {
                        openingBracketsLastIndex--;
                        openingBrackets = realloc(openingBrackets, (openingBracketsLastIndex + 1) * sizeof(long));
                    }
                    break;
                default:
                    break;
            }
        } while(1);

        printf("\n");
    }

    return 0;
}