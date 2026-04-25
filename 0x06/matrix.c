#include <stdio.h>
#include <stdlib.h>

#define FORi(a) for (int i = 0; i < a; i++)
#define FORm(m, n) for (int i = 0; i < (m); i++) for (int j = 0; j < (n); j++)
// função para alocar memória para a matriz
int** allocMatrix(int m, int n) {
    int **matrix = (int **) malloc(m * sizeof(int *)); // alocando memoria para toda a região que receberá a matriz dinâmica
    // boa prática: tratando possíveis erros na alocação de memória
    if (matrix == NULL) {
        printf("[!] failed to allocate memory");
        exit(1);
    }
    // iterando sobre a matriz dinâmica e alocando memória para cada linha, além de validar possíveis erros na alocação de memória
    FORi(m) {
        matrix[i] = (int *) malloc(n * sizeof(int));
        if (matrix == NULL) {
            printf("[!] failed to allocate memory");
            exit(1);
        }
    }
    return matrix;
}
// função para montar a matriz
void buildMatrix(int **matrix, int m, int n) {
    FORm(m, n) {
        scanf("%d", &matrix[i][j]);
    }
}
// operação 1
int doubleVal(int val) {
    return val * 2;
}
// operação 2
int quadVal(int val) {
    return val * val;
}
// operação 3
int absVal(int val) {
    return abs(val);
}
// função que itera sobre a matriz e aplica as operações a partir do ponteiro operation, que é um ponteiro para função
void applyOperation(int **matrix, int m, int n, int (*operation)(int)) {
    FORm(m, n) {
        matrix[i][j] = operation(matrix[i][j]);
    }
}
// função para gerenciar as operações usando o switch
void manageOp(int **matrix, int m, int n, int op) {
    int (*operation)(int) = NULL; // é mais inteligente declarar o ponteiro para função aqui dentro do que na main
    switch(op) {
        case 1:
            operation = doubleVal;
            break;
        case 2:
            operation = quadVal;
            break;
        case 3:
            operation = absVal;
            break;
    }
    if (operation != NULL) {
        applyOperation(matrix, m, n, operation);
    }
}
// função para printar a matriz, ao final das operações
void printMatrix(int **matrix, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d%s", matrix[i][j], (j == n - 1) ? "" : " ");
        }
        printf("\n");
    }
}
// função para liberar a memória ao final do programa (boa prática)
void freeMem(int **matrix, int m) {
    FORi(m) {
        free(matrix[i]);
    }
    free(matrix);
}

int main(void) {
    int m, n, op;
    int **matrix;

    scanf("%d %d", &m, &n);
    
    matrix = allocMatrix(m, n);
    buildMatrix(matrix, m, n);

    scanf("%d", &op);
    
    manageOp(matrix, m, n, op);
    printMatrix(matrix, m, n);
    freeMem(matrix, m);

    return 0;
}
