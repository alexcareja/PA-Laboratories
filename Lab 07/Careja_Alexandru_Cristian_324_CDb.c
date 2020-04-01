#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode{
	int elem;
	struct QueueNode *next;
}QueueNode; // tipul de data nod dintr-o coada

typedef struct Queue{
	QueueNode *front;
	QueueNode *rear;
	int size;
}Queue; // tipul de data coada

Queue* createQueue(void){ // crearea unei cozi vide
	Queue *q = (Queue *) malloc(sizeof(Queue));
	q->front = NULL;
	q->rear = NULL;
	q->size = 0; 
	return q;
} 

int isQueueEmpty(Queue *q){ // verificare coada goala
	if (q->front == NULL) {
		return 1;
	}
	return 0;
}

void enqueue(Queue *q, int elem){ // inscriere in coada
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

int front(Queue* q){ // vezi primul element din coada
	return q->front->elem;
}

void dequeue(Queue* q){ // scoate primul element din coada
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



void destroyQueue(Queue *q){ // distruge coada
	while(!isQueueEmpty) {
		dequeue(q);
	}
	free(q);
}

void BFS();

void print_queue(Queue *);

char get_char(int );

void DFS();

void explorare(int , int *, int *, int *, int *, int *, Queue **);

int main() {
	BFS();
	DFS();
	return 0;
}

void BFS() {
	/*
	Codific A = 0, B = 1, C = 2 .. J = 9, si pentru afiasre folosesc o functie de parsare a numarului in litera corespunzatoare
	*/
	Queue **vector_adiacenta = (Queue **) malloc(10 * sizeof(Queue *));
	int i, dimensiune;
	dimensiune = 10;
	for(i = 0; i < 10; i++) {
		vector_adiacenta[i] = createQueue();
	}
	// adaugarea arcelor din graful orientat
	enqueue(vector_adiacenta[0], 1); // A->B
	enqueue(vector_adiacenta[0], 2); // A->C
	enqueue(vector_adiacenta[0], 7); // A->H
	enqueue(vector_adiacenta[1], 3); // B->D
	enqueue(vector_adiacenta[1], 4); // B->E
	enqueue(vector_adiacenta[1], 7); // B->H
	enqueue(vector_adiacenta[1], 8); // B->I
	enqueue(vector_adiacenta[2], 3); // C->D
	enqueue(vector_adiacenta[3], 4); // D->E
	enqueue(vector_adiacenta[3], 9); // D->J
	enqueue(vector_adiacenta[4], 5); // E->F
	enqueue(vector_adiacenta[4], 6); // E->G
	enqueue(vector_adiacenta[5], 6); // F->G
	enqueue(vector_adiacenta[7], 8); // H->I
	enqueue(vector_adiacenta[8], 0); // I->A

	printf("BFS:\n\n");
	int *d = (int *) malloc(dimensiune * sizeof(int)); // momentul descoperirii
	int *p = (int *) malloc(dimensiune * sizeof(int)); // parinti
	int *c = (int *) malloc(dimensiune * sizeof(int)); // culori: a = alb, g = gri, n = negru
	int pas, current, succesor;
	for(i = 0; i < dimensiune; i++) {
		c[i] = 'a'; // initial toate nodurile sunt albe
		p[i] = -1;
	}
	pas = 0;
	for(i = 0; i < dimensiune; i++) { // for noduri surse (in cazul din laborator, numai A este sursa)
		if(c[i] != 'a') { // daca nodul a fost deja vizitat (nu mai e alb), atunci nu poate fi sursa
			continue;
		}
		char litera = get_char(i);
		printf("Pasul %d: ", pas++);
		printf("d(%c) = 0, p(%c) = null, c(%c) = gri, Q = {%c}\n", litera, litera, litera, litera);
		Queue *q = createQueue();
		enqueue(q, i);
		c[i] = 'g';
		while(!isQueueEmpty(q)) { // cat tine coada nu este goala
			printf("Pasul %d: ", pas++);
			current = front(q);
			while(!isQueueEmpty(vector_adiacenta[current])) { // pentru fiecare succesor al lui current
				succesor = front(vector_adiacenta[current]);
				dequeue(vector_adiacenta[current]);
				if(c[succesor] == 'a') { // daca nodul nu este explorat
					litera = get_char(succesor);
					printf("d[%c] = %d, p[%c] = %c, c[%c] = gri, ", litera, d[current] + 1, litera, get_char(current), litera);
					d[succesor] = d[current] + 1;
					p[succesor] = current;
					c[succesor] = 'g';
					enqueue(q, succesor);
				}
			}
			dequeue(q);
			printf("c(%c) = negru, ", get_char(current));
			c[current] = 'n';
			printf("Q = ");
			print_queue(q);
			printf("\n");
		}
		
	}
	printf("\nREZULTAT FINAL:\n");
	for(i = 0; i < dimensiune; i++) {
		printf("%c: d = %d, p = %c\n",get_char(i), d[i], get_char(p[i]));
	}
	printf("\n\n");

	for(i = 0; i < 10; i++) {
		destroyQueue(vector_adiacenta[i]);
	}
	free(vector_adiacenta);
}

void print_queue(Queue * q) {
	QueueNode *aux = q->front;
	printf("{ ");
	while(aux != NULL) {
		printf("%c ", get_char(aux->elem));
		aux = aux->next;
	}
	printf("}");
}

char get_char(int n) {
	if (n == -1) {
		return 0;
	}
	char x = 'A';
	while(n > 0) {
		n--;
		x++;
	}
	return x;
}

void DFS() {
	/*
	Codific A = 0, B = 1, C = 2 .. J = 9, si pentru afiasre folosesc o functie de parsare a numarului in litera corespunzatoare
	*/
	Queue **vector_adiacenta = (Queue **) malloc(10 * sizeof(Queue *));
	int i, dimensiune;
	dimensiune = 10;
	for(i = 0; i < 10; i++) {
		vector_adiacenta[i] = createQueue();
	}
	// adaugarea arcelor din graful orientat
	enqueue(vector_adiacenta[0], 1); // A->B
	enqueue(vector_adiacenta[0], 2); // A->C
	enqueue(vector_adiacenta[0], 7); // A->H
	enqueue(vector_adiacenta[1], 3); // B->D
	enqueue(vector_adiacenta[1], 4); // B->E
	enqueue(vector_adiacenta[1], 7); // B->H
	enqueue(vector_adiacenta[1], 8); // B->I
	enqueue(vector_adiacenta[2], 3); // C->D
	enqueue(vector_adiacenta[3], 4); // D->E
	enqueue(vector_adiacenta[3], 9); // D->J
	enqueue(vector_adiacenta[4], 5); // E->F
	enqueue(vector_adiacenta[4], 6); // E->G
	enqueue(vector_adiacenta[5], 6); // F->G
	enqueue(vector_adiacenta[7], 8); // H->I
	enqueue(vector_adiacenta[8], 0); // I->A

	printf("BFS:\n\n");
	// alocare dinamica vectori ce urmeaza a fi folsiti
	int *d = (int *) malloc(dimensiune * sizeof(int)); // momentul descoperirii
	int *f = (int *) malloc(dimensiune * sizeof(int)); // momentul terminarii explorarii din nodul curent
	int *p = (int *) malloc(dimensiune * sizeof(int)); // parinti
	int *c = (int *) malloc(dimensiune * sizeof(int)); // culori: a = alb, g = gri, n = negru
	int current, succesor;
	for(i = 0; i < dimensiune; i++) {
		c[i] = 'a'; // initial toate nodurile sunt albe
		p[i] = -1; // nimeni nu are niciun parinte setat
	}
	int timp = 0; // variabila pentru moment
	for(i = 0; i < dimensiune; i++) { // incercam sa parcurgem DFS din orice surse posibile
		if (c[i] == 'a') { // daca nodul i nu este explorat, atunci inseaman ca este sursa si il explorez
			p[i] = -1; // nodul sursa nu are parinte
			explorare(i, &timp, d, f, p, c, vector_adiacenta);
		}
	}
	for(i = 0; i < 10; i++) {
		destroyQueue(vector_adiacenta[i]);
	}
	free(vector_adiacenta);
}

void explorare(int current, int *timp, int *d, int *f, int *p, int *c, Queue **vector_adiacenta) {
	int succesor;
	char litera = get_char(current); // litera nodului curent
	*timp = *timp + 1; // incrementare moment
	d[current] = *timp; 
	c[current] = 'g'; // nod in curs de vizitare => gri
	printf("%d: c(%c) = gri, d(%c) = %d, p(%c) = %c\n", *timp, litera, litera, *timp, litera, get_char(p[current]));
	Queue *q = vector_adiacenta[current]; // lista de adiacenta a nodului curent
	while (!isQueueEmpty(q)) { // pentru fiecare vecin
		succesor = front(q);
		dequeue(q);
		if (c[succesor] == 'a') { // daca nu este vizitat, il vizitez acum
			p[succesor] = current; // setez parinte
			explorare(succesor, timp, d, f, p, c, vector_adiacenta);
		}
	}
	c[current] = 'n';
	*timp = *timp + 1;
	f[current] = *timp;
	printf("%d: c(%c) = negru, f(%c) = %d\n", *timp, litera, litera, *timp);
}