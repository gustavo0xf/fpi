#include <stdio.h>

int main(void) {
    
    int m, n;
    
    scanf("%d %d", &m, &n);
    char room[m][n + 1];
    
    for (int i = 0; i < m; i++) {
        scanf("%s", &room[i]); 
    }
    
    int water = 1;

    while (water) {
        
        water = 0; // flag de controle, verifica se a água ainda pode cair
        
        // varrendo a matriz do quarto
        for (int i = 0; i < m - 1; i++) {
            for (int j = 0; j < n; j++) {
                
                // ao encontrar uma gota d'agua, começar a declarar as condições p/ ela cair
                if (room[i][j] == 'o') {
                    
                    // se não tiver nenhuma prateleira, molha 
                    if (room[i + 1][j] == '.') {
                        room[i + 1][j] = 'o';
                        water = 1;
                    }
                    
                    // bateu na prateleira, espalha pros lados
                    else if (room[i + 1][j] == '#') {
                        // espalha pra esquerda
                        if (j > 0 && room[i][j - 1] == '.') { // j = 0 -> extrema esquerda
                            room[i][j - 1] = 'o'; // muda a gotinha pra esquerda pra continuar a descida
                            water = 1;
                        }
                        // espalha pra direita
                        if (j < n - 1 && room[i][j + 1] == '.') { // j = n - 1 -> extrema direita
                            room[i][j + 1] = 'o'; // muda a gotinha pra direita pra continuar a descida
                            water = 1;
                        }
                    }
                }
            }
        }
    }
    
    // quarto molhado
    for (int i = 0; i < m; i++) {
        printf("%s\n", room[i]);
    }
    
    return 0;
}
