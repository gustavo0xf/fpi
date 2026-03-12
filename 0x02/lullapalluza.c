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

/*
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int number, channels, v1, v2, f_prev, f_current, f_next;

    int global_min_distance = -1;
    int best_channel = -1;
    int best_minute = -1;
    int best_term_overall = -1;

    scanf("%d %d", &number, &channels);

    for (int i = 0; i < channels; i++) {
        scanf("%d %d", &v1, &v2);

        int current_distance;
        int current_best_minute;
        int current_best_term;

        current_distance = abs(number - v1);
        current_best_minute = 1;
        current_best_term = v1;

        int d2 = abs(number - v2);
        if (d2 < current_distance || (d2 == current_distance && v2 < current_best_term)) {
            current_distance = d2;
            current_best_minute = 2;
            current_best_term = v2;
        }

        f_prev = v1;
        f_current = v2;
        for (int j = 3; j <= 60; j++) {
            f_next = f_current + f_prev;
            f_prev = f_current;
            f_current = f_next;

            int actual_distance = abs(number - f_next);

            if (actual_distance < current_distance || (actual_distance == current_distance && f_next < current_best_term)) {
                current_distance = actual_distance;
                current_best_minute = j;
                current_best_term = f_next;
            }
        }

        int channel_idx = i + 1;
        if (global_min_distance == -1 || current_distance < global_min_distance || (current_distance == global_min_distance && channel_idx > best_channel)) {
            global_min_distance = current_distance;
            best_channel = channel_idx;
            best_minute = current_best_minute;
            best_term_overall = current_best_term;
        }
    }

    int sum_digits = 0;
    long long temp = abs(best_term_overall);
    while (temp > 0) {
        sum_digits += (int)(temp % 10);
        temp /= 10;
    }

    if (sum_digits > 10) {
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d e com o VIP garantido!!!\n", best_channel, best_minute);
    } else {
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d, mas o ingresso VIP não vai rolar :(\n", best_channel, best_minute);
    }

    return 0;
}
*/
