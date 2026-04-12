#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fuse_elements(char *str) {
    int fusion_occurred = 1;
    
    while (fusion_occurred) {
        fusion_occurred = 0;
        int i = 0;
        
        while (str[i] != '\0' && str[i + 1] != '\0') {
            if (str[i] == str[i + 1]) {
                if (str[i] == 'z') {
                    str[i] = 'a';
                } else {
                    str[i] = str[i] + 1;
                }

                int j = i + 1;
                while (str[j] != '\0') {
                    str[j] = str[j + 1];
                    j++;
                }

                fusion_occurred = 1;
                i++; 
            } else {
                i++;
            }
        }
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int *lengths = (int *)malloc(n * sizeof(int));
    int *offsets = (int *)malloc(n * sizeof(int));
    char *data_storage = NULL;

    if (lengths == NULL || offsets == NULL) return 1;

    int total_chars = 0;
    int max_length = 0;
    int current_offset = 0;

    for (int i = 0; i < n; i++) {
        char buffer[1001];
        scanf("%s", buffer);
        int len = (int)strlen(buffer);

        lengths[i] = len;
        offsets[i] = current_offset;

        if (len > max_length) {
            max_length = len;
        }

        char *temp_ptr = (char *)realloc(data_storage, current_offset + len + 1);
        if (temp_ptr == NULL) {
            free(lengths);
            free(offsets);
            free(data_storage);
            return 1;
        }
        data_storage = temp_ptr;

        for (int j = 0; j < len; j++) {
            data_storage[current_offset + j] = buffer[j];
        }
        
        current_offset += len;
        total_chars += len;
    }

    char *merged_string = (char *)malloc((total_chars + 1) * sizeof(char));
    if (merged_string == NULL) return 1;

    int k = 0;
    for (int i = 0; i < max_length; i++) {
        for (int j = 0; j < n; j++) {
            if (i < lengths[j]) {
                merged_string[k++] = data_storage[offsets[j] + i];
            }
        }
    }
    merged_string[k] = '\0';

    printf("%s\n", merged_string);

    fuse_elements(merged_string);

    printf("%s\n", merged_string);

    free(lengths);
    free(offsets);
    free(data_storage);
    free(merged_string);

    return 0;
}
