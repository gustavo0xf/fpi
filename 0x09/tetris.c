#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// struct para os nós da pilha
typedef struct Node {
    char color;
    struct Node *below; 
} Node;
// struct com um ponteiro para o topo da pilha e com o tamanho da pilha
typedef struct {
    Node *top;
    int height;       
} Board;          
// inicializar a stack, zerando a altura e anuland o topo
void initBoard(Board *b) {
    b->top = NULL;
    b->height = 0;
}
// verifica se a pilha ta vazia
bool isEmpty(Board *b) {
    if (b->top == NULL) {
        return true;
    }
    return false;
}
// retorna a cor do topo da pilha
char peekTop(Board *b) {
    if (isEmpty(b)) {
        return 0;
    }
    return b->top->color;
}
// retorna a cor do elemento logo abaixo do topo
char peekSecond(Board *b) {
    if (b->height >= 2) {
        return b->top->below->color;
    }
    return 0;
}
// operação de empilhar
void push(Board *b, char color) {
    Node *newBlock = (Node*) malloc(sizeof(Node));
    if (newBlock == NULL) {
        exit(1); 
    }
    newBlock->color = color;
    newBlock->below = b->top; 
    b->top = newBlock;
    b->height++;
}
// operação de desempilhar
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
// printar a stack
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
// zera a stack
void clearBoard(Board *b) {
    while (!isEmpty(b)) {
        pop(b);
    }
}
// lógica proposta na questão de combinar as cores
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
// lógica proposta na questão de eliminar os nós
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
// chamando todas as funções
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
