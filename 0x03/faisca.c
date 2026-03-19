#include <stdio.h>
#include <string.h> // strlen() e strcat()

int main() {
    
    int tests, clocks;
    char config[61];
    char giant[70000]; // até 1000 casos de configurações com até 60 leds
    int bigLen = 0; // inicializando a variável para o tamanho da luz gigante

    scanf("%d", &tests);

    for (int i = 0; i < tests; i++) {
        
        scanf("%s %d", config, &clocks);

        int size_c = strlen(config); // pegar o tamaho da configuração

        for (int j = 0; j < clocks; j++) { // varre os clocks
            for (int k = 0; k < size_c; k++) { // para cada clock, varremos a configuração para facilitar a aplicação das regras
                char lastState = config[k]; // salva o ultimo estado do bit a ser modificado, variável de controle muito comum
              
                if (config[k] == 'O') {
                    config[k] = 'X'; // se estava ligado, desliga
                } else {
                    config[k] = 'O'; // se estava desligado, liga
                }

                if (lastState == 'O' && config[k] == 'X') {
                    continue; // se o bit passou de 0 pra X, pulamos direto para o proximo bit, para que consigamos mudar o seu estado (k = 0 -> k = 1)
                } else {
                    break; // nesse caso, como apenas o MSB deve mudar, o trabalho com esse clock já está feito, podemos ir pro proximo (j = 0 -> j = 1)
                }
            }
        }
        printf("%s\n", config);
        
        if (i > 0) { // só vale se tiver feito mais de um teste
            
            char lastLed  = giant[bigLen - 1]; // ultimo led da luz gigante, vulgo ultimo led do ultimo teste
            char firstLeD = config[0]; // primeiro led da luz gigante, vulgo primeiro led do primeiro teste
            char orn;

            // tradução imediata das instruções do enunciado
            if (bigLen % 2 == 0) {
                if (lastLed == firstLeD) {
                    orn = '@';
                } else {
                    orn = '$';
                }
            } else {
                if (lastLed == firstLeD) {
                    orn = '#';
                } else {
                    orn = '%';
                }
            }
            
            giant[bigLen] = orn; // adicionar os ornamentos
            bigLen++;
            giant[bigLen] = '\0';
            
        }
        
        strcat(giant, config); // concatena as configurações com os ornamentos
        bigLen += size_c; // luz gigante recebe o tamanho das configurações
        
    }
    
    printf("%s", giant);
    

    return 0;
}

/*
- principais ideias:
  - é interessante usar variaveis de controle para o ultimo valor de uma iteração
  - strcat() -> concatenação
*/
