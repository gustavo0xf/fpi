#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void) {

    int day1, day2, month1, month2, year1, year2, sum, sum2, love, work, color, luck;
    scanf("%d/%d/%d %d/%d/%d", &day1, &month1, &year1, &day2, &month2, &year2);

    sum  = day1 + month1 + year1 + day2 + month2 + year2;
    sum2 = (day1 * day1) + (day2 * day2) + (month1 * month1) + (month2 * month2) + (year1 * year1) + (year2 * year2);
    luck = (9*(day1 + day2 + month1 + month2) + abs(year2 - year1)) % 101;
    love = (sum * 7) % 101;
    work = ((year1 + year2) - 8*(day1 + day2 + month1 + month2)) % 101;
    color = sum2 % 11;

    printf("%d\n", love);
    printf("%d\n", luck);
    printf("%d\n", work);

    if (love < 20) {
        printf("Amor: %d Pessimo dia para se apaixonar.\n", love);
    } 
    if (love > 20 && love < 40) {
        printf("Amor: %d Melhor manter o coracao <3 longe de perigo.\n", love);
    } 
    if (love >= 40 && love < 69) {
        printf("Amor: %d Se o papo e as ideias baterem, esta liberado pensar em algo.\n", love);
    } 
    if (love > 70 && love < 80) {
        printf("Amor: %d Saia com o coracao aberto, mas lembre, nem toda troca de olhar em onibus e sinal de romance.\n", love);
    } 
    if (love > 80) {
        printf("Amor: %d Um dia deslumbrantemente lindo para amar. Ps: Cuidado com a intensidade.\n", love);
    } 
    if (luck < 30) {
        printf("Sorte: %d Nem jogue moedas pra cima hoje. Sem tigrinho nem jogos de azar, por favor!\n", luck);
    } 
    if (luck > 30 && luck < 50) {
        printf("Sorte: %d Melhor nao arriscar. Sem tigrinho nem jogos de azar, por favor!\n", luck);
    } 
    if (luck > 51 && luck < 79) {
        printf("Sorte: %d Por sua conta em risco. Sem tigrinho nem jogos de azar, por favor!\n", luck);
    } 
    if (luck > 80 && luck < 90) {
        printf("Sorte: %d Hoje vale a pena arriscar. Sem tigrinho nem jogos de azar, por favor!\n", luck);
    } 
    if (luck >= 90) {
        printf("Sorte: %d Nao tenha medo de virar cartas hoje. Sem tigrinho nem jogos de azar, por favor!\n", luck);
    } 
    if (work < 40) {
        printf("Trabalho: %d Hoje nao sera um dia tao proveitoso, keep calm e faca o basico.\n", work);
    } 
    if (work > 40 && work < 50) {
        printf("Trabalho: %d Segura a emocao, nao xinga ninguem, nao esquece de beber agua.\n", work);
    } 
    if (work > 51 && work < 69) {
        printf("Trabalho: %d Um dia proveitoso com certeza, leve sua simpatia consigo.\n", work);
    } 
    if (work >= 70 && work < 84) {
        printf("Trabalho: %d Boas vibracoes hoje, chances podem estar ao seu redor.\n", work);
    } 
    if (work > 85) {
        printf("Trabalho: %d Use do maximo de networking possÃ­vel hoje, dia bom para negocios.\n", work);
    }

    switch (color) {
        case 0:
            printf("Cor: Cinza\n");
            break;
        case 1:
            printf("Cor: Vermelho\n");
            break;
        case 2:
            printf("Cor: Laranja\n");
            break;
        case 3:
            printf("Cor: Amarelo\n");
            break;
        case 4:
            printf("Cor: Verde\n");
            break;
        case 5:
            printf("Cor: Azul\n");
            break;
        case 6:
            printf("Cor: Roxo\n");
            break;
        case 7:
            printf("Cor: Marrom\n");
            break;
        case 8:
            printf("Cor: Rosa\n");
            break;
        case 9:
            printf("Cor: Preto\n");
            break;
        case 10:
            printf("Cor: Branco\n");
            break;
        default:
            break;
    }

    return 0;
}
