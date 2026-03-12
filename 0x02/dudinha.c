#include <stdio.h>

int main(void) {
    int n, k, p;

    scanf("%d %d %d", &n, &k, &p);

    int primeiro_achado = -1;
    int total_encontrados = 0;

    for (int i = n; i < k; i++) {
        int num_atual = i;

        if (num_atual < 2) {
            if (p == 0) {
                if (primeiro_achado == -1) primeiro_achado = i;
                total_encontrados++;
            }
            continue;
        }

        while (num_atual % 2 == 0) {
            num_atual /= 2;
        }

        int fatores_impares_distintos = 0;
        int valido = 1;

        for (int j = 3; j * j <= num_atual; j += 2) {
            if (num_atual % j == 0) {
                fatores_impares_distintos++;
                num_atual /= j;

                if (num_atual % j == 0) {
                    valido = 0;
                    break;
                }
            }
        }

        if (valido && num_atual > 1) {
            fatores_impares_distintos++;
        }

        if (valido && fatores_impares_distintos == p) {
            if (primeiro_achado == -1) {
                primeiro_achado = i;
            }
            total_encontrados++;
        }
    }

    if (primeiro_achado != -1) {
        printf("%d %d\n", primeiro_achado, total_encontrados - 1);
    } else {
        printf("Poxa dudinha, me desculpa, nao achei os numeros mas vou te mandar uma foto de um gatinho fofo.\n");
    }

    return 0;
}
