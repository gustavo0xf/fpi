#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FORi(a)    for (int i = 0; i < a; i++)
#define FORt(b)    for (int t = 0; t < b; t++)
#define FORm(x, y) for (int i = 0; i < (x); i++) for (int j = 0; j < (y); j++)
#define FORf(c)    for (int dx = -1; dx <= 1; dx++) for (int dy = -1; dy <= 1; dy++)
// alocando memoria para a matriz
int** allocMatrix(int rows, int cols) {
    int **matrix = (int **) malloc(rows * sizeof(int *));
    FORi(rows) {
        matrix[i] = (int *) malloc(cols * sizeof(int));
    }
    return matrix;
}
// montando a matriz
void buildMatrix(int **matrix, int rows, int cols) {
    FORm(rows, cols) {
        scanf("%d", &matrix[i][j]);
    }
}
// liberando a memoria alocada
void freeMatrix(int **matrix, int rows) {
    FORi(rows) {
        free(matrix[i]);
    }
    free(matrix);
}
// função para verificar os limites da matriz
int isInside(int r, int c, int rows, int cols) {
    if (r >= 0 && r < rows && c >= 0 && c < cols) {
        return 1;
    }
    return 0;
}
// função para aplicar as modificações na primeira camada
int modFirstLayer(int r, int c, int targetX, int targetY) {
    if (r == targetX && c == targetY) {
        return 1;
    }
    if (r == targetX - 1 && c == targetY) {
        return 1;
    }
    if (r == targetX + 1 && c == targetY) {
        return 1;
    }
    if (r == targetX && c == targetY - 1) {
        return 1;
    }
    if (r == targetX && c == targetY + 1) {
        return 1;
    }
    return 0;
}
// função para aplicar as modificações na segunda camada
int modSecondLayer(int r, int c, int targetX, int targetY, int rows, int cols) {
    if (modFirstLayer(r, c, targetX, targetY)) {
        return 0;
    }
    FORf(0) {
        int ni = r + dx;
        int nj = c + dy;
        if (modFirstLayer(ni, nj, targetX, targetY)) {
            return 1;
        }
    }
    return 0;
}
// função para contar os vizinhos
int evalAdjc(int **matrix, int r, int c, int rows, int cols) {
    int adjc = 0;
    FORf(0) {
        if (dx == 0 && dy == 0) {
            continue;
        }
        int ni = r + dx;
        int nj = c + dy;
        if (isInside(ni, nj, rows, cols)) {
            if (matrix[ni][nj] > 0) {
                adjc++;
            }
        }
    }
    return adjc;
}
// função para aplicar a explosao arcana
void arcaneExplosion(int **matrix, int rows, int cols, int targetX, int targetY) {
    printf("Estado do mapa após usar a Explosão Arcana:\n");
    FORm(rows, cols) {
        int damage = 0;
        if (modFirstLayer(i, j, targetX, targetY)) {
            damage = 50;
        } else if (modSecondLayer(i, j, targetX, targetY, rows, cols)) {
            damage = 25;
        }
        matrix[i][j] = matrix[i][j] - damage;
        if (matrix[i][j] < 0) {
            matrix[i][j] = 0;
        }
    }
    FORi(rows) {
        for (int j = 0; j < cols; j++) {
            printf("%d", matrix[i][j]);
            if (j < cols - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}
// função para aplicar a nuvem venenosa
void poisonCloud(int **matrix, int rows, int cols, int targetX, int targetY) {
    printf("Estado do mapa, por turno, após usar a Nuvem Venenosa:\n");
    FORt(3) {
        int livingInArea = 0;
        int **tempMatrix = allocMatrix(rows, cols);
        FORm(rows, cols) {
            tempMatrix[i][j] = matrix[i][j];
        }
        FORm(rows, cols) {
            if (modFirstLayer(i, j, targetX, targetY) || modSecondLayer(i, j, targetX, targetY, rows, cols)) {
                int neighbors = evalAdjc(matrix, i, j, rows, cols);
                int damage = 5 + (8 * neighbors);
                tempMatrix[i][j] = tempMatrix[i][j] - damage;
                if (tempMatrix[i][j] < 0) {
                    tempMatrix[i][j] = 0;
                }
                if (tempMatrix[i][j] > 0) {
                    livingInArea = 1;
                }
            }
        }
        FORm(rows, cols) {
            matrix[i][j] = tempMatrix[i][j];
        }
        freeMatrix(tempMatrix, rows);
        FORi(rows) {
            for (int j = 0; j < cols; j++) {
                printf("%d", matrix[i][j]);
                if (j < cols - 1) {
                    printf(" ");
                }
            }
            printf("\n");
        }
        if (livingInArea == 0) {
            break;
        }
        printf("\n");
    }
}
// printando a matriz inicial
void printMatrix(int **matrix, int rows, int cols) {
    printf("Estado inicial do mapa:\n");
    FORi(rows) {
        for (int j = 0; j < cols; j++) {
            printf("%d", matrix[i][j]);
            if (j < cols - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main(void) {
    int rows, cols, targetX, targetY;
    char agentName[50];
    int **grid, **gridCopy;

    if (scanf("%d %d", &rows, &cols) != 2) {
        return 0;
    }
    grid = allocMatrix(rows, cols);
    buildMatrix(grid, rows, cols);
    
    scanf("%d %d", &targetX, &targetY);
    scanf("%s", agentName);

    gridCopy = allocMatrix(rows, cols);
    FORm(rows, cols) {
        gridCopy[i][j] = grid[i][j];
    }

    printMatrix(grid, rows, cols);

    void (*agent)(int**, int, int, int, int) = NULL;

    if (strcmp(agentName, "EXPLOSAO_ARCANA") == 0) {
        agent = arcaneExplosion;
    } else if (strcmp(agentName, "NUVEM_VENENOSA") == 0) {
        agent = poisonCloud;
    }

    if (agent != NULL) {
        agent(gridCopy, rows, cols, targetX, targetY);
    }

    freeMatrix(grid, rows);
    freeMatrix(gridCopy, rows);

    return 0;
}
