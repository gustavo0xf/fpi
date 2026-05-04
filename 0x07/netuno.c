#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// macros default
#define FORi(n) for (int i = 0; i < n; i++)
#define FORj(n) for (int j = 0; j < n; j++)
// struct para organizar os sistemas de cada mecha
typedef struct {
    char name[30];
    int attrib1;
    int attrib2;
    void (*subroutine)(struct Mecha *m, int slot, int input, int *output);
} SubSystem;
// struct para organizar os mechas de fato
typedef struct Mecha {
    int id;
    char model[50];
    int currentEnergy;
    int numSystems;
    int wintermuteValue;
    SubSystem systems[];
} Mecha;
// tipo: defesa -> input - atrib1 - (slot * atrib2)
void execDefense(struct Mecha *m, int slot, int input, int *output) {
    int damage = input - m->systems[slot].attrib1 - (slot * m->systems[slot].attrib2);
    if (damage < 0) {
        damage = 0;
    }
    *output = damage;
}
// tipo: utilidade -> atrib1 + (slot * atrib2) e soma-se à energia atual
void execUtility(struct Mecha *m, int slot, int input, int *output) {
    int recovery = m->systems[slot].attrib1 + (slot * m->systems[slot].attrib2);
    m->currentEnergy = m->currentEnergy + recovery;
    *output = m->currentEnergy;
}
// tipo: ataque -> energia atual > custo => atrib1 + energia_atual + slot - input
void execAttack(struct Mecha *m, int slot, int input, int *output) {
    if (m->currentEnergy < m->systems[slot].attrib2) {
        *output = 0;
    } else {
        *output = m->systems[slot].attrib1 + m->currentEnergy + slot - input;
        m->currentEnergy = m->currentEnergy - m->systems[slot].attrib2;
    }
}
// funcao para montar os mechas
Mecha* buildMecha() {
    int id;
    int energy;
    int quantity;
    char model[50];

    scanf("%d %s %d %d", &id, model, &energy, &quantity);

    Mecha *m = (Mecha *) malloc(sizeof(Mecha) + (quantity * sizeof(SubSystem)));
    m->id = id;
    strcpy(m->model, model);
    m->currentEnergy = energy;
    m->numSystems = quantity;

    FORi(quantity) {
        char type[5];
        scanf("%s %s %d %d", type, m->systems[i].name, &m->systems[i].attrib1, &m->systems[i].attrib2);
        if (type[0] == 'D') {
            m->systems[i].subroutine = execDefense;
        } else if (type[0] == 'U') {
            m->systems[i].subroutine = execUtility;
        } else if (type[0] == 'A') {
            m->systems[i].subroutine = execAttack;
        }
    }
    scanf("%d", &m->wintermuteValue);

    return m;
}

int compareMecha(const void *a, const void *b) {
    Mecha *m1 = *(Mecha **) a;
    Mecha *m2 = *(Mecha **) b;

    return m1->id - m2->id;
}

void runSimulation(Mecha **squad, int numMechas) {
    printf("[RELATORIO DE MISSÃO: OPERAÇÃO LANÇA DE NETUNO]\n");
    
    FORi(numMechas) {
        Mecha *m = squad[i];
        printf("ID: %d | MECHA: %s | ENERGIA: %d\n", m->id, m->model, m->currentEnergy);
        FORj(m->numSystems) {
            if (m->systems[j].subroutine == execDefense) {
                int output;
                m->systems[j].subroutine(m, j, m->wintermuteValue, &output);
                printf("-> [DEFESA] %s | Dano final sofrido: %d\n", m->systems[j].name, output);
            }
        }
        FORj(m->numSystems) {
            if (m->systems[j].subroutine == execUtility) {
                int output;
                m->systems[j].subroutine(m, j, m->wintermuteValue, &output);
                printf("-> [UTILIDADE] %s | Energia atual: %d\n", m->systems[j].name, m->currentEnergy);
            }
        }
        FORj(m->numSystems) {
            if (m->systems[j].subroutine == execAttack) {
                int output;
                int cost = m->systems[j].attrib2;
                
                if (m->currentEnergy < cost) {
                    m->systems[j].subroutine(m, j, m->wintermuteValue, &output);
                    printf("-> [ATAQUE] %s | Energia insuficiente!\n", m->systems[j].name);
                } else {
                    m->systems[j].subroutine(m, j, m->wintermuteValue, &output);
                    printf("-> [ATAQUE] %s | Dano causado: %d | Energia restante: %d\n", m->systems[j].name, output, m->currentEnergy);
                }
            }
        }
        
        printf("ENERGIA FINAL: %d\n", m->currentEnergy);
        printf("-----------------------------------------\n");
    }
    
    printf("Esquadrao pronto para o combate.\n");
}

int main(void) {
    int numMechas;

    scanf("%d", &numMechas);

    Mecha **squad = malloc(numMechas * sizeof(Mecha *));
    FORi(numMechas) {
        squad[i] = buildMecha();
    }

    qsort(squad, numMechas, sizeof(Mecha *), compareMecha);
    runSimulation(squad, numMechas);
    FORi(numMechas) {
        free(squad[i]);
    }
    free(squad);

    return 0;
}
