#include <stdio.h>

int main(void) {
    
    int tests, size;
    
    scanf("%d", &tests);
    
    for (int i = 0; i < tests; i++) {
        
        scanf("%d", &size);
        
        int vtr[size];
        
        for (int j = 0; j < size; j++) {
            scanf("%d", &vtr[j]); // montar o array com os numeros fornecidos, de acordo com o tamanho especificado
        }
        
        if (size < 2) {
            printf("0\n"); // se o array tiver apenas 1 numero, não existe sequencia, logo, passamos pro proximo array
            continue;
        }
        
        int max_len    = 1; // maior sequencia
        int curr_len   = 1; // tamanho da sequencia atual
        int max_start  = 0; // a partir de onde devemos começar a olhar a sequencia
        int curr_start = 0;
        
        for (int j = 1; j < size; j++) {
            if (vtr[j] < vtr[j - 1]) { // numero atual - seu antecessor
                curr_len++;
            } else {
                if (curr_len > max_len) {
                    max_len   = curr_len; // sequencia atual vira a sequencia otima
                    max_start = curr_start;
                }
                curr_len   = 1; // reinicia o contador caso não seja a sequencia otima
                curr_start = j;
            }
        }
        
        if (curr_len > max_len) {
            max_len   = curr_len; // ao final da iteração, a sequencia otima é validada, bem como aonde ela se inicia
            max_start = curr_start; 
        }
        
        if (max_len > 1) { // se a sequencia for maior que 1, printar seus elementos e o seu tamanho
            printf("%d\n", max_len);
            for (int j = 0; j < max_len; j++) {
                printf("%d ", vtr[max_start + j]);
            }
            printf("\n");
        } else {
            printf("0\n");
        }
    }
    
    return 0;
}

/*
- principais ideias:
    - minha ideia original era usar um array pra pegar a sequencia, mas isso dava problema na hora de validar a sequencia otima
    - definir o tamanho da sequencia otima e onde ela se inicia dentro do proprio array é uma ideia muito mais inteligente
    - definir o estado atual de uma coisa para depois validar o estado ótimo é uma boa ideia na hora de implementar variaveis de controle

#include <stdio.h>

int main(void) {

        int cases, size, value;
        int ant, suc, counter = 0;

        scanf("%d", &cases);

        for (int i = 0; i < cases; i++) {

                scanf("%d", &size);
                
                int vtr[size], seq[size];

                for (int j = 0; j < size; j++) {
                        scanf("%d", &value);
                        vtr[j] = value;
                }

                for (int k = 0; k < size; k++) {
                    
                    if (k == 0) {
                        ant = 0;
                        suc = vtr[k + 1];
                    } else if (k == size - 1) {
                        ant = vtr[k - 1];
                        suc = 0;
                    } else {
                        ant = vtr[k - 1];
                        suc = vtr[k + 1];
                    }

                    if (vtr[k] - ant <= 0) {
                        seq[k - 1] = vtr[k - 1];
                        seq[k] = vtr[k];
                    }
                    
                    if (vtr[k] > suc && k == 0) {
                        seq[k] = vtr[k];
                    }
                    
                }
                
                for (int b = 0; b < size; b++) {
                    if (seq[b] != 0) {
                        counter++;
                    }
                }
                
                printf("%d\n", counter);
                counter = 0;
                
                for (int c = 0; c < size; c++) {
                    if (seq[c] != 0) {
                        printf("%d ", seq[c]);
                    }
                }
                
                for (int a = 0; a < size; a++) {
                    seq[a] = 0;
                }
                
                printf("\n");

        }

        return 0;
}
*/
