#include <stdio.h>
#include <stdlib.h>

int main(void) {

    int x, y, qNow, qAvoid, dx, dy, tx, ty;

    scanf("%d %d %d", &x, &y, &qAvoid);

    if (x > 0 && y > 0) {qNow = 1;}
    if (x < 0 && y > 0) {qNow = 2;}
    if (x < 0 && y < 0) {qNow = 3;}
    if (x > 0 && y < 0) {qNow = 4;}

    if (qNow == 1) {tx = -1; ty = -1;} // q1 -> q3
    if (qNow == 2) {tx = 1;  ty = -1;} // q2 -> q4
    if (qNow == 3) {tx = 1;  ty = 1;}  // q3 -> q1
    if (qNow == 4) {tx = -1; ty = 1;}  // q4 -> q2

    dx = abs(tx - x);
    dy = abs(ty - y);

    // q1 -> q3
    if (qNow == 1 && qAvoid == 2) {
        printf("dy = %d\ndx = %d\n", dy, dx);
    }
    if (qNow == 1 && qAvoid == 4) {
        printf("dx = %d\ndy = %d\n", dx, dy);
    }

    // q2 -> q4
    if (qNow == 2 && qAvoid == 3) {
        printf("dx = %d\ndy = %d\n", dx, dy);
    }
    if (qNow == 2 && qAvoid == 1) {
        printf("dy = %d\ndx = %d\n", dy, dx);
    }

    // q3 -> q1
    if (qNow == 3 && qAvoid == 4) {
        printf("dy = %d\ndx = %d\n", dy, dx);
    }
    if (qNow == 3 && qAvoid == 2) {
        printf("dx = %d\ndy = %d\n", dx, dy);
    }

    // q4 -> q2
    if (qNow == 4 && qAvoid == 1) {
        printf("dx = %d\ndy = %d\n", dx, dy);
    }
    if (qNow == 4 && qAvoid == 3) {
        printf("dy = %d\ndx = %d\n", dy, dx);
    }

    if (qNow == qAvoid) {
        printf("caminhada invalida\n");
        return 1;
    }

    return 0;
}
