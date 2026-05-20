#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// minhas macros. __VA_ARGS__ serve para trabalhar com um numero variavel de argumentos
#define FORi(n)                         for (int i = 0; i < n; i++)
#define FOR_READ(file_ptr, format, ...) for (; fscanf(file_ptr, format, __VA_ARGS__) == 4 ;)
#define FOR_MOVE(file_ptr, format, ...) for (; fscanf(file_ptr, format, __VA_ARGS__) == 3 ;)
#define FOR_LINE(file_ptr, line, size)  for (; fgets(line, size, file_ptr) != NULL ;)
// typedefs para a struct que define os produtos e para aque define os elementos do report
typedef struct {
    int id;
    char name[50];
    int quantity;
    double price;
} Product;

typedef struct {
    int productCount;
    int successfulMoves;
    int deniedOutputs;
    int unknownProducts;
} ReportStats;
// tratar erros na abertura de arquivos
FILE* handleFileErrors(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        printf("[!] failed to open file\n");
        exit(1);
    }
    return file;
}
// tratar erros de alocação de memória
void* handleMemoryErrors(void *allocatedPointer, void *oldPointerToFree) {
    if (allocatedPointer == NULL) {
        printf("[!] failed to allocate memory\n");
        if (oldPointerToFree != NULL) {
            free(oldPointerToFree);
        }
        exit(1);
    }
    return allocatedPointer;
}

Product* addProduct(Product *products, int *count, Product newProduct) {
    (*count)++;
    products = (Product *) handleMemoryErrors(realloc(products, (*count) * sizeof(Product)), products);
    products[(*count) - 1] = newProduct;
    return products;
}

int findProductIndex(Product *products, int count, int id) {
    FORi(count) {
        if (products[i].id == id) {
            return i;
        }
    }
    return -1;
}

Product* loadMasterFile(int *productCount) {
    FILE *fileProd = handleFileErrors("produtos.txt", "r");
    Product *products = NULL;
    Product tempProd;

    FOR_READ(fileProd, "%d %49s %d %lf", &tempProd.id, tempProd.name, &tempProd.quantity, &tempProd.price) {
        products = addProduct(products, productCount, tempProd);
    }

    fclose(fileProd);
    return products;
}

ReportStats processMovementsFile(Product *products, int productCount) {
    FILE *fileMov = handleFileErrors("movimentos.txt", "r");
    FILE *fileInc = handleFileErrors("temp_inc.txt", "w");

    ReportStats stats = {productCount, 0, 0, 0};

    int movId;
    char movType;
    int movQty;

    FOR_MOVE(fileMov, "%d %c %d", &movId, &movType, &movQty) {
        int index = findProductIndex(products, productCount, movId);

        if (index == -1) {
            stats.unknownProducts++;
            fprintf(fileInc, "%d %c %d PRODUTO_INEXISTENTE\n", movId, movType, movQty);
        } else {
            if (movType == 'E') {
                products[index].quantity += movQty;
                stats.successfulMoves++;
            } else if (movType == 'S') {
                if (products[index].quantity >= movQty) {
                    products[index].quantity -= movQty;
                    stats.successfulMoves++;
                } else {
                    stats.deniedOutputs++;
                    fprintf(fileInc, "%d %c %d ESTOQUE_INSUFICIENTE\n", movId, movType, movQty);
                }
            }
        }
    }

    fclose(fileMov);
    fclose(fileInc);
    return stats;
}

void writeUpdatedStock(Product *products, int productCount) {
    FILE *fileStock = handleFileErrors("estoque_atualizado.txt", "w");

    FORi(productCount) {
        fprintf(fileStock, "%d %s %d %.2f\n", products[i].id, products[i].name, products[i].quantity, products[i].price);
    }
    fclose(fileStock);
}

void appendInconsistencies(FILE *fileRep) {
    FILE *fileInc = handleFileErrors("temp_inc.txt", "r");

    char line[128];
    FOR_LINE(fileInc, line, sizeof(line)) {
        fprintf(fileRep, "%s", line);
    }

    fclose(fileInc);
    remove("temp_inc.txt");
}

void generateFinalReport(ReportStats stats, Product *products, int productCount) {
    FILE *fileRep = handleFileErrors("relatorio.txt", "w");

    fprintf(fileRep, "PRODUTOS PROCESSADOS: %d\n", stats.productCount);
    fprintf(fileRep, "MOVIMENTOS APLICADOS: %d\n", stats.successfulMoves);
    fprintf(fileRep, "SAIDAS RECUSADAS: %d\n", stats.deniedOutputs);
    fprintf(fileRep, "MOVIMENTOS SEM CADASTRO: %d\n", stats.unknownProducts);

    fprintf(fileRep, "ESTOQUE BAIXO:\n");
    FORi(productCount) {
        if (products[i].quantity <= 5) {
            fprintf(fileRep, "%d %s %d\n", products[i].id, products[i].name, products[i].quantity);
        }
    }

    fprintf(fileRep, "INCONSISTENCIAS:\n");
    appendInconsistencies(fileRep);

    fclose(fileRep);
}

int main() {
    int productCount = 0;
    Product *products = loadMasterFile(&productCount);

    if (products != NULL || productCount == 0) {
        ReportStats stats = processMovementsFile(products, productCount);
        writeUpdatedStock(products, productCount);
        generateFinalReport(stats, products, productCount);
        free(products);
    }

    return 0;
}
