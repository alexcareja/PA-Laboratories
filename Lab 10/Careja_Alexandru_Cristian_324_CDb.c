#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 10000000

typedef struct QueueNode{
	int elem;
	int cost;
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

void enqueue(Queue *q, int elem, int cost){ // inscriere in coada
	q->size += 1;
	QueueNode *node = (QueueNode *) malloc(sizeof(QueueNode));
	node->elem = elem;
	node->cost = cost;
	node->next = NULL;
	if (isQueueEmpty(q)) {
		q->front = node;
		q->rear = node;
		return;
	}
	q->rear->next = node;
	q->rear = node;
}

int frontElem(Queue* q){ // vezi primul element din coada
	return q->front->elem;
}

int frontCost(Queue* q){ // vezi primul element din coada
	return q->front->cost;
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

void Dijkstra();
int ExtrageMin(QueueNode *, int *);
QueueNode *ScoateMin(QueueNode *, int *);
void BellmanFord();

int main() {
	Dijkstra();
	BellmanFord();
	return 0;
}

void Dijkstra() {
	int i, j, dimensiune = 7;
	Queue **vector_adiacenta = (Queue **) malloc((dimensiune + 1) * sizeof(Queue *));
	for(i = 1; i <= dimensiune; i++) {
		vector_adiacenta[i] = createQueue();
	}
	// adaugarea arcelor din graful orientat
	enqueue(vector_adiacenta[1], 2, 3); // 1->2 cost 3
	enqueue(vector_adiacenta[1], 3, 4); // 1->3 cost 4
	enqueue(vector_adiacenta[1], 5, 1); // 1->5 cost 1
	enqueue(vector_adiacenta[1], 6, 10); // 1->6 cost 10
	enqueue(vector_adiacenta[1], 7, 3); // 1->7 cost 3
	enqueue(vector_adiacenta[2], 3, 2); // 2->3 cost 2
	enqueue(vector_adiacenta[3], 4, 2); // 3->4 cost 2
	enqueue(vector_adiacenta[3], 6, 2); // 3->6 cost 2
	enqueue(vector_adiacenta[5], 4, 3); // 5->4 cost 3
	enqueue(vector_adiacenta[5], 7, 1); // 5->7 cost 1
	enqueue(vector_adiacenta[6], 4, 2); // 6->4 cost 2
	enqueue(vector_adiacenta[7], 3, 1); // 7->3 cost 1
	enqueue(vector_adiacenta[7], 4, 10); // 7->4 cost 10
	enqueue(vector_adiacenta[7], 5, 2); // 7->5 cost 2

	printf("Dijkstra:\n");
	// alocare dinamica vectori ce urmeaza a fi folsiti
	int *d = (int *) malloc((dimensiune + 1) * sizeof(int));  // distanta de la sursa
	int *p = (int *) malloc((dimensiune + 1) * sizeof(int));  // vector de parinti
	int current, succesor;
	for(i = 1; i <= dimensiune; i++) {
		d[i] = INF;  // initial toate nodurile au d = 0
		p[i] = -1;  // initial niciun nod nu are parinte
	}
	d[1] = 0;
	QueueNode *q = (QueueNode *) malloc(sizeof(QueueNode)); // coada cu prioritati
	q->elem = 1;
	QueueNode *aux, *aux1;
	aux = q;
	// construieste coada cu prioritati
	for (i = 2; i <= dimensiune; i++) {
		aux1 = (QueueNode *) malloc(sizeof(QueueNode));
		aux1->elem = i;
		aux1->next = NULL;
		aux->next = aux1;
		aux = aux->next;
	}
	int u, v, w;
	while (q != NULL) {
		// extrage nodul cu cost minim din coada cu prioritati
		u = ExtrageMin(q, d);
		q = ScoateMin(q, d);
		printf("Extrage din coada nodul cu disanta minima: %d\n", u);
		while (! isQueueEmpty(vector_adiacenta[u])) {
			// pentru toate nodurile adiacente
			v = frontElem(vector_adiacenta[u]);
			w = frontCost(vector_adiacenta[u]);
			dequeue(vector_adiacenta[u]);
			printf("testeaza d[%d] > d[%d] + W%d%d\t", v,  u, u, v);
			if (d[v] > d[u] + w) {
				// daca se poate relaxa un arc, actualizeaza d si p
				d[v] = d[u] + w;
				p[v] = u;
				printf("Adevarat => d[%d] = %d si p[%d] = %d\n", v, d[v], v, u);
			} else {
				printf("Fals\n");
			}
		}
	}
	// printare rezultat si eliberare memorie
	printf("Rezultat:");
	for(i = 1; i <= dimensiune; i++) { // afisare
		printf("d[%d] = %d\tp[%d] = %d\n", i, d[i], i, p[i]);
		destroyQueue(vector_adiacenta[i]);
	}
	printf("\n");
	free(vector_adiacenta);
	free(d);
	free(p);
}


int ExtrageMin(QueueNode *q, int * d) {
	// functie care returneaza nodul cu distanta minima din coada
	QueueNode *aux = q;
	int min = aux->elem;
	while (aux != NULL) {
		if (d[aux->elem] < d[min]) {
			min = aux->elem;
		}
		aux = aux->next;
	}
	return min;
}

QueueNode *ScoateMin(QueueNode *q, int * d) {
	// functie care elimina nodul cu distanta minima din coada
	QueueNode *aux = q;
	int min = ExtrageMin(q, d);
	if (q->elem == min) {
		return q->next;
	}
	aux = q;
	QueueNode *aux2 = q->next;
	while (aux2 != NULL) {
		if (aux2->elem == min) {
			aux->next = aux2->next;
			break;
		}
		aux = aux2;
		aux2 = aux2->next;
	}
	return q;
}

void BellmanFord() {
	int i, j, k, l, dimensiune = 7;
	Queue **vector_adiacenta = (Queue **) malloc((dimensiune + 1) * sizeof(Queue *));
	for(i = 1; i <= dimensiune; i++) {
		vector_adiacenta[i] = createQueue();
	}
	// adaugarea arcelor din graful orientat
	enqueue(vector_adiacenta[1], 2, 3); // 1->2 cost 3
	enqueue(vector_adiacenta[1], 3, 4); // 1->3 cost 4
	enqueue(vector_adiacenta[1], 5, 1); // 1->5 cost 1
	enqueue(vector_adiacenta[1], 6, 10); // 1->6 cost 10
	enqueue(vector_adiacenta[1], 7, 3); // 1->7 cost 3
	enqueue(vector_adiacenta[2], 3, 2); // 2->3 cost 2
	enqueue(vector_adiacenta[3], 4, 2); // 3->4 cost 2
	enqueue(vector_adiacenta[3], 6, 2); // 3->6 cost 2
	enqueue(vector_adiacenta[5], 4, 3); // 5->4 cost 3
	enqueue(vector_adiacenta[5], 7, 1); // 5->7 cost 1
	enqueue(vector_adiacenta[6], 4, 2); // 6->4 cost 2
	enqueue(vector_adiacenta[7], 3, 1); // 7->3 cost 1
	enqueue(vector_adiacenta[7], 4, 10); // 7->4 cost 10
	enqueue(vector_adiacenta[7], 5, 2); // 7->5 cost 2

	printf("\nBellman-Ford:\n");
	// alocare dinamica vectori ce urmeaza a fi folsiti
	int *d = (int *) malloc((dimensiune + 1) * sizeof(int));  // distanta de la sursa
	int *p = (int *) malloc((dimensiune + 1) * sizeof(int));  // vector de parinti
	int current, succesor;
	for(i = 1; i <= dimensiune; i++) {
		d[i] = INF;  // initial toate nodurile au d = 0
		p[i] = -1;  // initial niciun nod nu are parinte
	}
	d[1] = 0;	// nodul sursa are d = 0
	int *noduri_considerate = (int *) calloc(dimensiune + 1, sizeof(int));
	// noduri_considerate = vectorul in care iterez prin nodurile considerate la pasul anterior
	int *noduri_noi_considerate = (int *) calloc(dimensiune + 1, sizeof(int));
	// noduri_noi_considerate = vectorul in care retin nodurile considerate la pasul curent
	int u, v, w, ok;
	QueueNode *aux;	// auxiliar pentru parcurgerea cozii de noduri adiacente
	noduri_considerate[0] = 1;	// primul nod considerat este sursa
	for (i = 0; i < dimensiune; i++) {
		printf("%d: i = %d\n", i, i);
		k = 0;	// contor pentru noduri_noi_considerate
		j = 0;	// indice pentru parcurgere noduri_considerate
		u = noduri_considerate[j];
		while(u != 0) {
			aux = vector_adiacenta[u]->front;
			while (aux != NULL) {
				v = aux->elem;
				w = aux->cost;
				printf("(u, v) = (%d, %d)\n", u, v);
				printf("daca d[%d] > d[%d] + W%d%d\t", v, u, u, v);
				if (d[v] > d[u] + w) {
					// daca am gasit un drum mai bun actualizeaza d si p
					d[v] = d[u] + w;
					p[v] = u;
					ok = 1;
					for (l = 0; l < k; l++) {
						if (noduri_noi_considerate[l] == v) {
							// atunci am considerat deja acest nod
							ok = 0;
						}
					}
					if (ok) {
						// daca nu a fost deja considerat nodul, il adaug in lista
						// de noduri considerate
						noduri_noi_considerate[k] = v;
						k++;
					}
					printf("Adevarat => d[%d] = %d si p[%d] = %d\n", v, d[v], v, p[v]);
				}
				else {
					printf("Fals\n");
				}
				aux = aux->next;
			}
			j++;
			u = noduri_considerate[j];	// continua cu urmatorul nod considerat anterior
		}
		// copiaza in noduri_considerate continutul noduri_noi_considerate pentru a itera prin ele
		memcpy(noduri_considerate, noduri_noi_considerate, (dimensiune + 1) * sizeof(int));
		// seteaza pe 0 noduri_noi_considerate
		memset(noduri_noi_considerate, 0,(dimensiune + 1) * sizeof(int));
		printf("\n");
	}
	// printare rezultat si eliberare memorie
	printf("Rezultat:\n");
	for(i = 1; i <= dimensiune; i++) { // afisare
		printf("d[%d] = %d\tp[%d] = %d\n", i, d[i], i, p[i]);
		destroyQueue(vector_adiacenta[i]);
	}
	printf("\n");
	free(vector_adiacenta);
	free(noduri_considerate);
	free(noduri_noi_considerate);
	free(d);
	free(p);
}