#include <stdio.h>

int main(void) {

        char movs[42];
        int matrix[4][4] = {{0, 0}};
        int curr_line = 0;
        int curr_column = 0;
        int greater = 0;
        int x_greater = 0;
        int y_greater = 0;

        fgets(movs, 42, stdin);

        for (int k = 0; k < 42; k++) {

            if (movs[k] != ' ') {

                if (movs[k] == 'b') {
                    curr_line++;
                    matrix[curr_line][curr_column]++;
                } else if (movs[k] == 'c') {
                    curr_line--;
                    matrix[curr_line][curr_column]++;
                } else if (movs[k] == 'd') {
                    curr_column++;
                    matrix[curr_line][curr_column]++;
                } else if (movs[k] == 'e') {
                    curr_column--;
                    matrix[curr_line][curr_column]++;
                }

            }
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {

                if (i == 0 && j == 0) {
                    greater = matrix[i][j];
                } else if (matrix[i][j] > greater) {
                    greater = matrix[i][j];
                    x_greater = i;
                    y_greater = j;
                }
            }
        }

        printf("Coordenada X:%d, Y:%d\n", y_greater, x_greater);

        return 0;
}
