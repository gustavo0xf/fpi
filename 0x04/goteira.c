#include <stdio.h>

int main(void) {
    
    int m, n;
    
    scanf("%d %d", &m, &n);
    char room[m][n + 1];
    
    for (int i = 0; i < m; i++) {
        scanf("%s", &room[i]); // montagem da matriz de chars
    }
    
    int water = 1; // flag de controle, verifica se a água ainda pode cair

    while (water) {
        
        water = 0; // evitar que o loop seja infinito
        // varrendo a matriz do quarto
        for (int i = 0; i < m - 1; i++) {
            for (int j = 0; j < n; j++) {
                
                // varre a matriz e acha a gotinha
                if (room[i][j] == 'o') {
                    
                    // se não tiver nenhuma prateleira  abaixo, molha 
                    if (room[i + 1][j] == '.') {
                        room[i + 1][j] = 'o';
                        water = 1; // pode continuar caindo
                    }
                    // se tiver uma prateleira abaixo, escorre pros lados
                    else if (room[i + 1][j] == '#') {
                        // espalha pra esquerda
                        if (j > 0 && room[i][j - 1] == '.') { // verifica os limiites da matriz e verifica se tá livre pra molhar
                            room[i][j - 1] = 'o';
                            water = 1; // pode continuar caindo
                        }
                        // espalha pra direita
                        if (j < n - 1 && room[i][j + 1] == '.') { // verifica os limites da matriz e verifica se tá livre pra molhar
                            room[i][j + 1] = 'o'; // muda a gotinha pra direita pra continuar a descida
                            water = 1; // pode continuar caindo
                        }
                    }
                }
            }
        }
    }
    
    // retorna o quarto molhado
    for (int i = 0; i < m; i++) {
        printf("%s\n", room[i]);
    }
    
    return 0;
}
