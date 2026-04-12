#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// função para calcular a média das notas, recebe um ponteiro para as notas, bem como o seu tamanho
double evalAvg(double *grades, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += grades[i];
    }
    if (n > 0) {
        return sum / n; // simplesmente soma todos os elementos e divide pelo numero de termos, óbvio
    } else {
        return 0;
    }
}
// função para calcular a menor e a maior nota
void evalExt(double *grades, int n) {
    // uma abordagem clássica para decidir qual dos elementos de um array é o maior/menor
    // dizemos que o maior/menor é o primeiro, daí, percorremos o array e caso o elemento atual seja maior/menor que o suposto maior/menor, atualizamos.
    double big = grades[0];
    double small = grades[0];
    int bigIdx = 1;
    int smallIdx = 1;

    for (int i = 1; i < n; i++) {
        if (grades[i] > big) {
            big = grades[i];
            bigIdx = i + 1;
        }
        if (grades[i] < small) {
            small = grades[i];
            smallIdx = i + 1;
        }
    }
    printf("Maior nota: %.2f (aluno %d)\n", big, bigIdx);
    printf("Menor nota: %.2f (aluno %d)\n", small, smallIdx);
}
// função para contar quantos alunos ficaram acima da média, não tem muito oq comentar acerca.
int evalBests(double *grades, int n, double avg) {
    int counter = 0;
    for (int i = 0; i < n; i++) {
        if (grades[i] > avg) {
            counter++;
        }
    }
    return counter;
}

void swap(double *first, double *second) {
    double tmp = *first; // segura o primeiro
    *first = *second; // primeiro -> segundo
    *second = tmp; // segundo -> primeiro
}
// função para gerenciar o bubble sort, algoritmo simples para ordenar o array em ordem crescente, viabilizando o calculo da mediana e facilitando o da moda.
void bSort(double *grades, int n) {
    // percorremos duas vezes o array, chamando a função de swap para ordenar os termos na ordem crescente
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (grades[j] > grades[j + 1]) {
                swap(&grades[j], &grades[j + 1]);
            }
        }
    }
}
// função para avaliar a mediana da amostra
double evalMedian(double *grades, int n) {
    double *temp = malloc(n * sizeof(double)); // declarmos um ponteiro temporario, para receber uma copia do array original
    memcpy(temp, grades, n * sizeof(double));
    bSort(temp, n); // fazemos o bubble sort na cópia do array, para evitar problemas
    double res;
    // qtd. par -> mediana = media dos termos medios, qtd impar -> mediana = termo medio
    if (n % 2 == 0) {
        res = (temp[n/2 - 1] + temp[n/2]) / 2.0;
    } else {
        res = temp[n/2];
    }

    free(temp);
    return res;
}
// função para avaliar a moda da amostra. lembre-se de que podem haver multiplas modas
void evalMode(double *grades, int n) {
    double *temp = malloc(n * sizeof(double));
    memcpy(temp, grades, n * sizeof(double));
    bSort(temp, n); // mesmo esquema da função anterior de fazer o bubble sort na copia do array
    // variaveis de controle para contabilizarmos a frequencia de cada termo, bem como a maxima freq., que nos ajudará a decidir se a moda é única
    int max_freq = 0;
    int c_freq = 1;
    int modes_count = 0;
    double mode_val = temp[0];
    // varremos o array, verificamos os limites e coletamos os termos repetidos. depois verificamos se é a maior moda possivel
    for (int i = 1; i <= n; i++) {
        if (i < n && temp[i] == temp[i - 1]) {
            c_freq++;
        } else {
            if (c_freq > max_freq) {
                max_freq = c_freq;
            }
            c_freq = 1;
        }
    }
    // varremos o array novamente e contamos as modas
    c_freq = 1;
    for (int i = 1; i <= n; i++) {
        if (i < n && temp[i] == temp[i - 1]) {
            c_freq++;
        } else {
            if (c_freq == max_freq) {
                modes_count++;
                mode_val = temp[i - 1];
            }
            c_freq = 1;
        }
    }
    // verificar unicidade da moda
    if (modes_count == 1) {
        printf("Moda: %.2f\n", mode_val);
    } else {
        printf("Moda: Nao ha moda unica\n");
    }
    free(temp);
}
// função para printar o relatorio final, com todas as informações obtidas 
void printReport(double *grades, int n, char *title) {
    printf("%s\n", title);
    double avg = evalAvg(grades, n);
    printf("Media: %.2f\n", avg);
    evalExt(grades, n);
    printf("Acima da media: %d\n", evalBests(grades, n, avg));
    printf("Mediana: %.2f\n", evalMedian(grades, n));
    evalMode(grades, n);
    printf("\n");
}

int main() {

    int n, k = 0;
    scanf("%d", &n);

    double *grades = malloc(n * sizeof(double)); // aloca memoria para o ponteiro que vai apontar para o array de notas

    for (int i = 0; i < n; i++) {
        scanf("%lf", &grades[i]); // monta o array com as notas
    }

    printReport(grades, n, "Relatorio inicial"); // mostra o relatorio, passando o ponteiro pras notas e o seu tamanho

    if (scanf("%d", &k) == 1) {
        if (k >= 0) {
            // fazendo um resize na região de memória já alocada, para receber as novas notas
            grades = realloc(grades, (n + k) * sizeof(double));
            for (int i = 0; i < k; i++) {
                scanf("%lf", &grades[n + i]);
            }
            n += k;
        }
    }

    printReport(grades, n, "Relatorio atualizado"); // relatorio final
    free(grades); // boa prática: limpando a região de memória após ser usada

    return 0;
}
