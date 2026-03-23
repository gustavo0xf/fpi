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

*/
