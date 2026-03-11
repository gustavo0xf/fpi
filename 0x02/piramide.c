#include <stdio.h>

int main(void) {

        char c;
        scanf("%c", &c);

        for (char now = 'A'; now <= c; now++) { // implementar o algoritmo base repetidamete

                for (char dot = 0; dot < (c - now); dot++) { // mais pontinhos nas linhas com menos letras
                        printf(".");
                }

                char init = 'A';

                for (char t = 'A'; t < now; t++) { // printar as letras que antecedem a inputada em ordem crescente
                        printf("%c", t);
                }

                for (int j = 0; now >= init; j++) { // printar a letra inputada e as letras que a antecedem em ordem decrescente
                        init++;
                        printf("%c", now - j);
                }

                for (char dot = 0; dot < (c - now); dot++) { // simetria
                        printf(".");
                }

                printf("\n");

        }

        return 0;
}

/*
- algoritmo implementado pra apenas uma letra:

        for (char t = 'A'; t < c; t++) {
                printf("%c", t);
        }

        for (int j = 0; c >= init; j++) {
                init++;
                printf("%c", c - j);
        }

        ex.: input = 'D' => output: ABCDCBA
        
- feito isso, basta implementar um for pra varrer as letras partindo de A até chegar na que foi inputada e trocar as variaveis corretamente

*/
