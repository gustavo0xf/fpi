#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void) {

        int number, channels, v1, v2;
        long long f_prev, f_current, f_next;

        scanf("%d %d", &number, &channels);

        for (int i = 0; i < channels; i++) {
                scanf("%d %d", &v1, &v2);
                f_prev = v1;
                f_current = v2;

                int minute = 1;
                long long distance = llabs(number - v1);

                for (int j = 3; j <= 60; j++) {
                        f_next = f_current + f_prev;
                        f_prev = f_current;
                        f_current = f_next;

                        long long actual_distance = llabs(number - f_next);

                        if (actual_distance < distance) {
                                distance = actual_distance;
                                minute = j;
                        }

                }

                printf("%d", minute);
        }


        return 0;
}
