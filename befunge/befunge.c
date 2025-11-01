#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_PATH_LENGTH 4096
#define WIDTH 80
#define HEIGHT 25

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

struct GridPointer {
    int x;
    int y;
};

struct Stack {
    int size;
    long* data;
};

void push(struct Stack *stack, long value) {
    stack->size++;
    stack->data = realloc(stack->data, stack->size * sizeof(long));
    stack->data[stack->size-1] = value;
}

long pop(struct Stack *stack) {
    long value = 0;
    if (stack->size > 0) {
        value = stack->data[stack->size-1];
        stack->size--;
        stack->data = realloc(stack->data, stack->size * sizeof(long));
    }
    return value;
}

int main() {
    printf("----- Befunge interpreter -----\n");
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

        enum Direction direction = RIGHT;
        struct GridPointer gridPointer = {.x = 0, .y = 0};
        struct Stack stack = {.size = 0, .data = NULL};
        bool stringMode = false;
        char character;

        do {
            character = fgetc(fptr);

            if (feof(fptr)) {
                break;
            }

            switch (character) {
                default:
                    break;
            }
        } while(1);

        free(stack.data);
    }
}