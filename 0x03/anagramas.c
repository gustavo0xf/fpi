#include <stdio.h>
#include <string.h> // fgets()

int main(void) {
  
    char str[105];
    int inicio[50], fim[50]; // arrays para guardar a posição de inicio e fim anagramas
    int n = 0, i, j, k, total = 0;

    fgets(str, sizeof(str), stdin); // a scanf() é ruim pra ler string com espaço

    for (i = 0; str[i] != '\0' && str[i] != '\n'; i++) { // iterando sobre a string até ela acabar ou até ter uma quebra de linha
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
            inicio[n] = i; // marca o começo do anagrama
            while ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) { // case insensitive
                i++; // o problema diz que a string pode ter caracteres especiais, mas os anagramas só podem conter letras
            }
            fim[n] = i - 1; // marca o fim do anagrama
            n++;
            i--; 
        }
    }

    int header = 0; // flag para garantir que o cabeçalho só apareça se encontrarmos o primeiro par
    for (i = 0; i < n; i++) { // seleciona uma palavra da lista mapeada
        for (j = i + 1; j < n; j++) { // percorre as palavras seguintes para formar pares únicos
            int tam1 = fim[i] - inicio[i] + 1; // calcula o tamanho da palavra i
            int tam2 = fim[j] - inicio[j] + 1; // calcula o tamanho da palavra j

            if (tam1 == tam2) { // se os tamanhos forem diferentes, é impossível ser anagrama
                int freq[26] = {0}; // array de contagem para as 26 letras do alfabeto
                
                for (k = inicio[i]; k <= fim[i]; k++) { // processa a primeira palavra do par
                    char c = str[k];
                    if (c >= 'A' && c <= 'Z') c += 32; // normaliza para minúsculo usando a tabela ASCII (+32)
                    freq[c - 'a']++; // incrementa a "balança" na posição da letra
                }
                
                for (k = inicio[j]; k <= fim[j]; k++) { // processa a segunda palavra do par
                    char c = str[k];
                    if (c >= 'A' && c <= 'Z') c += 32; // normaliza para minúsculo
                    freq[c - 'a']--; // decrementa a "balança" (anulando o incremento se a letra for igual)
                }

                int is_anagram = 1; // assume que é anagrama até que se prove o contrário
                for (k = 0; k < 26; k++) {
                    if (freq[k] != 0) { // se sobrou alguma letra na contagem, não é anagrama
                        is_anagram = 0;
                        break;
                    }
                }

                if (is_anagram) {
                    if (header == 0) {
                        printf("Pares de anagramas encontrados:\n");
                        header = 1; // ativa o header para não imprimir novamente
                    }
                    // imprime as palavras buscando direto na string original através dos índices salvos
                    for (k = inicio[i]; k <= fim[i]; k++) printf("%c", str[k]);
                    printf(" e ");
                    for (k = inicio[j]; k <= fim[j]; k++) printf("%c", str[k]);
                    printf("\n");
                    total++; // incrementa o contador global de pares
                }
            }
        }
    }

    if (total > 0) {
        printf("\nTotal de pares: %d\n", total); // exibe a contagem final se houver ocorrências
    } else {
        printf("Nao existem anagramas na frase.\n"); // caso contrário, exibe a mensagem de ausência
    }

    return 0;
}
