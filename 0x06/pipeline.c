#include <stdio.h>
#include <stdlib.h>
#define FORi(n)    for (int i = 0; i < n; i++)
#define FORm(x, y) for (int i = 0; i < (x); i++) for (int j = 0; j < (y); j++)
// para as minhas funções "default", o comentário será precedido por um (*), visto que serão utilizadas em praticamente todas as questoes da lista
// (*) alocando memoria pra matriz
int** allocMatrix(int m, int n) {
    int **matrix = (int **) malloc(m * sizeof(int *));
    FORi(m) {
        matrix[i] = (int *) malloc(n * sizeof(int));
    }
    return matrix;
}
// (*) montando a matriz
void buildMatrix(int **matrix, int m, int n) {
    FORm(m, n) {
        scanf("%d", &matrix[i][j]);
    }
}
// (*) boa prática: limpeza de memória 
void freeMatrix(int **matrix, int m) {
    FORi(m) {
        free(matrix[i]);
    }
    free(matrix);
}
// operação 1
int cmd1 (int n) { 
    return n + 5; 
}
// operação 2
int cmd2 (int n) { 
    if (n > 80) {
        return 80;
    } else {
        return n;
    }
 }
// operação 3
int cmd3 (int n) { 
    return n * 2; 
}
// gerenciamento da pipeline
void runPipeline(int **matrix, int m, int n, int (**pipeline)(int), int k) {
    FORm(m, n) {
        for (int f = 0; f < k; f++) {
            matrix[i][j] = pipeline[f](matrix[i][j]); // note que a função recebe um vetor de ponteiros para função, para viabilizar o gerenciamento da pipeline
        }
    }
}
// função para fazer o gerenciamento da pipeline em si
void manageProc(int **matrix, int m, int n) {
    int code;
    int (*cmd[])(int) = {NULL, cmd1, cmd2, cmd3}; // definindo um vetor de ponteiros para função

    while (scanf("%d", &code) && code != 0) {
        int k = 0;
        int (**pipeline)(int) = NULL; // inicializando o vetor de ponteiros para função que vai ser de fato passado pra função acima
        // tratando as operações de 1 a 3 como casos particulares da operação 4, isto é, uma pipeline com apenas uma operação
        if (code >= 1 && code <= 3) {
            k = 1;
            pipeline = (int (**)(int)) malloc(sizeof(int (*)(int))); // alocando memoria pro ponteiro da pipeline
            pipeline[0] = cmd[code];
        }
        else if (code == 4) { // caso a pipeline de fato seja acionada, vamos liberar para continuar recebendo comandos
            scanf("%d", &k);
            pipeline = (int (**)(int)) malloc(k * sizeof(int (*)(int))); // alocando memoria pro ponteiro da pipeline, de acordo com o numero de operações
            FORi(k) {
                int id;
                scanf("%d", &id);
                pipeline[i] = cmd[id]; // populando a pipeline
            }
        }

        if (pipeline != NULL) {
            runPipeline(matrix, m, n, pipeline, k);
            free(pipeline);
        }
    }
}

void finishProc(int **matrix, int m, int n) {
    int max = matrix[0][0];
    int mi = 0;
    int mj = 0;

    printf("Matriz processada:\n");
    FORi(m) {
        for (int j = 0; j < n; j++) {
            printf("%d%s", matrix[i][j], (j == n - 1) ? "" : " ");
            if (matrix[i][j] > max) {
                max = matrix[i][j];
                mi = i; 
                mj = j;
            }
        }
        printf("\n");
    }
    printf("\n");
    printf("Sensor critico: %d\n", max);
    printf("Posicao: (%d,%d)\n", mi, mj);
}

int main(void) {
    int m, n;
    int **matrix;

    scanf("%d %d", &m, &n);

    matrix = allocMatrix(m, n);
    buildMatrix(matrix, m, n);
    manageProc(matrix, m, n);
    finishProc(matrix, m, n);
    freeMatrix(matrix, m);

    return 0;
}
