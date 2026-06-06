#include <stdio.h>
#include <stdlib.h>
// struct para os elementos da fila, atenção pra prioridade
typedef struct Task {
    int id;
    int priority;
    struct Task *next;
} Task;
// struct com ponteiros para o inicio e para o final da fila
typedef struct {
    Task *head;
    Task *tail;
} Queue;
// zerar a fila, zerando o inicio e o fim
void initQueue(Queue *q) {
    q->head = NULL;
    q->tail = NULL;
}
// função enqueue para enfileirar um nó
void insertTask(Queue *q, int id, int priority) {
    Task *newTask = (Task *) malloc(sizeof(Task));
    
    if (newTask == NULL) {
        exit(1);
    }
    
    newTask->id = id;
    newTask->priority = priority;
    newTask->next = NULL;
    // checa se a fila esta vaia
    if (q->tail == NULL) {
        q->head = newTask;
        q->tail = newTask;
    } else {
        q->tail->next = newTask;
        q->tail = newTask;
    }
}
// função dequeue para tirar o primeiro nó da fila
void removeTask(Queue *q) {
    if (q->head == NULL) {
        printf("Fila vazia\n");
        return;
    }
    Task *removedTask = q->head;
    printf("Removida: id=%d prioridade=%d\n", removedTask->id, removedTask->priority);
    q->head = q->head->next;
    
    if (q->head == NULL) {
        q->tail = NULL;
    }
    free(removedTask);
}
// printar a fila
void listTasks(Queue *q) {
    if (q->head == NULL) {
        printf("Fila vazia\n");
    }
    Task *current = q->head;
    while (current != NULL) {
        printf("id=%d prioridade=%d\n", current->id, current->priority);
        current = current->next;
    }
}
// limpar a fila
void clearQueue(Queue *q) {
    while (q->head != NULL) {
        Task *temp = q->head;
        q->head = q->head->next;
        free(temp);
    }
}
// chamando todas as funções
int main() {
    char command;
    int id, priority;
    Queue taskQueue;
    initQueue(&taskQueue);
    
    while (scanf(" %c", &command) != EOF) {
        if (command == 'F') {
            break;
        } else if (command == 'I') {
            scanf("%d %d", &id, &priority);
            insertTask(&taskQueue, id, priority);
        } else if (command == 'R') {
            removeTask(&taskQueue);
        } else if (command == 'L') {
            listTasks(&taskQueue);
        }
    }
    clearQueue(&taskQueue);
    
    return 0;
}
