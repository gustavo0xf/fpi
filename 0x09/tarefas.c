#include <stdio.h>
#include <stdlib.h>

typedef struct Task {
    int id;
    int priority;
    struct Task *next;
} Task;

typedef struct {
    Task *head;
    Task *tail;
} Queue;

void initQueue(Queue *q) {
    q->head = NULL;
    q->tail = NULL;
}

void insertTask(Queue *q, int id, int priority) {
    Task *newTask = (Task *)malloc(sizeof(Task));
    if (newTask == NULL) {
        return;
    }
    
    newTask->id = id;
    newTask->priority = priority;
    newTask->next = NULL;
    
    if (q->tail == NULL) {
        q->head = newTask;
        q->tail = newTask;
    } else {
        q->tail->next = newTask;
        q->tail = newTask;
    }
}

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

void listTasks(Queue *q) {
    if (q->head == NULL) {
        printf("Fila vazia\n");
        return;
    }
    
    Task *current = q->head;
    while (current != NULL) {
        printf("id=%d prioridade=%d\n", current->id, current->priority);
        current = current->next;
    }
}

void clearQueue(Queue *q) {
    while (q->head != NULL) {
        Task *temp = q->head;
        q->head = q->head->next;
        free(temp);
    }
}

int main() {
    Queue taskQueue;
    initQueue(&taskQueue);
    
    char command;
    int id, priority;

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
