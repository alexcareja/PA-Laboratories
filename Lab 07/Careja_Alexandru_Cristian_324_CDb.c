#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode{
	char elem;
	struct QueueNode *next;
}QueueNode;

typedef struct Queue{
	QueueNode *front;
	QueueNode *rear;
	int size;
}Queue;

Queue* createQueue(void){
	Queue *q = (Queue *) malloc(sizeof(Queue));
	q->front = NULL;
	q->rear = NULL;
	q->size = 0; 
	return q;
} 

int isQueueEmpty(Queue *q){
	if (q->front == NULL) {
		return 1;
	}
	return 0;
}

void enqueue(Queue *q, char elem){
	q->size += 1;
	QueueNode *node = (QueueNode *) malloc(sizeof(QueueNode));
	node->elem = elem;
	node->next = NULL;
	if (isQueueEmpty(q)) {
		q->front = node;
		q->rear = node;
		return;
	}
	q->rear->next = node;
	q->rear = node;
}

char front(Queue* q){
	return q->front->elem;
}

void dequeue(Queue* q){
	if (isQueueEmpty(q)) {
		return;
	}
	q->size -= 1;
	QueueNode *aux = q->front;
	q->front = q->front->next;
	if (q->front == NULL) {
		q->rear = NULL;
	}
	free(aux);
}



void destroyQueue(Queue *q){
	while(!isQueueEmpty) {
		dequeue(q);
	}
	free(q);
}

int main() {

	return 0;
}