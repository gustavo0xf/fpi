#include <stdio.h>
// minha macro default
#define FORi(n) for (int i = 0; i < n; i++)
// typedef para o tipo unsigned char e para a union com o byte bruto e a struct com os bitfields
typedef unsigned char uchar
typedef union {
        uchar rawByte;          // byte bruto
        struct {
                uchar err  : 1; // 1 bit (LSB)
                uchar mode : 3; // 3 bits
                uchar read : 4; // 4 bits (MSB)
        } fields;
} SensorStatus;
// a funcao recebe o valor de teste e acontece o truncamento para preencher os bitfields, considerando a ordem definida no enunciado
void manageSensor(uchar value) {
        SensorStatus status;
        status.rawByte = value;
        printf("Byte bruto: %u | Erro: %u | Modo: %u | Leitura: %u\n", status.rawByte, status.fields.err, status.fields.mode,status.fields.read);
}
// efetuando os testes
int main(void) {
    uchar tests[] = {0, 255, 162, 85, 200};

    FORi(5) {
        manageSensor(tests[i]);
    }

    return 0;
}
