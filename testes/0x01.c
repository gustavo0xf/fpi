#include <stdio.h>

int main(void) {

    int v1, v2, v3, d, d1, d2, bonus, dpath, ipath;

    scanf("%d %d %d %d", &v1, &v2, &v3, &d);

    d1 = d / 10;
    d2 = d % 10;

    if (d1 > d2) {
        dpath = v1 + v3 + (d1 - d2);
        ipath = v1 + v2 + v3;
    }

    if (d2 > d1) {
        ipath = v1 + v2 + v3 + (d2 - d1);
        dpath = v1 + v3;
    }

    if (d1 == d2) {
        dpath = v1 + v3 + (d1 + d2);
        ipath = v1 + v2 + v3 + (d1 + d2);
    }


    if (dpath > ipath) {
        if (dpath > 30) {
            printf("Caminho: direto. Xupenio aprova! Nível: ELITE.\n");
        } else if (dpath >= 10 && dpath <= 30) {
            printf("Caminho: direto. Boa caminhada! Nível: SÓLIDO.\n");
        } else if (dpath >= 0 && dpath <= 9) {
            printf("Caminho: direto. Passou por pouco. Nível: BÁSICO.\n");
        } else if (dpath < 0) {
            printf("Caminho: direto. Xupenio reprova. Nível: CRÍTICO.\n");
        }
    } else if (dpath == ipath) {
        if (ipath > 30) {
            printf("Caminho: P2. Xupenio aprova! Nível: ELITE.\n");
        } else if (ipath >= 10 && ipath <= 30) {
            printf("Caminho: P2. Boa caminhada! Nível: SÓLIDO.\n");
        } else if (ipath >= 0 && ipath <= 9) {
            printf("Caminho: P2. Passou por pouco. Nível: BÁSICO.\n");
        } else if (ipath < 0) {
            printf("Caminho: P2. Xupenio reprova. Nível: CRÍTICO.\n");
        } 
    } else if (ipath > dpath) {
        if (ipath > 30) {
            printf("Caminho: P2. Xupenio aprova! Nível: ELITE.\n");
        } else if (ipath >= 10 && ipath <= 30) {
            printf("Caminho: P2. Boa caminhada! Nível: SÓLIDO.\n");
        } else if (ipath >= 0 && ipath <= 9) {
            printf("Caminho: P2. Passou por pouco. Nível: BÁSICO.\n");
        } else if (ipath < 0) {
            printf("Caminho: P2. Xupenio reprova. Nível: CRÍTICO.\n");
        }
    }

    return 0;
}
