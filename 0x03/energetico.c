#include <stdio.h>

int main(void) {
    
    int n, x, y, w, z, cans;

    scanf("%d %d %d", &n, &x, &y);

    int clients[n + 1];
    
    for (int i = 0; i <= n; i++){
        clients[i] = 0; // evitar problemas com garbage
    }

    if (x > 0) {
        for (int a = x; a <= n; a += x) {
            clients[a] = 1; // clientes que compraram apenas 1 lata
        }
    }

    for (int i = 0; i < y; i++) {
        
        scanf("%d:%d %d", &w, &z, &cans);
        
        int pos = (w * 3600 + z * 60 - 25200) / 180; // ex.: 9h30 - 7h00 = 50
        
        if (pos >= 0 && pos <= n) {
            clients[pos] = cans; // clientes que compraram mais de uma lata
        }
    }

    int sum = 0;

    for (int i = 0; i <= n; i++) {
        
        int cans_f = clients[i];
        
        if (cans_f == 0) {
            continue;
        }

        if (sum < 50 && (sum + cans_f) >= 50) {
            
            int t_min = i * 3;
            int hh    = 7 + (t_min / 60);
            int mm    = t_min % 60;

            printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d lata%s.\n", 
                    i, hh, mm, cans_f, (cans_f > 1 ? "s" : ""));
            return 0;
        }
        
        sum += cans_f;
    }

    printf("Ainda nao foram vendidas latas suficientes. Faltam %d latas.\n", 50 - sum);

    return 0;
}
