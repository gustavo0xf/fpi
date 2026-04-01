#include <stdio.h>

int main(void)

    int m, n;
    scanf("%d %d", &m, &n);

    char plaza[m][n + 1];
    char result[m][n + 1];

    for (int i = 0; i < m; i++) {
        scanf("%s", plaza[i]);
        for (int j = 0; j < n; j++) {
            result[i][j] = plaza[i][j];
        }
        result[i][j] = '\0';
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {

            if (plaza[i][j] == 'P') {

                for (int d_line = -1; d_line <= 1; d_line++) {
                    for (int d_column = -1; d_column <= 1; d_column++) {

                        int line_adjc = i + d_line;
                        int column_adjc = j + d_column;

                        if (line_adjc >= 0 && line_adjc < m && column_adjc >= 0 && column_adjc < n) {

                            if (plaza[line_adjc][column_adjc] != 'P') {

                                if (d_line == 0 || d_column == 0) {
                                    if (d_line != 0 || d_column != 0) { // não é o próprio centro
                                        result[line_adjc][column_adjc] = '+';
                                    }
                                } else {
                                    if (result[line_adjc][column_adjc] == '-') {
                                        result[line_adjc][column_adjc] = 'x';
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    for (int l = 0; l < m; l++) {
        printf("%s\n", result[l]);
    }

    return 0;
}
