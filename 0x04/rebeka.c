#include <stdio.h>

int main(void) {
    
    int m, n;
    
    scanf("%dx%d", &m, &n);
    char map[m][n + 1];
    int dist[m][n]; // matriz pr reegistrar a distancia que cada elemento está da origem
    // variaveis de controle para marcar a posição do destino
    int x_goal = -1;
    int y_goal = -1;

    for (int i = 0; i < m; i++) {
        scanf("%s", map[i]); // monta o mapa
        for (int j = 0; j < n; j++) {
            
            dist[i][j] = 9999; // ao mesmo tempo, preenche a matriz de distancias com 9999 em tudo que não for a origem
            
            if (map[i][j] == 'o') {
                dist[i][j] = 0; // a distancia da origem pra origem eh 0
            }
            
            if (map[i][j] == 'd') { // registra a posição de destino
                x_goal = i; 
                y_goal = j; 
            }
            
        }
    }

    for (int step = 0; step < m * n; step++) { // simular a caminhada da rebeka
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                
                if (dist[i][j] == step) {
                    // mesma trick da questão da praça, agora com a feature de não andar em diagonal
                    for (int d_line = -1; d_line <= 1; d_line++) {
                        for (int d_col = -1; d_col <= 1; d_col++) {
                            
                            if ((d_line == 0 || d_col == 0) && (d_line != d_col)) { // delta line e delta column iguais implicam em uma mov. diagonal
                                
                                int ni = i + d_line;
                                int nj = j + d_col;

                                if (ni >= 0 && ni < m && nj >= 0 && nj < n) { // verifica os limites da matriz
                                    if (map[ni][nj] != '#' && dist[ni][nj] > step + 1) { // verific se não tem obstaculos
                                        dist[ni][nj] = step + 1; // atualiza a matriz de distancias
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (dist[x_goal][y_goal] != 9999) { // se a matriz de distancias, no indice do destino, for diferente de 9999, é pq foi alterada, então, é pq rebeka chegou
            break;
        }
    }

    // mensagens finais
    if (dist[x_goal][y_goal] != 9999) {
        printf("Apos correr %d metros e quase desistir por causa da dist�ncia, Rebeka conseguiu escapar!\n", dist[x_goal][y_goal]);
    } else {
        printf("Poxa... Parece que nao foi dessa vez que Rebeka conseguiu fugir\n");
    }

    return 0;
}
