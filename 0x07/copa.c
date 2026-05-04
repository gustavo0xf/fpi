#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// macros default
#define SIZE 200
#define FORi(m, n) for (int i = m; n != '\0'; i++)
#define FORj(n)    for (int i = 0; i < n; i++)
// struct para organizar as cidadelas
typedef struct {
    char name[SIZE];
    int pop;
    int hazard;
    char func[SIZE];
    int key;
    int isSpecial;
} City;
// funcao para arrumar o nome das cidades, deixando apenas a primeira letra em maiusculo
void applyTitleCase(char *text) {
    if (strlen(text) == 0) {
        return;
    } 
    text[0] = toupper(text[0]);
    FORi(1, text[i]) {
        text[i] = tolower(text[i]);
    }
}
// recebe a mensagem cifrada (src), extrai o nome da cidade (letras em maiusculo) e joga pra uma nova string (dst)
void extractName(char *src, char *dst) {
    int index = 0;
    FORi(0, src[i]) {
        if (isupper(src[i])) {
            dst[index] = src[i];
            index++;
        }
    }
    dst[index] = '\0';
    applyTitleCase(dst);
}
// recebe a mensagem cifrada (src) e retorna a população concatenando TODOS os dígitos da string
int extractPop(char *src) {
    int totalPop = 0;
    for (int i = 0; src[i] != '\0'; i++) {
        if (isdigit(src[i])) {
            totalPop = (totalPop * 10) + (src[i] - '0');
        }
    }
    return totalPop;
}
// recebe a mensagem cifrada (src) e calcula a quantidade de asteriscos, que definem a periculosidade
int extractHazard(char *src) {
    int hazardLevel = 0;
    FORi(0, src[i]) {
        if (src[i] == '*') {
            hazardLevel++;
        }
    }
    return hazardLevel;
}
// recebe a mensagem cifrada (src), extrai a funcao da cidade e joga pra uma nova string (dst)
void extractFunc(char *src, char *dst) {
    int index = 0;
    char *ptr = strstr(src, "  "); 
    
    if (ptr != NULL) {
        int i = 0;
        int inWord = 0;
        while (ptr[i] != '\0') {
            if (isalpha(ptr[i])) {
                if (!inWord) {
                    // Pega a primeira letra de cada palavra encontrada após o espaço duplo
                    dst[index++] = ptr[i];
                    inWord = 1;
                }
            } else {
                inWord = 0;
            }
            i++;
        }
    }
    dst[index] = '\0';
    applyTitleCase(dst);
}
// recebe a string criptografada e monta a struct para aquela cidade, chamando todas as funções acima
City decryptMsg(char *msg) {
    City currentCity;

    currentCity.name[0] = '\0';
    currentCity.func[0] = '\0';
    currentCity.pop     = 0;
    currentCity.hazard  = extractHazard(msg);
    currentCity.key     = 0;
    
    if (strchr(msg, '!') != NULL) { // caso tenha um ! na mensagem, definir a cidade como sendo especial 
        currentCity.isSpecial = 1;
        currentCity.key = extractPop(msg);
    } else {
        currentCity.isSpecial = 0;
        extractName(msg, currentCity.name);
        currentCity.pop = extractPop(msg);
        extractFunc(msg, currentCity.func);
    }
    
    return currentCity;
}
// funcao para comparar o tamaho das populações de cada cidade
int compareCities(const void *a, const void *b) {
    City *cityA = (City *) a;
    City *cityB = (City *) b;
    
    if (cityA->pop != cityB->pop) {
        return cityB->pop - cityA->pop;
    }
    if (cityA->hazard != cityB->hazard) {
        return cityB->hazard - cityA->hazard;
    }
    return strcmp(cityA->name, cityB->name);
}
// chamando todas as outras funcoes
int main(void) {
    char encryptedMsg[SIZE];
    int counter = 0;
    int finalKey = 0;
    City *cities = NULL;

    while (fgets(encryptedMsg, SIZE, stdin) != NULL) {
        City parsedCity = decryptMsg(encryptedMsg);
        
        if (parsedCity.isSpecial) {
            finalKey = parsedCity.key;
        } else {
            cities = (City *) realloc(cities, sizeof(City) * (counter + 1));
            cities[counter] = parsedCity;
            counter++;
        }
    }

    if (finalKey == 0) {
        printf("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n");
    } else {
        qsort(cities, counter, sizeof(City), compareCities);
        City targetCity = cities[finalKey - 1];
        printf("Gingrey foi encontrada em %s, uma cidadela com %d mil habitantes cuja função é %s e periculosidade ", targetCity.name, targetCity.pop, targetCity.func);
        FORj(targetCity.hazard) {
            printf("*");
        }
        printf(". "); 

        if (targetCity.pop >= 1000 && targetCity.hazard > 3) {
            printf("Talvez seja melhor desistir...\n");
        } else if (targetCity.pop >= 1000) {
            printf("Um lugar denso, vai ser difícil achar ela.\n");
        } else if (targetCity.hazard > 3) {
            printf("Vai ser complicado entrar lá.\n");
        } else {
            printf("\n");
        }
    }

    free(cities);
    return 0;
}
