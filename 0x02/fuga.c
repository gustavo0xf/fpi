#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main(void) {

    int q, steps;
    char mov;

    scanf("%d", &q);

    int x = 0;

    for (int i = 0; i < q; i++) {

        scanf("%d %c", &steps, &mov);

        if (i == 0) {
            if (mov == 'D') {
                x = steps - 1;
                for (int j = 0; j <= x; j++) {printf(".");}
                printf("\n");
            } else if (mov == 'E') {
                x = 0 - (steps - 1);
                if (x < 0) {
                    printf("Informacao invalida\n");
                    return 0;
                }
                for (int j = 0; j <= x; j++) {printf(".");}
                printf("\n");
            } else if (mov == 'B') {
                x = 0;
                for (int j = 0; j < steps - 1; j++) {printf(".\n");}
                if (i == q - 1) {printf(".\n");}
            }
        }

        else {
            switch (mov) {
                case 'D':
                    for (int j = 0; j < x; j++) {printf(" ");}
                    for (int j = 0; j <= steps; j++) {printf(".");}
                    printf("\n");
                    x += steps;
                    break;

                case 'E': {
                    int novo_x = x - steps;

                    if (novo_x < 0) {
                        printf("Informacao invalida\n");
                        return 0;
                    }

                    for (int j = 0; j < novo_x; j++) {printf(" ");}
                    for (int j = 0; j <= steps; j++) {printf(".");}
                    printf("\n");

                    x = novo_x;
                    break;
                }

                case 'B':
                    for (int j = 0; j < steps - 1; j++) {
                        for (int s = 0; s < x; s++) printf(" ");
                        printf(".\n");
                    }

                    if (i == q - 1) {
                        for (int s = 0; s < x; s++) printf(" ");
                        printf(".\n");
                    }
                    break;
            }
        }
    }

    return 0;
}
