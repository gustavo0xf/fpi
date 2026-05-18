#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
// macros
#define FORi(n) for (int i = 0; i < n; i++)
// typedefs para o tipo uint32_t e para a union do pacote de telemetria
typedef uint32_t u32;
typedef union {
    u32 raw;
    struct {
        u32 id      : 10;
        u32 status  : 3;
        u32 battery : 1;
        u32 temp    : 12;
        u32 parity  : 6;
    } fields;
} TelPacket;
// funcao para alocar memoria dinamicamente para o ponteiro para a union
TelPacket* allocMem(int cap) {
    TelPacket *p = (TelPacket *) malloc(cap * sizeof(TelPacket));
    if (p == NULL) {
        printf("[!] failed to allocate memory\n");
        exit(1);
    }
    return p;
}
// funcao para montar os pacotes
TelPacket* buildPacket(TelPacket *packet, int *total, int *cap, u32 raw) {
    if (*total == *cap) { // capacidade maxima atingida -> dobrar o tamanho com a realloc
        *cap *= 2;
        TelPacket *tmp = (TelPacket *) realloc(packet, (*cap) * sizeof(TelPacket));
        if (tmp == NULL) {
            printf("[!] failed to allocate memory\n");
            free(packet);
            exit(1);
        }
        packet = tmp;
    }
    packet[*total].raw = raw;
    (*total)++;
    return packet;
}
// relatorio final
void printReport(TelPacket *packet, int total) {
    FORi(total) {
        printf("Pacote [%d] - Dado Bruto: 0x%08X\n", i + 1, packet[i].raw);
        printf("ID do Sensor : %u\n", packet[i].fields.id);
        printf("Status : %u\n", packet[i].fields.status);
        printf("Bateria Baixa: %s\n", packet[i].fields.battery ? "SIM (ALERTA)" : "Nao");
        printf("Temperatura : %d graus\n", ~packet[i].fields.temp + 1);
        printf("-------------------------------------------------\n");
    }
}
// liberar a memória que fora alocada
void freeMem(TelPacket *packet) {
    if (packet != NULL) {
        free(packet);
    }
}
// chamando todas as funções
int main(void) {
    int cap = 2;
    int total = 0;
    u32 input;

    TelPacket *gateway = allocMem(cap);

    while (scanf("%x", &input) == 1 && input != 0) {
        gateway = buildPacket(gateway, &total, &cap, input);
    }

    printReport(gateway, total);
    freeMem(gateway);

    return 0;
}
