#include <stdio.h>

int main(void) {
    
    int clients, x, y, hh, mm, cans;
    int sys_cans[100000] = {0}; // array com o registro de todas as latas compradas
    
    scanf("%d", &clients);
    scanf("%d", &x);
    scanf("%d", &y);
    
    for (int i = 0; i < y; i++) {
        scanf("%d:%d %d", &hh, &mm, &cans);
        int total_mins = (hh - 7) * 60 + mm; // ex.: 09h30 - 07h00 = 150 min
        int client_idx = total_mins / 3; // pega a posição do cliente na ordem de compras.
        sys_cans[client_idx] = cans; // atualiza o array na posição do cliente com o seu n de latas
    }
    
    int total_cans_sold = 0;
    int winner_client   = 0; // cliente que comprou a 50 lata
    int winner_cans     = 0; // quantas latas ele comprou
    
    for (int i = 1; i <= clients; i++) { // começa em 1 pq a primeira venda é efetuada sempre às 07h03, ai no nosso calculo fica 3min/3 = 1
        
        int current_cans = 0; // manter o registro de quantas latas foram vendidas
        
        if (sys_cans[i] > 0) { // verifica se o cliente i tem o seu numero de latas registrado
            current_cans = sys_cans[i];
        } else if (x != 0 && i % x == 0) {
            current_cans = 1; // se não tiver, coloca uma, pois até agora, nosso array só tem os que compraram duas ou mais latas.
        }
        
        total_cans_sold += current_cans; // atualiza o registro
        
        // se ja foram vendidas 50 latas e o vencedor ainda não foi definido, definir agr
        if (total_cans_sold >= 50 && winner_client == 0) {
            winner_client = i;
            winner_cans = current_cans;
        }
    }
    
    // vencedor já definido
    if (winner_client != 0) {
        // pegando o horario em que o cliente venceu
        int winner_mins = winner_client * 3;
        int winner_hh = 7 + (winner_mins / 60);
        int winner_mm = winner_mins % 60;
        
        if (winner_cans == 1) {
            printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d lata.\n", winner_client, winner_hh, winner_mm, winner_cans); // uma
        } else {
            printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d latas.\n", winner_client, winner_hh, winner_mm, winner_cans); // umas
        }
    } else {
        int missing = 50 - total_cans_sold;
        if (missing == 1) {
            printf("Ainda nao foram vendidas latas suficientes. Falta %d lata.\n", missing); // uma
        } else {
            printf("Ainda nao foram vendidas latas suficientes. Faltam %d latas.\n", missing); // umas
        }
    }
    
    return 0;
}

/*
- resumo
 - criamos um array pra registrar o numero de latas dos clientes que compraram varias latas, a partir da sua posição
 - iteramos sobre o numero de clientes
  - se sys_cans[i] > 0 -> latas_atual = sys_cans[i]
  - se (x != 0 && i % x == 0) -> latas_atual = 1
  - total_latas += latas_atual
  - se total_latas >= 50 -> cliente_vencedor = i; latas_compradas por ele = latas_atual
- burocracia
*/
