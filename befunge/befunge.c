#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PATH_LENGTH 4096
#define NBLINES 25
#define NBCOLUMNS 80

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

bool isADigit(char character) {
    return character >= 48 && character <= 57;
}

void moveForward(struct GridPointer *gridPointer, enum Direction direction) {
    switch (direction) {
        case UP:
            gridPointer->y = (gridPointer->y - 1) % NBLINES;
            break;
        case RIGHT:
            gridPointer->x = (gridPointer->x + 1) % NBCOLUMNS;
            break;
        case DOWN:
            gridPointer->y = (gridPointer->y + 1) % NBLINES;
            break;
        case LEFT:
            gridPointer->x = (gridPointer->x - 1) % NBCOLUMNS;
            break;
    }
}

int main() {
    srand(time(NULL));

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
        long a;
        long b;
        long v;
        long x;
        long y;

        // File loading
        char playfield[NBLINES][NBCOLUMNS];
        for (int i = 0; i < NBLINES; i++) {
            for (int j = 0; j < NBCOLUMNS; j++) {
                playfield[i][j] = ' ';
            }
        }
        char line = 0;
        char column = 0;
        do {
            character = fgetc(fptr);

            if (feof(fptr)) {
                break;
            }

            else if (character == '\n') {
                if (line < NBLINES) {
                    line++;
                } else {
                    break;
                }
                column = 0;
            }

            else {
                playfield[line][column] = character;
                if (column < NBCOLUMNS) {
                    column++;
                } else {
                    break;
                }
            }
        } while (1);

        do {
            character = playfield[gridPointer.y][gridPointer.x];

            if (character == '@') {
                break;
            }

            if (isADigit(character)) {
                push(&stack, character - 48);
            } else {
                switch (character) {
                    case '+':
                        a = pop(&stack);
                        b = pop(&stack);
                        push(&stack, a + b);
                        break;
                    case '-':
                        a = pop(&stack);
                        b = pop(&stack);
                        push(&stack, b - a);
                        break;
                    case '*':
                        a = pop(&stack);
                        b = pop(&stack);
                        push(&stack, a * b);
                        break;
                    case '/':
                        a = pop(&stack);
                        b = pop(&stack);
                        push(&stack, b / a);
                        break;
                    case '%':
                        a = pop(&stack);
                        b = pop(&stack);
                        push(&stack, b % a);
                        break;
                    case '!':
                        a = pop(&stack);
                        push(&stack, a == 0);
                        break;
                    case '`':
                        a = pop(&stack);
                        b = pop(&stack);
                        push(&stack, b > a);
                        break;
                    case '>':
                        direction = RIGHT;
                        break;
                    case '<':
                        direction = LEFT;
                        break;
                    case '^':
                        direction = UP;
                        break;
                    case 'v':
                        direction = DOWN;
                        break;
                    case '?':
                        direction = rand() % 4;
                        break;
                    case '_':
                        a = pop(&stack);
                        if (a == 0) {
                            direction = RIGHT;
                        } else {
                            direction = LEFT;
                        }
                        break;
                    case '|':
                        a = pop(&stack);
                        if (a == 0) {
                            direction = DOWN;
                        } else {
                            direction = UP;
                        }
                        break;
                    case '"':
                        moveForward(&gridPointer, direction);
                        character = playfield[gridPointer.y][gridPointer.x];
                        while (character != '"') {
                            push(&stack, character);
                        }
                        break;
                    case ':':
                        a = pop(&stack);
                        push(&stack, a);
                        push(&stack, a);
                        break;
                    case '\'':
                        a = pop(&stack);
                        b = pop(&stack);
                        push(&stack, a);
                        push(&stack, b);
                        break;
                    case '$':
                        pop(&stack);
                        break;
                    case '.':
                        a = pop(&stack);
                        printf("%ld", a);
                        break;
                    case ',':
                        a = pop(&stack);
                        printf("%c", a);
                        break;
                    case '#':
                        moveForward(&gridPointer, direction);
                        break;
                    case 'g':
                        y = pop(&stack);
                        x = pop(&stack);
                        v = 0;
                        if (x >= 0 && x < NBCOLUMNS && y >= 0 && y < NBLINES) {
                            v = *playfield[y, x];
                        }
                        break;
                    case 'p':
                        y = pop(&stack);
                        x = pop(&stack);
                        v = pop(&stack);
                        if (x >= 0 && x < NBCOLUMNS && y >= 0 && y < NBLINES) {
                            *playfield[y, x] = v;
                        }
                        break;
                    case '&':
                        long numericValue;
                        scanf("%ld", &numericValue);
                        push(&stack, numericValue);
                        break;
                    case '~':
                        char characterValue;
                        scanf("%c", &characterValue);
                        push(&stack, characterValue);
                        break;
                    default:
                        break;
                }
            }
            moveForward(&gridPointer, direction);
        } while(1);

        free(stack.data);
    }
}