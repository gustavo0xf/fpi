#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    char color;
    struct Node *below; 
} Node;

typedef struct {
    Node *top;
    int height;       
} Board;          

void initBoard(Board *b) {
    b->top = NULL;
    b->height = 0;
}

bool isEmpty(Board *b) {
    if (b->top == NULL) {
        return true;
    }
    return false;
}

char peekTop(Board *b) {
    if (isEmpty(b)) {
        return 0;
    }
    return b->top->color;
}

char peekSecond(Board *b) {
    if (b->height >= 2) {
        return b->top->below->color;
    }
    return 0;
}

void push(Board *b, char color) {
    Node *newBlock = (Node*) malloc(sizeof(Node));
    if (newBlock == NULL) {
        return; 
    }
    
    newBlock->color = color;
    newBlock->below = b->top; 
    
    b->top = newBlock;
    b->height++;
}

char pop(Board *b) {
    if (isEmpty(b)) {
        return 0;
    }
    
    Node *removedBlock = b->top;
    char color = removedBlock->color;
    
    b->top = removedBlock->below;
    free(removedBlock);
    b->height--;
    
    return color;
}

void printBoard(Board *b) {
    if (isEmpty(b)) {
        printf("Pilha vazia!\n\n");
    } else {
        Node *current = b->top;
        while (current != NULL) {
            printf("%c\n", current->color);
            current = current->below;
        }
        printf("\n");
    }
}

void clearBoard(Board *b) {
    while (!isEmpty(b)) {
        pop(b);
    }
}

char mergeColors(char c1, char c2) {
    if ((c1 == 'g' && c2 == 'b') || (c1 == 'b' && c2 == 'g')) {
        return 'c';
    }
    if ((c1 == 'r' && c2 == 'b') || (c1 == 'b' && c2 == 'r')) {
        return 'm';
    }
    if ((c1 == 'r' && c2 == 'g') || (c1 == 'g' && c2 == 'r')) {
        return 'y';
    }
    return 0; 
}

void dropBlock(Board *b, char newColor) {
    if (!isEmpty(b)) {
        char mergedColor = mergeColors(peekTop(b), newColor);
        if (mergedColor != 0) {
            pop(b); 
            dropBlock(b, mergedColor);
            return;
        }
    }

    if (b->height >= 2 && peekTop(b) == newColor && peekSecond(b) == newColor) {
        pop(b);
        pop(b);
    } else {
        push(b, newColor);
    }
}

int main() {
    Board game;
    initBoard(&game);
    char incomingColor;

    while (scanf(" %c", &incomingColor) != EOF) {
        dropBlock(&game, incomingColor);
        printBoard(&game);
    }

    printf("Thank You So Much For Playing My Game!\n");
    clearBoard(&game); 
    
    return 0;
}
