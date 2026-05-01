#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// macros default
#define SIZE    50
#define FORi(n) for (int i = 0; i < n; i++)
// definindo uma struct para organizar os jogos. para referenciá-los, basta utilizar um ponteiro para esta struct
typedef struct {
    char title[SIZE];
    char gen[SIZE];
    char studio[SIZE];
    char console[SIZE];
    int score;
    int year;
} Game;
// avaliar a nota do jogo
void evalGrade(int score) {
    if (score > 7) {
        printf("AWESOME! Mais um GOTY pra minha coleção!\n");
    } else if (score < 4) {
        printf("Era melhor jogar mais um jogo de Mahjong.\n");
    }
}
// construindo a colecao utilizando um ponteiro para a struct Game junto com a funcao realloc (trick da lista 5)
Game* buildCollection(int n) {
    Game *games = NULL;
    FORi(n) {
        games = (Game *) realloc(games, (i + 1) * sizeof(Game));
        scanf("%s %s %s %s %d %d", games[i].title, games[i].gen, games[i].studio, games[i].console, &games[i].score, &games[i].year);
        evalGrade(games[i].score);
    }
    return games;
}
// imprime os jogos lançados em um ano específico
void printAno(Game *games, int n, char *param) {
    int count = 0;
    int target = atoi(param);
    FORi(n) {
        if (games[i].year == target) {
            printf("%s\n", games[i].title);
            count++;
        }
    }
    if (count > 0) {
        printf("Tenho %d jogos || %s.\n", count, param);
    } else {
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}
// Imprime os jogos que começam com uma letra em específico
void printLetra(Game *games, int n, char *param) {
    int count = 0;
    char target = param[0];
    FORi(n) {
        if (games[i].title[0] == target) {
            printf("%s\n", games[i].title);
            count++;
        }
    }
    if (count > 0) {
        printf("Tenho %d jogos || %s.\n", count, param);
    } else {
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}
// Imprime os jogos de um estúdio especificado
void printStudio(Game *games, int n, char *param) {
    int count = 0;
    FORi(n) {
        if (strcmp(games[i].studio, param) == 0) {
            printf("%s\n", games[i].title);
            count++;
        }
    }
    if (count > 0) {
        printf("Tenho %d jogos || %s.\n", count, param);
    } else {
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}
// Imprime os jogos de um console especificado
void printConsole(Game *games, int n, char *param) {
    int count = 0;
    FORi(n) {
        if (strcmp(games[i].console, param) == 0) {
            printf("%s\n", games[i].title);
            count++;
        }
    }
    if (count > 0) {
        printf("Tenho %d jogos || %s.\n", count, param);
    } else {
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}
// imprime todos os títulos e as notas, não tem parâmetro
void printColecao(Game *games, int n, char *param) {
    FORi(n) {
        printf("%s %d\n", games[i].title, games[i].score);
    }
}
// gerenciando os callbacks utilizando um ponteiro para cad funcao
void manageCallbacks(Game *games, int n, char *func, char *arg) {
    void (*callback)(Game *, int, char *);

    while (scanf("%s", func) != EOF) {
        callback = NULL;
        arg[0] = '\0';

        if (!strcmp(func, "printAno")) { // se bem sucedida, strcmp retorna 0. usamos ! pra ficar 1 (true)
            callback = printAno;
            scanf("%s", arg);
        } else if (!strcmp(func, "printLetra")) {
            callback = printLetra;
            scanf("%s", arg);
        } else if (!strcmp(func, "printStudio")) {
            callback = printStudio;
            scanf("%s", arg);
        } else if (!strcmp(func, "printConsole")) {
            callback = printConsole;
            scanf("%s", arg);
        } else if (!strcmp(func, "printColecao")) {
            callback = printColecao;
        }

        if (callback) {
            callback(games, n, arg);
        }
    }
}

int main(void) {
    int n;
    char func[SIZE];
    char arg[SIZE];

    scanf("%d", &n);
    Game *collection = buildCollection(n);
    manageCallbacks(collection, n, func, arg);
    printf("Enjoei de jogar, agora vou ver TV.\n");
    free(collection);

    return 0;
}
