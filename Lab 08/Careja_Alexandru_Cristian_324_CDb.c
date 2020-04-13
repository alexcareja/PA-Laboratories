#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void print_queue(Queue *);

char get_char(int );

void sortare_topologica();

void explorare(int , int *, int *, int *, char *, Queue **);

void componente_tare_conexe();

void construieste_ctc(Queue **, int, int *, char *);

int main() {
	sortare_topologica();
	componente_tare_conexe();
	return 0;
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
	char x = 'a';
	while(n > 0) {
		n--;
		x++;
	}
	return x;
}

void sortare_topologica() {
	/*
	Codific camasa->a, cravata->b, ....
	*/
	Queue **vector_adiacenta = (Queue **) malloc(7 * sizeof(Queue *));
	int i, j, dimensiune;
	dimensiune = 7;
	for(i = 0; i < 7; i++) {
		vector_adiacenta[i] = createQueue();
	}
	// adaugarea arcelor din graful orientat
	enqueue(vector_adiacenta[0], 6); // a->g
	enqueue(vector_adiacenta[0], 3); // a->d
	enqueue(vector_adiacenta[0], 1); // a->b
	enqueue(vector_adiacenta[1], 6); // b->g
	enqueue(vector_adiacenta[3], 4); // d->e
	enqueue(vector_adiacenta[5], 4); // f->e
	enqueue(vector_adiacenta[6], 2); // g->c

	printf("Exercitiul 2: Sortare topologica (ordine invers alfabetica)\n\nDFS:\n");
	// alocare dinamica vectori ce urmeaza a fi folsiti
	int *d = (int *) malloc(dimensiune * sizeof(int)); // momentul descoperirii
	int *f = (int *) malloc(dimensiune * sizeof(int)); // momentul terminarii explorarii din nodul curent
	char *c = (char *) malloc(dimensiune * sizeof(char)); // culori: a = alb, g = gri, n = negru
	int current, succesor;
	for(i = 0; i < dimensiune; i++) {
		c[i] = 'a'; // initial toate nodurile sunt albe
	}
	int timp = 0; // variabila pentru moment
	for(i = dimensiune - 1; i >= 0; i--) { // incercam sa parcurgem DFS din orice surse posibile
		if (c[i] == 'a') { // daca nodul i nu este explorat, atunci inseaman ca este sursa si il explorez
			explorare(i, &timp, d, f, c, vector_adiacenta);
		}
	}
	int *l = (int *) malloc(7 * sizeof(int)); // vector cu indicele nodurilor pe care il sortez
	int x; // folosit pentru interschimbare
	for (i = 0; i < dimensiune; i++) {
		l[i] = i;
	}
	for (i = 0; i < dimensiune; i++) { // bubble sort pentru timpii de finalizare respectiv cu indicii nodurilor
		for (j = i + 1; j < dimensiune; j++) {
			if(f[j] > f[i]) {
				x = l[j]; // interschimba l[i] l[j]
				l[j] = l[i];
				l[i] = x;
				x = f[j]; // interschimba f[i] f[j]
				f[j] = f[i];
				f[i] = x;
			}
		}
	}
	printf("\nOrdine topologica: ");
	for(i = 0; i < dimensiune; i++) { // afisare
		printf("%c ", get_char(l[i]));
		destroyQueue(vector_adiacenta[i]);
	}
	printf("\n\n");
	free(vector_adiacenta);
}

void explorare(int current, int *timp, int *d, int *f, char *c, Queue **vector_adiacenta) {
	int succesor;
	char litera = get_char(current); // litera nodului curent
	*timp = *timp + 1; // incrementare timp
	d[current] = *timp; 
	c[current] = 'g'; // nod in curs de vizitare => gri
	printf("%d: c(%c) = gri, d(%c) = %d\n", *timp, litera, litera, *timp);
	Queue *q = vector_adiacenta[current]; // lista de adiacenta a nodului curent
	while (!isQueueEmpty(q)) { // pentru fiecare vecin
		succesor = front(q);
		dequeue(q);
		if (c[succesor] == 'a') { // daca nu este vizitat, il vizitez acum
			explorare(succesor, timp, d, f, c, vector_adiacenta);
		}
	}
	c[current] = 'n'; // schimba culoarea
	*timp = *timp + 1; // incrementeaza timpul
	f[current] = *timp; 
	printf("%d: c(%c) = negru, f(%c) = %d\n", *timp, litera, litera, *timp);
}

void componente_tare_conexe() {
	printf("\nExercitiul 4: Componente tare conexe\n\n");
	int i, j, dimensiune = 16;
	Queue **vector_adiacenta = (Queue **) malloc(dimensiune * sizeof(Queue *));
	for(i = 0; i < dimensiune; i++) {
		vector_adiacenta[i] = createQueue();
	}
	// adaugarea arcelor din graful orientat
	enqueue(vector_adiacenta[0], 1); // a->b
	enqueue(vector_adiacenta[0], 6); // a->g
	enqueue(vector_adiacenta[1], 2); // b->c
	enqueue(vector_adiacenta[1], 6); // b->g
	enqueue(vector_adiacenta[2], 4); // c->e
	enqueue(vector_adiacenta[3], 2); // d->c
	enqueue(vector_adiacenta[3], 5); // d->f
	enqueue(vector_adiacenta[4], 3); // e->d
	enqueue(vector_adiacenta[6], 7); // g->h
	enqueue(vector_adiacenta[8], 0); // i->a
	enqueue(vector_adiacenta[8], 9); // i->j
	enqueue(vector_adiacenta[8], 11); // i->l
	enqueue(vector_adiacenta[9], 10); // j->k
	enqueue(vector_adiacenta[10], 8); // k->i
	enqueue(vector_adiacenta[10], 13); // k->m
	enqueue(vector_adiacenta[11], 10); // l->k
	enqueue(vector_adiacenta[12], 13); // m->n
	enqueue(vector_adiacenta[13], 14); // n->o
	enqueue(vector_adiacenta[14], 12); // o->m
	enqueue(vector_adiacenta[14], 15); // o->p
	// alocare dinamica vectori ce urmeaza a fi folsiti
	int *d = (int *) malloc(dimensiune * sizeof(int)); // momentul descoperirii
	int *f = (int *) malloc(dimensiune * sizeof(int)); // momentul terminarii explorarii din nodul curent
	char *c = (char *) malloc(dimensiune * sizeof(char)); // culori: a = alb, g = gri, n = negru
	int current, succesor;
	for(i = 0; i < dimensiune; i++) {
		c[i] = 'a'; // initial toate nodurile sunt albe
	}
	int timp = 0; // variabila pentru moment
	for(i = 0; i < dimensiune; i++) { // incercam sa parcurgem DFS din orice surse posibile
		if (c[i] == 'a') { // daca nodul i nu este explorat, atunci inseaman ca este sursa si il explorez
			explorare(i, &timp, d, f, c, vector_adiacenta);
		}
	}
	int *l = (int *) malloc(dimensiune * sizeof(int)); // vector cu indicele nodurilor pe care il sortez
	int x; // folosit pentru interschimbare
	for (i = 0; i < dimensiune; i++) {
		l[i] = i;
	}
	for (i = 0; i < dimensiune; i++) { // bubble sort pentru timpii de finalizare respectiv cu indicii nodurilor
		for (j = i + 1; j < dimensiune; j++) {
			if(f[j] > f[i]) {
				x = l[j]; // interschimba l[i] l[j]
				l[j] = l[i];
				l[i] = x;
				x = f[j]; // interschimba f[i] f[j]
				f[j] = f[i];
				f[i] = x;
			}
		}
	}
	// Rescriu listele initiale de adiacenta. Urmeaza sa transpun graful
	enqueue(vector_adiacenta[0], 1); // a->b
	enqueue(vector_adiacenta[0], 6); // a->g
	enqueue(vector_adiacenta[1], 2); // b->c
	enqueue(vector_adiacenta[1], 6); // b->g
	enqueue(vector_adiacenta[2], 4); // c->e
	enqueue(vector_adiacenta[3], 2); // d->c
	enqueue(vector_adiacenta[3], 5); // d->f
	enqueue(vector_adiacenta[4], 3); // e->d
	enqueue(vector_adiacenta[6], 7); // g->h
	enqueue(vector_adiacenta[8], 0); // i->a
	enqueue(vector_adiacenta[8], 9); // i->j
	enqueue(vector_adiacenta[8], 11); // i->l
	enqueue(vector_adiacenta[9], 10); // j->k
	enqueue(vector_adiacenta[10], 8); // k->i
	enqueue(vector_adiacenta[10], 13); // k->m
	enqueue(vector_adiacenta[11], 10); // l->k
	enqueue(vector_adiacenta[12], 13); // m->n
	enqueue(vector_adiacenta[13], 14); // n->o
	enqueue(vector_adiacenta[14], 12); // o->m
	enqueue(vector_adiacenta[14], 15); // o->p
	int index;
	Queue **transpus = (Queue **) malloc(dimensiune * sizeof(Queue *));
	for(i = 0; i < dimensiune; i++) {
		transpus[i] = createQueue();
		c[i] = 'a';
	}
	printf("Transpun graful\n");
	// transpun graful si tin cont de ordinea topologica in inserarea arcelor
	for (i = 0; i < dimensiune; i++) {
		index = l[i];
		while(!isQueueEmpty(vector_adiacenta[index])) {
			x = front(vector_adiacenta[index]);
			dequeue(vector_adiacenta[index]);
			enqueue(transpus[x], index); // x->index (inainte arcul era index->x)
		}
	}
	for(i = 0, j = 0; i < dimensiune; i++) { // incercam sa parcurgem DFS din orice surse posibile
		index = l[i];
		if (c[index] == 'a') { // daca nodul i nu este explorat, atunci inseaman ca este sursa si il explorez
			printf("Componenta tare conexa %d :", ++j);
			construieste_ctc(transpus, index, l, c);
			printf("\n");
		}
	}
	
}

void construieste_ctc(Queue **transpus, int index, int *l, char *c) {
	printf(" %c", get_char(index));
	int succesor;
	char litera = get_char(index); // litera nodului curent
	c[index] = 'g'; // nod in curs de vizitare => gri
	Queue *q = transpus[index]; // lista de adiacenta a nodului curent
	while (!isQueueEmpty(q)) { // pentru fiecare vecin
		succesor = front(q);
		dequeue(q);
		if (c[succesor] == 'a') { // daca nu este vizitat, il vizitez acum
			construieste_ctc(transpus, succesor, l, c);
		}
	}
	c[index] = 'n'; // schimba culoarea
}