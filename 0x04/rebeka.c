#include <stdio.h>
#include <stdbool.h>

int main(void) {
    
    int m, n;
    int distance = 0;
    int curr_line;
    int curr_column;
    bool win = false;

    scanf("%dx%d", &m, &n);
    char map[m][n + 1];
    
    for (int i = 0; i < m; i++) {
        scanf("%s", &map[i]);
    }
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            
            if (map[i][j] == 'o') {
                
                curr_line = i;
                curr_column = j;
                
                if (map[i + 1][j] == '_' && map[i + 1][j] != 'd') {
                    curr_line++;
                    distance++;
                    map[i][j] = 'x';
                    map[curr_line][curr_column] = 'o';
                } else if (map[i - 1][j] == '_' && map[i - 1][j] != 'd') {
                    curr_line--;
                    distance++;
                    map[i][j] = 'x';
                    map[curr_line][curr_column] = 'o';
                } else if (map[i][j + 1] == '_' && map[i][j + 1] != 'd') {
                    curr_column++;
                    distance++;
                    map[i][j] = 'x';
                    map[curr_line][curr_column] = 'o';
                } else if (map[i][j - 1] == '_' && map[i][j - 1] != 'd') {
                    curr_column--;
                    distance++;
                    map[i][j] = 'x';
                    map[curr_line][curr_column] = 'o';
                }
                
                if (map[i + 1][j] == 'd' || map[i - 1][j] == 'd' || map[i][j + 1] == 'd' || map[i][j - 1] == 'd') {
                    distance++;
                    win = true;
                }
                
            }
            
        }
    }
    
    if (win) {
        printf("Apos correr %d metros e quase desistir por causa da dist�ncia, Rebeka conseguiu escapar!\n", distance);
    } else {
        printf("Poxa... Parece que nao foi dessa vez que Rebeka conseguiu fugir\n");   
    }
    
    return 0;
}
