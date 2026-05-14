#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FORi(n) for (int i = 0; i < n; i++)
#define FORj(n) for (int j = 0; j < n; j++)
#define FORk(n) for (int k = 1; k <= n; k++)

typedef struct {
    double sepal_length;
    double sepal_width;
    double petal_length;
    double petal_width;
    char species[30];
} IrisRecord;

IrisRecord* addRecord(IrisRecord *records, int *count, IrisRecord record) {
    (*count)++;
    IrisRecord *tmp = (IrisRecord *) realloc(records, (*count) * sizeof(IrisRecord));
    if (tmp == NULL) {
        free(records);
        exit(1);
    }
    tmp[(*count) - 1] = record;
    return tmp;
}
// calcular media arimetica
void evalAvg(IrisRecord *records, int count, double *results) {
    double sums[4] = {0.0, 0.0, 0.0, 0.0};

    FORi(count) {
        sums[0] += records[i].sepal_length;
        sums[1] += records[i].sepal_width;
        sums[2] += records[i].petal_length;
        sums[3] += records[i].petal_width;
    }

    FORi(4) {
        results[i] = sums[i] / count;
    }
}
// calcular a moda
void evalMode(IrisRecord *records, int count, char *mode) {
    int mfreq = 0;

    FORi(count) {
        int cfreq = 0;
        FORj(count) {
            if (strcmp(records[i].species, records[j].species) == 0) {
                cfreq++;
            }
        }

        if (cfreq > mfreq) {
            mfreq = cfreq;
            strcpy(mode, records[i].species);
        } else if (cfreq == mfreq) {
            if (strcmp(records[i].species, mode) < 0) {
                strcpy(mode, records[i].species);
            }
        }
    }
}

void processFile(const char *filename) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        return;
    }

    IrisRecord *records = NULL;
    int count = 0;
    char header[128];

    if (fscanf(file, "%127s", header) != 1) {
        fclose(file);
        return;
    }

    IrisRecord tmp;
    while (fscanf(file, " %lf,%lf,%lf,%lf,%29[^ \n]", &tmp.sepal_length, &tmp.sepal_width, &tmp.petal_length, &tmp.petal_width, tmp.species) == 5) {
        records = addRecord(records, &count, tmp);
    }

    if (count > 0) {
        double avg[4];
        char mode[30];

        evalAvg(records, count, avg);
        evalMode(records, count, mode);

        printf("\nfile: %s\n%s\n", filename, header);
        FORi(count) {
            printf("%.1f,%.1f,%.1f,%.1f,%s\n", records[i].sepal_length, records[i].sepal_width, records[i].petal_length, records[i].petal_width, records[i].species);
        }

        fprintf(file, "average: %.2f, %.2f, %.2f, %.2f\n", avg[0], avg[1], avg[2], avg[3]);
        fprintf(file, "mode: %s\n", mode);
    }

    free(records);
    fclose(file);
}

int main() {
    int total;
    scanf("%d", &total);

    FORk(total) {
        char filename[32];
        sprintf(filename, "iris%d.csv", k);
        processFile(filename);
    }

    return 0;
}
