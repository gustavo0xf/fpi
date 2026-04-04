#include <stdio.h>

int main(void) {

        char movs[100];
        int matrix[4][4] = {{0, 0}};
        // variaveis de controle comuns na hora de encontrar o maior/menor elemento de uma matriz -> current + greater
        int curr_line = 0;
        int curr_column = 0;
        int greater = 0;
        int x_greater = 0;
        int y_greater = 0;

        fgets(movs, 100, stdin);

        for (int k = 0; k < 42; k++) {

            if (movs[k] != ' ') { // a sequencia de movimento contém espaços, mas eles nao me interessam

                if (movs[k] == 'b') { // baixo: aumenta a linha atual e incrementa em 1 o novo indice correspondente
                    curr_line++;
                    matrix[curr_line][curr_column]++;
                } else if (movs[k] == 'c') { // cima: diminui a linha atual e incrementa em 1 o novo indice correspondente
                    curr_line--;
                    matrix[curr_line][curr_column]++;
                } else if (movs[k] == 'd') { // direita: aumenta a coluna atual e incrementa em 1 o novo indice correspondente
                    curr_column++;
                    matrix[curr_line][curr_column]++;
                } else if (movs[k] == 'e') { // esquerda: diminui a coluna atual e incrementa em 1 o novo indice correspondente
                    curr_column--;
                    matrix[curr_line][curr_column]++;
                }

            }
        }

        // método clássico de encontrar o maior elemento em uma matriz
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == 0 && j == 0) {
                    greater = matrix[i][j]; // definimos o primeiro elemento como o maior
                } else if (matrix[i][j] > greater) { // continua lendo a matriz, se encontrar um valor maior, ele passa a ser o novo maaior (confuso, mas vc entendeu)
                    greater = matrix[i][j];
                    x_greater = i;
                    y_greater = j;
                }
            }
        }

        printf("Coordenada X:%d, Y:%d\n", y_greater, x_greater);

        return 0;
}
