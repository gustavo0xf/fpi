#include <stdio.h>
#include <string.h> // strcpy()

int main(void) {
    
    int m, n;
    
    scanf("%d %d", &m, &n);
    char plaza[m][n + 1];
    char result[m][n + 1];

    // essa trick pode ser utilizada em basicmente em todas as questões
    // consiste em iterar sobre a matriz original e fazer as alterações em uma matriz auxiliar
    for (int i = 0; i < m; i++) {
        scanf("%s", plaza[i]);
        strcpy(result[i], plaza[i]);
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // itera sobre a matriz e acha um poste
            if (plaza[i][j] == 'P') {
                // como precisaamos verificar as adjacencias do poste, precisamos verificaar o que está acima, abaixo, à direita e à esquerda
                // para não fazer um condicional para cada caso, criamos um for de -1 (cima/esquerda) a +1 (baixo, direita) pra linha e coluna
                for (int d_line = -1; d_line <= 1; d_line++) {
                    for (int d_column = -1; d_column <= 1; d_column++) {
                        
                        if (d_line == 0 && d_column == 0) {
                            continue; // pula o próprio poste
                        }

                        int ni = i + d_line; // cima/baixo
                        int nj = j + d_column; // direita/esquerda
                        // verifica os limites da matriz e vê se não é poste
                        if (ni >= 0 && ni < m && nj >= 0 && nj < n && result[ni][nj] != 'P') {
                            
                            if (d_line == 0 || d_column == 0) { // mesma linha ou mesma coluna do poste = cima/baixo + direita/esquerda -> recebe o +
                                result[ni][nj] = '+';
                            }
                            else if (result[ni][nj] == '-') { // se não recebe o + e tá livre, recebe o x
                                result[ni][nj] = 'x';
                            }
                        }
                    }
                }
            }
        }
    }
    // mostra o resultado
    for (int i = 0; i < m; i++) {
        printf("%s\n", result[i]);
    }

    return 0;
}
