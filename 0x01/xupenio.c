#include <stdio.h>

int main(void) {

        long long n, a, b, sum1, m1, m2, m3, sum2, sum3, sum4; // 1 <= N, A, B <= 10000000 esse valor não cabe num int, logo foi usado um long long

        scanf("%lld", &n);
        scanf("%lld %lld", &a, &b);

        sum1 = ((1 + n)*n)/2 ;                     // soma de todos os numeros do intervalo. ex.: (1 + 10).10/2 = 11.10/2 = 55
        m1   = n/a;                                // pegar o numero de multiplos de a dentro do intervalo. ex.: 10/2 = 5 (2,4,6,8,10)
        m2   = n/b;                                // pegar o numero de multiplos de b dentro do intervalo. ex.: 10/3 = 3 (3,6,9)
        m3   = n/(a*b);                            // pegar a quantidade de termos repetidos. ex.: 10/6 = 1
        sum2 = ((a + m1*a)*m1)/2;                  // soma dos multiplos de a
        sum3 = ((b + m2*b)*m2)/2;                  // soma dos multiplos de b
        sum4 = ((a*b + m3*a*b)*m3)/2;              // soma dos termos repetidos
        printf("%lld\n", sum1 - sum2 - sum3 + sum4); // total - multiplos de a - multiplos de b + repetidos

        if ((sum1 - sum2 - sum3 + sum4) % 2 == 0 ) {
                printf("Lá ele!!!\n");
        } else if ((sum1 - sum2 - sum3 + sum4) % 2 != 0 ) {
                printf("Opa xupenio AULAS...\n");
        }

        return 0;
}
