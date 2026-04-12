#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double evalAvg(double *grades, int n) {

    double sum = 0;

    for (int i = 0; i < n; i++) {
        sum += grades[i];
    }

    if (n > 0) {
        return sum / n;
    } else {
        return 0;
    }
}

void evalExt(double *grades, int n) {

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
    double tmp = *first;
    *first = *second;
    *second = tmp;
}

void bSort(double *grades, int n) {

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (grades[j] > grades[j + 1]) {
                swap(&grades[j], &grades[j + 1]);
            }
        }
    }
}

double evalMedian(double *grades, int n) {

    double *temp = malloc(n * sizeof(double));
    memcpy(temp, grades, n * sizeof(double));
    
    bSort(temp, n);

    double res;

    if (n % 2 == 0) {
        res = (temp[n/2 - 1] + temp[n/2]) / 2.0;
    } else {
        res = temp[n/2];
    }

    free(temp);
    return res;
}

void evalMode(double *grades, int n) {

    double *temp = malloc(n * sizeof(double));
    memcpy(temp, grades, n * sizeof(double));
    bSort(temp, n);

    int max_freq = 0;
    int c_freq = 1;
    int modes_count = 0;
    double mode_val = temp[0];

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

    if (modes_count == 1) {
        printf("Moda: %.2f\n", mode_val);
    } else {
        printf("Moda: Nao ha moda unica\n");
    }

    free(temp);
}

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

    printReport(grades, n, "Relatorio inicial");

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

    printReport(grades, n, "Relatorio atualizado");

    free(grades); // boa prática: limpando a região de memória após ser usada

    return 0;
}
