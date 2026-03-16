#include <stdio.h>

int main(void) {
    
    int n, k, p;

    scanf("%d %d %d", &n, &k, &p);

    int primeiro_achado = -1;
    int total_encontrados = 0;

    for (int i = n; i < k; i++) {
        int num_atual = i;

        // caso trivial: a contagem começa com n = 1 ou n = 0 e o numero de fatores primos impares distintos é 0, logo, eles devem entrar na contagem
        if (num_atual < 2) {
            if (p == 0) {
                if (primeiro_achado == -1) {primeiro_achado = i;}
                total_encontrados++;
            }
            continue; // volta pro fluxo de execução normal do loop
        }

        while (num_atual % 2 == 0) {
            num_atual /= 2; // limpeza de qualquer fator 2, pois só queremos fatores primos ímpares
        }

        int fatores_impares_distintos = 0; // controle dos fatores impares
        int valido = 1; // como já foi feita a limpeza de fatores pares, vai sobrar apenas um número inteiro então, por padrão, dizemos que ele é válido, caso contrário, mudamos esse valor

        // j² <= num_atual ∴ j <= \sqrt(num_atual). se um numero tem um fator, pelo menos um dos fatores é menor ou igual à raiz quadrada desse numero
        for (int j = 3; j * j <= num_atual; j += 2) { // como já eliminamos os fatores pares, podemos começar do 3 e ir pulando de 2 em 2
            if (num_atual % j == 0) {
                fatores_impares_distintos++; // estamos iterando divisões por impares, então a cada laço, aumentamos nosso controle
                num_atual /= j;

                if (num_atual % j == 0) { // se após a divisão, ele continua divisível pelo mesmo numero impar, não nos serve mais
                    valido = 0;
                    break;
                }
            }
        }

        if (valido && num_atual > 1) { // caso o nosso número impar não atenda a nenhuma das condições acima, como ele ainda obviamente tem um fator impar, registramos isso
            fatores_impares_distintos++;
        }

        if (valido && fatores_impares_distintos == p) { // numero válido e tem os fatores impares especificados pelo usuário: OK
            if (primeiro_achado == -1) {
                primeiro_achado = i;
            }
            total_encontrados++; // faz a validação entre n e k
        }
    }

    if (primeiro_achado != -1) {
        printf("%d %d\n", primeiro_achado, total_encontrados - 1);
    } else {
        printf("Poxa dudinha, me desculpa, nao achei os numeros mas vou te mandar uma foto de um gatinho fofo.\n");
    }

    return 0;
}
