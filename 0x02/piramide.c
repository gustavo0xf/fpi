#include <stdio.h>

int main(void) {

        char c;
        scanf("%c", &c);

        for (char now = 'A'; now <= c; now++) {

                for (char dot = 0; dot < (c - now); dot++) {
                        printf(".");
                }

                char init = 'A';

                for (char t = 'A'; t < now; t++) {
                        printf("%c", t);
                }

                for (int j = 0; now >= init; j++) {
                        init++;
                        printf("%c", now - j);
                }

                for (char dot = 0; dot < (c - now); dot++) {
                        printf(".");
                }

                printf("\n");

        }

        return 0;

}
