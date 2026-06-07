#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// struct para o conteudo de cada nó
typedef struct Student {
    long long matriculation;
    int priority;
    float cr;
    int arrivalTime;
    int timeoutTime;
    int score;
} Student;
// struct para os nós de fato
typedef struct Node {
    Student data;
    struct Node *next;
} Node;
// struct com ponteiros pro inicio e pro fim da fila
typedef struct Queue {
    Node *front;
    Node *rear;
} Queue;
// inicializar a fila
void initQueue(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
}
// verificar se a fila ta vazia
int isEmpty(Queue *q) {
    if (q->front == NULL) {
        return 1;
    }
    return 0;
}
// colocar um novo nó na fila
void enqueue(Queue *q, Student s) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        return;
    }
    newNode->data = s;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } 
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}
// tirar um estudante da fila
Student dequeue(Queue *q) {
    if (isEmpty(q)) {
        Student empty = {0};
        return empty;
    }

    Node *temp = q->front;
    Student s = temp->data;

    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return s;
}
// calcular o score do aluno
int calculateScore(float cr, int priority) {
    int roundedCr = (int)round(cr * 100);
    return roundedCr / priority;
}
// chamando as funções
int main() {
    char command[10];
    char subjectName[51];
    int vacancies = 0;
    int serverTime = 1;

    Queue requestQueue;
    Queue confirmedQueue;

    initQueue(&requestQueue);
    initQueue(&confirmedQueue);

    while (scanf("%s", command) != EOF) {
        if (strcmp(command, "START") == 0) {
            scanf("%s %d", subjectName, &vacancies);
        } 
        else if (strcmp(command, "ADD") == 0) {
            Student s;
            scanf("%lld %d %f %d %d", &s.matriculation, &s.priority, &s.cr, &s.arrivalTime, &s.timeoutTime);
            s.score = calculateScore(s.cr, s.priority);
            enqueue(&requestQueue, s);
        } 
        else if (strcmp(command, "PROC") == 0) {
            int qtd;
            scanf("%d", &qtd);

            int processedCount = 0;
            while (processedCount < qtd && !isEmpty(&requestQueue)) {
                Student current = requestQueue.front->data;
                
                if (serverTime < current.arrivalTime) {
                    serverTime = current.arrivalTime;
                }

                if (serverTime > current.timeoutTime) {
                    printf("[TIMEOUT] mat=%lld | Desconectado da fila.\n", current.matriculation);
                    dequeue(&requestQueue);
                } 
                else {
                    dequeue(&requestQueue);

                    if (vacancies > 0) {
                        printf("[ALOCADO] mat=%lld | score=%d | Processado no seg: %d\n", 
                               current.matriculation, current.score, serverTime);
                        enqueue(&confirmedQueue, current);
                        vacancies--;
                    } 
                    else {
                        printf("[LOTADO] mat=%lld | score=%d | Processado no seg: %d\n", 
                               current.matriculation, current.score, serverTime);
                    }
                    
                    serverTime++;
                    processedCount++;
                }
            }
        } 
        else if (strcmp(command, "FIM") == 0) {
            printf("--- LISTA OFICIAL: %s ---\n", subjectName);
            int position = 1;
            while (!isEmpty(&confirmedQueue)) {
                Student s = dequeue(&confirmedQueue);
                printf("%d. Matricula: %lld\n", position, s.matriculation);
                position++;
            }
            break;
        }
    }

    return 0;
}
