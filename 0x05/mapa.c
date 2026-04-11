#include <stdio.h>
#include <stdlib.h>

// função para printar os numeros impares
void printOdds(int *array, int size) { // recebe um ponteiro para o array com os numeros, alem do seu tamanho
    for (int i = 0; i < size; i++) {
        if (array[i] % 2 != 0) { // verifica se é impar
            printf("%d\n", array[i]);
        }
    }
}

// função para printar os numeros pares
void printEven(int *array, int size) { // recebe um ponteiro para o array com os numeros, alem do seu tamanho
    for (int i = 0; i < size; i++) {
        if (array[i] % 2 == 0) { // verifica se é par
            printf("%d\n", array[i]);
        }
    }
}

int main() {

    // inicializa um ponteiro para receber os numeros, além de um contador para nos auxiliar a receber os valores, visto que de antemão não sabemos a quantidade  
    int *places = NULL;
    int number, counter = 0;

    while (scanf("%d", &number) != EOF) { // recebe os numeros até o input acabar (EOF = end of file)

        counter++; // a cada novo numero recebido, incrementa o contador
        // como não sabemos quantos numeros vamos receber, a cada numero recebido, fazemos um resize na região de memoria que guarda esses valores
        int *tmp = realloc(places, counter * sizeof(int)); 

        // boa prática: trata um eventual erro de alocação de memoria
        if (tmp == NULL) {
            printf("[!] failed to allocate memory\n");
            free(places);
            exit(1);
        }

        places = tmp;
        places[counter - 1] = number; // gradualmente vai montando o array com os inputs
    }

    printf("Mais um bom dia de trabalho!\n");

    if (counter > 0) {
        printOdds(places, counter);
        printEven(places, counter);
    }

    printf("Vou visitar esses lugares de novo... algum dia.\n");

    free(places); // boa prática: limpa a região de memória após o final do programa
    // use after free
    return 0;
}
