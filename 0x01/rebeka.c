#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main(void) {

        int amount, x, y, z, a, b, c;
        int amountRbk  = 3;
        int done       = 0;
        int investment = -1;

        scanf("%d %d %d %d", &amount, &x, &y, &z);

        // rebeka não investe, fica com oq sobra e volta p casa
        if ((amount * x) % 100 == 0 && (amount * y) % 100 == 0 && (amount * z) % 100 == 0) {

                a = (amount * x) / 100;
                b = (amount * y) / 100;
                c = (amount * z) / 100;

                int remains = amount - (a + b + c);
                amountRbk  += remains; // rebeka fica com oq sobra da divisão
                done        = 1;
                investment  = 0;
        }
        // rebeka investe 1 real, fica com oq sobra e volta p/ casa
        if (done == 0 && ((amount + 1) * x) % 100 == 0 && ((amount + 1) * y) % 100 == 0 && ((amount + 1) * z) % 100 == 0) {

                int newAmount = amount + 1;
                int tA        = (newAmount * x) / 100;
                int tB        = (newAmount * y) / 100;
                int tC        = (newAmount * z) / 100;
                int s         = newAmount - (tA + tB + tC);

                if (s >= 2) { // retorno de pelo menos 2 reais
                        a          = tA;
                        b          = tB;
                        c          = tC;
                        amountRbk  = (3 - 1) + s;
                        done       = 1;
                        investment = 1;
                }
        }
        // rebeka investe 2 reais, fica com oq sobra e volta pra casa
        if (done == 0 && ((amount + 2) * x) % 100 == 0 && ((amount + 2) * y) % 100 == 0 && ((amount + 2) * z) % 100 == 0) {
                int newAmount = amount + 2;
                int tA        = (newAmount * x) / 100;
                int tB        = (newAmount * y) / 100;
                int tC        = (newAmount * z) / 100;
                int s         = newAmount - (tA + tB + tC);

                if (s >= 3) { // retorno de pelo menos 3 reais
                        a          = tA;
                        b          = tB;
                        c          = tC;
                        amountRbk  = (3 - 2) + s;
                        done       = 1;
                        investment = 2;
                }
        }
        // rebeka investe 3 reais, fica com oq sobra e volta pra casa
        if (done == 0 && ((amount + 3) * x) % 100 == 0 && ((amount + 3) * y) % 100 == 0 && ((amount + 3) * z) % 100 == 0) {
                int newAmount = amount + 3;
                int tA        = (newAmount * x) / 100;
                int tB        = (newAmount * y) / 100;
                int tC        = (newAmount * z) / 100;
                int s         = newAmount - (tA + tB + tC);

                if (s >= 4) { // retorno de pelo menos 4 reais
                        a          = tA;
                        b          = tB;
                        c          = tC;
                        amountRbk  = (3 - 3) + s;
                        done       = 1;
                        investment = 3;
                }
        }

        if (done) {
                printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", a, b, c);
                if (investment == 2) {
                        char c1, c2, c3;
                        scanf(" %c %c %c", &c1, &c2, &c3);
                        int v1 = (c1 >= 'a') ? (c1 - 'a' + 1) : (c1 - 'A' + 1); // ex. c1 = a ('a' = 97). 'a' - 'a' + 1 = 97 - 97 + 1 = 1
                        int v2 = (c2 >= 'a') ? (c2 - 'a' + 1) : (c2 - 'A' + 1); // ex. c2 = b ('b' = 98). 'b' - 'a' + 1 = 98 - 97 + 1 = 2 
                        int v3 = (c3 >= 'a') ? (c3 - 'a' + 1) : (c3 - 'A' + 1);
                        printf("%d\n", v1 + v2 + v3);
                }
                else if (investment == 3) {
                        int i1, i2, i3;
                        scanf("%d %d %d", &i1, &i2, &i3);
                        if (i1 % 3 == 0 || i2 % 3 == 0 || i3 % 3 == 0) {
                                int parcelas = 0;
                                if (i1 % 3 == 0) {parcelas += i1 / 3};
                                if (i2 % 3 == 0) {parcelas += i2 / 3};
                                if (i3 % 3 == 0) {parcelas += i3 / 3};
                                printf("%d\n", parcelas);
                        }
                }
        } else {
                printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
        }

        if (amountRbk >= 7) {
                printf("Ela conseguiu! Rebeka voltou para casa e apanhou da mae por sumir noite passada!\n");
        } else {
                printf("E parece que Rebeka vai ter que voltar andando...\n");
        }

        return 0;
}
