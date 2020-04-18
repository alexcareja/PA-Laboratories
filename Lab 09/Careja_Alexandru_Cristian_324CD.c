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

void tarjan();

void explorare_t(int , int *, int *, int *, int *, int *, int *, char *, Queue **);

void punti();

void explorare_p(int , int *, int *, int *, int *, int **, int *, char *, Queue **);

int main() {
	tarjan();
	punti();
	return 0;
}

void tarjan() {
	Queue **vector_adiacenta = (Queue **) malloc(10 * sizeof(Queue *));
	int i, j, dimensiune;
	dimensiune = 10;
	for(i = 0; i < 10; i++) {
		vector_adiacenta[i] = createQueue();
	}
	// adaugarea arcelor din graful orientat
	enqueue(vector_adiacenta[0], 1); // 0-1
	enqueue(vector_adiacenta[0], 9); // 0-9
	enqueue(vector_adiacenta[1], 2); // 1-2
	enqueue(vector_adiacenta[2], 1); // 2-1
	enqueue(vector_adiacenta[1], 8); // 1-8
	enqueue(vector_adiacenta[8], 1); // 8-1
	enqueue(vector_adiacenta[2], 3); // 2-3
	enqueue(vector_adiacenta[3], 2); // 3-2
	enqueue(vector_adiacenta[2], 4); // 2-4
	enqueue(vector_adiacenta[4], 2); // 4-2
	enqueue(vector_adiacenta[2], 7); // 2-7
	enqueue(vector_adiacenta[7], 2); // 7-2
	enqueue(vector_adiacenta[3], 4); // 3-4
	enqueue(vector_adiacenta[4], 3); // 4-3
	enqueue(vector_adiacenta[3], 5); // 3-5
	enqueue(vector_adiacenta[5], 3); // 5-3
	enqueue(vector_adiacenta[5], 6); // 5-6
	enqueue(vector_adiacenta[6], 5); // 6-5
	enqueue(vector_adiacenta[7], 8); // 7-8
	enqueue(vector_adiacenta[8], 7); // 8-7

	printf("PUCNTE DE ARTICULATIE\n\nDFS:");
	// alocare dinamica vectori ce urmeaza a fi folsiti
	int *d = (int *) malloc(dimensiune * sizeof(int));  // momentul descoperirii
	int *low = (int *) malloc(dimensiune * sizeof(int));
	int *p = (int *) malloc(dimensiune * sizeof(int));  // vector de parinti
	int *subarb = (int *) malloc(dimensiune * sizeof(int));  // vector in care retin cati subarbori are un nod
	int *art = (int *) malloc(dimensiune * sizeof(int));  // vector in care retin daca nodul i e nod de articulatie
	char *c = (char *) malloc(dimensiune * sizeof(char));  // culori: a = alb, g = gri
	int current, succesor;
	for(i = 0; i < dimensiune; i++) {
		c[i] = 'a';  // initial toate nodurile sunt albe
		d[i] = 0;  // initial toate nodurile au d = 0
		p[i] = -1;  // initial niciun nod nu are parinte
		low[i] = 0;  // initial toate nodurile au low = 0
		subarb[i] = 0; // initial niciun nod nu are subarbori
	}
	int timp = 0; // variabila pentru moment
	for(i = 0; i < dimensiune; i++) { // incercam sa parcurgem DFS din orice surse posibile
		if (c[i] == 'a') { // daca nodul i nu este explorat, atunci inseaman ca este sursa si il explorez
			explorare_t(i, &timp, d, low, p, subarb, art, c, vector_adiacenta);
			printf("\ntestez subarb[%d] > 1 ....", current);
			if (subarb[i] > 1) {
				printf("Adevarat => art[%d] = 1 (nodul %d este nod de articulatie - cazul 1 al teoremei)", current, current);
				art[i] = 1;
			} else {
				printf("Fals");
			}
		}
	}
	printf("\n\nNodurile de articulatie: ");
	for(i = 0; i < dimensiune; i++) { // afisare
		if (art[i] == 1) {
			printf("%d ", i);
		}
		destroyQueue(vector_adiacenta[i]);
	}
	printf("\n");
	free(vector_adiacenta);
	free(d);
	free(low);
	free(p);
	free(subarb);
	free(c);
}

void explorare_t(int current, int *timp, int *d, int *low, int *p, int *subarb, int *art, char *c, Queue **vector_adiacenta) {
	int succesor;
	d[current] = *timp; // setare moment descoperire
	low[current] = *timp; // setare low
	c[current] = 'g'; // nod in curs de vizitare => gri
	printf("\n%d: d(%d) = %d, low(%d) = %d, c(%d) = gri, ", *timp, current, *timp, current, *timp, current);
	*timp = *timp + 1; // incrementare timp
	Queue *q = vector_adiacenta[current]; // lista de adiacenta a nodului curent
	while (!isQueueEmpty(q)) { // pentru fiecare vecin
		succesor = front(q);
		dequeue(q);
		if (c[succesor] == 'a') { // daca nu este vizitat, il vizitez acum
			p[succesor] = current; // setare parinte
			subarb[current]++; // incrementare subarbore
			printf("subarb[%d] = %d, p[%d] = %d", current, subarb[current], succesor, current);
			explorare_t(succesor, timp, d, low, p, subarb, art, c, vector_adiacenta);
			if (low[succesor] < low[current]) {
				low[current] = low[succesor];  // actualizare low
			}
			printf("\nlow(%d) = min{low(%d), low(%d)} = %d", current, current, succesor, low[current]);
			printf("\ntestez: low[%d] >= d[%d] && p[%d] != null .... ", succesor, current, current);
			if (p[current] != -1 && low[succesor] >= d[current]) {  // cazul 2 al teoremei
				printf("Adevarat => art[%d] = 1  (nodul %d este nod de articulatie - cazul 2 al teoremei)", current, current);
				art[current] = 1;
			} else {
				printf("Fals");
			}
		} else { // daca nodul vecin a fost deja vizitat
			printf("\ntestez: low[%d] > d[%d] .... ", current, succesor);
			if (d[succesor] < low[current] && p[current] != -1) {
				printf("Adevarat => low[%d] = d[%d] = %d", current, succesor, d[succesor]);
				low[current] = d[succesor];
			} else {
				printf("Fals");
			}
		}
	}
}

void punti() {
	Queue **vector_adiacenta = (Queue **) malloc(10 * sizeof(Queue *));
	int i, j, dimensiune;
	dimensiune = 10;
	for(i = 0; i < 10; i++) {
		vector_adiacenta[i] = createQueue();
	}
	// adaugarea arcelor din graful orientat
	enqueue(vector_adiacenta[0], 1); // 0-1
	enqueue(vector_adiacenta[0], 9); // 0-9
	enqueue(vector_adiacenta[1], 2); // 1-2
	enqueue(vector_adiacenta[2], 1); // 2-1
	enqueue(vector_adiacenta[1], 8); // 1-8
	enqueue(vector_adiacenta[8], 1); // 8-1
	enqueue(vector_adiacenta[2], 3); // 2-3
	enqueue(vector_adiacenta[3], 2); // 3-2
	enqueue(vector_adiacenta[2], 4); // 2-4
	enqueue(vector_adiacenta[4], 2); // 4-2
	enqueue(vector_adiacenta[2], 7); // 2-7
	enqueue(vector_adiacenta[7], 2); // 7-2
	enqueue(vector_adiacenta[3], 4); // 3-4
	enqueue(vector_adiacenta[4], 3); // 4-3
	enqueue(vector_adiacenta[3], 5); // 3-5
	enqueue(vector_adiacenta[5], 3); // 5-3
	enqueue(vector_adiacenta[5], 6); // 5-6
	enqueue(vector_adiacenta[6], 5); // 6-5
	enqueue(vector_adiacenta[7], 8); // 7-8
	enqueue(vector_adiacenta[8], 7); // 8-7

	printf("\n\nPUNTI\n\nDFS:");
	// alocare dinamica vectori ce urmeaza a fi folsiti
	int *d = (int *) malloc(dimensiune * sizeof(int));  // momentul descoperirii
	int *low = (int *) malloc(dimensiune * sizeof(int));
	int *p = (int *) malloc(dimensiune * sizeof(int));  // vector de parinti
	char *c = (char *) malloc(dimensiune * sizeof(char));  // culori: a = alb, g = gri
	int **punte = (int **) malloc(2 * sizeof(int *));
	punte[0] = (int *) malloc(dimensiune * sizeof(int));
	punte[1] = (int *) malloc(dimensiune * sizeof(int));
	int current, succesor;
	for(i = 0; i < dimensiune; i++) {
		c[i] = 'a';  // initial toate nodurile sunt albe
		d[i] = 0;  // initial toate nodurile au d = 0
		p[i] = -1;  // initial niciun nod nu are parinte
		low[i] = 0;  // initial toate nodurile au low = 0
	}
	int timp = 0;  // variabila pentru moment
	int nrp = 0;  // numarul de punti
	for(i = 0; i < dimensiune; i++) { // incercam sa parcurgem DFS din orice surse posibile
		if (c[i] == 'a') { // daca nodul i nu este explorat, atunci inseaman ca este sursa si il explorez
			explorare_p(i, &timp, d, low, p, punte, &nrp, c, vector_adiacenta);
		}
	}
	printf("\n\nPuntile sunt:\n");
	for(i = 0; i < nrp; i++) { // afisare punti
		printf("%d - %d\n", punte[0][i], punte[1][i]);
	}
	// eliberez memoria alocata
	free(vector_adiacenta);
	free(d);
	free(low);
	free(c);
	free(punte[1]);
	free(punte[0]);
	free(punte);
}

void explorare_p(int current, int *timp, int *d, int *low, int *p, int **punte,int *nrp, char *c, Queue **vector_adiacenta) {
	int succesor;
	d[current] = *timp; 
	low[current] = *timp;
	c[current] = 'g'; // nod in curs de vizitare => gri
	printf("\n%d: d(%d) = %d, low(%d) = %d, c(%d) = gri, ", *timp, current, *timp, current, *timp, current);
	*timp = *timp + 1; // incrementare timp
	Queue *q = vector_adiacenta[current]; // lista de adiacenta a nodului curent
	while (!isQueueEmpty(q)) { // pentru fiecare vecin
		succesor = front(q);
		dequeue(q);
		if (c[succesor] == 'a') { // daca nu este vizitat, il vizitez acum
			p[succesor] = current;
			printf("p[%d] = %d", succesor, current);
			explorare_p(succesor, timp, d, low, p, punte, nrp, c, vector_adiacenta);
			if (low[succesor] < low[current]) {
				low[current] = low[succesor];  // actualizare low
			}
			printf("\nlow(%d) = min{low(%d), low(%d)} = %d", current, current, succesor, low[current]);
			printf("\ntestez: low[%d] >= d[%d] .... ", succesor, current);
			if (low[succesor] > d[current]) {
				printf("Adevarat => punte %d-%d)", current, succesor);
				punte[0][*nrp] = current;
				punte[1][*nrp] = succesor;
				*nrp = *nrp + 1;
			} else {
				printf("Fals");
			}
		} else { // daca nodul vecin a fost deja vizitat
			printf("\ntestez: p[%d] != %d .... ", current, succesor);
			if (p[current] != succesor) { // actualizeaza low
				if (d[succesor] < low[current]) {
					low[current] = d[succesor];
				}
				printf("Adevarat => low[%d] = min{d[%d], low[%d]} = %d", current, succesor, current, low[current]);
			} else {
				printf("Fals");
			}
		}
	}
}
