#include <stdio.h>

int main(void) {

    int q;
    int init  = 0;
    char last = 'z'; // montar o mapa em runtime

    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        
        int x;
        char n;

        scanf("%d %c", &x, &n);

        if (n == 'D') {

            if (i == 0) {
                printf("."); // começar de (0,0)
            }

            if (last == 'B') }
                for (int j = 0; j < init; j++) {printf(" ");}
                printf("X"); // andar pra direita depois de descer implica em partir de uma casa ja visitada, portanto, marca-se o X
                for (int h = 0; h < x; h++) {printf(".");}
            } else {
                for (int g = 0; g < x; g++) {printf(".");} // caso essa instrução não seja precedida por uma descida, simplesmente imprimir os pontinhos
            }

            init += x;
            last = 'D';

        }

        else if (n == 'B') {

            printf("\n");

            if (i == q - 1) {
                for (int j = 0; j < x + 1; j++) {
                    for (int k = 0; k < init; k++) {
                        printf(" ");
                    }
                    printf(".\n"); // caso a ultima instrução seja uma descida, imprimir esse ponto no final p dar match nos test cases
                }
            } else {
                for (int j = 0; j < x; j++) {
                    for (int k = 0; k < init; k++) {
                        printf(" ");
                    }
                    printf(".\n"); // caso nao seja, simplesmente descer
                }
            }

            last = 'B';

        }

        else if (n == 'E') {

            if (x > init) {
                printf("Informacao invalida"); // esquerda volta 1 casa
                break;
            }

            if (i == 0) {
                printf("Informacao invalida"); // primeira instrução não pode ser ir pra esquerda
            } else {
                if (last != 'D') { // D e E são excludentes
                    for (int k = 0; k < init - x; k++) {
                        printf(" "); // imprimido os espaços de forma complementar
                    }
                    for (int g = 0; g < x; g++) {
                        printf(".");
                    }
                    printf("X");
                }
            }
            
            last = 'E';
            init -= x;
        }
    
    }

    return 0;
}
