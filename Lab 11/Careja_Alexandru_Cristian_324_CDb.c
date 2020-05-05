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

void Prim();
int amVizitatTot(int *, int);
int ExtrageMin(int *, int *, int);
char getChar(int);
void Kruskal();
void inserareMuchie(int, int **, int, int, int);
void interclasare(int **v, int i, int m, int j);
void sortare_pi(int **v, int i, int j);
int intersectie(int **, int , int , int);
void reuniune(int **, int , int , int);

int main() {
	Prim();
	Kruskal();
	return 0;
}

void Prim() {
	printf("Prim:\n\n");

	int i, j, dimensiune = 12;
	Queue **vector_adiacenta = (Queue **) malloc((dimensiune + 1) * sizeof(Queue *));
	for(i = 1; i <= dimensiune; i++) {
		vector_adiacenta[i] = createQueue();
	}
	// adaugarea arcelor din graful orientat o fac ca intr-un graf orientat,
	// si pentru o muchie X-Y, adaug X->Y si Y->X in listele mele de adiacenta
	// codific nodurile {A, B, C...} = {1, 2, 3...}
	enqueue(vector_adiacenta[1], 2, 9); // A->B cost 9
	enqueue(vector_adiacenta[1], 7, 10); // A->G cost 10
	enqueue(vector_adiacenta[1], 8, 6); // A->H cost 6
	enqueue(vector_adiacenta[1], 9, 3); // A->I cost 3
	enqueue(vector_adiacenta[2], 1, 9); // B->A cost 9
	enqueue(vector_adiacenta[2], 3, 5); // B->C cost 5
	enqueue(vector_adiacenta[2], 7, 11); // B->G cost 11
	enqueue(vector_adiacenta[3], 2, 2); // C->B cost 5
	enqueue(vector_adiacenta[3], 4, 3); // C->D cost 8
	enqueue(vector_adiacenta[3], 5, 12); // C->E cost 12
	enqueue(vector_adiacenta[4], 3, 8); // D->C cost 8
	enqueue(vector_adiacenta[4], 6, 9); // D->F cost 9
	enqueue(vector_adiacenta[5], 3, 12); // E->C cost 12
	enqueue(vector_adiacenta[5], 6, 2); // E->F cost 2
	enqueue(vector_adiacenta[6], 4, 9); // F->D cost 9
	enqueue(vector_adiacenta[6], 5, 2); // F->E cost 2
	enqueue(vector_adiacenta[7], 1, 10); // G->A cost 10
	enqueue(vector_adiacenta[7], 2, 11); // G->B cost 11
	enqueue(vector_adiacenta[7], 8, 4); // G->H cost 4
	enqueue(vector_adiacenta[8], 1, 6); // H->A cost 6
	enqueue(vector_adiacenta[8], 7, 4); // H->G cost 4
	enqueue(vector_adiacenta[9], 1, 3); // I->A cost 3
	enqueue(vector_adiacenta[9], 10, 5); // I->J cost 5
	enqueue(vector_adiacenta[9], 12, 8); // I->L cost 8
	enqueue(vector_adiacenta[10], 9, 5); // J->I cost 5
	enqueue(vector_adiacenta[10], 11, 14); // J->K cost 14
	enqueue(vector_adiacenta[11], 10, 14); // K->J cost 14
	enqueue(vector_adiacenta[11], 12, 6); // K->L cost 6
	enqueue(vector_adiacenta[12], 9, 8); // L->I cost 8
	enqueue(vector_adiacenta[12], 11, 7); // L->K cost 7

	// alocare dinamica vectori ce urmeaza a fi folsiti
	int *d = (int *) malloc((dimensiune + 1) * sizeof(int));  // distanta de la sursa
	int *p = (int *) malloc((dimensiune + 1) * sizeof(int));  // vector de parinti
	int *vizitat = (int *) malloc((dimensiune + 1) * sizeof(int));  // vector de vizite
	int **AMA = (int **) malloc(2 * sizeof(int *));	// AMA
	AMA[0] = (int *) calloc(dimensiune, sizeof(int));
	AMA[1] = (int *) calloc(dimensiune, sizeof(int));
	for(i = 1; i <= dimensiune; i++) {
		d[i] = INF;  // initial toate nodurile au d = 0
		p[i] = -1;  // initial niciun nod nu are parinte
		vizitat[i] = 0;  // initial niciun nod nu este vizitat
	}
	d[9] = 0;	// pornind din nodul 9 = "I"
	// in locul unei cozi de prioritati ma folosesc de vectorii vizitat si
	// d ca sa extrag nodul cel mai de aproape si de doua functii: una care
	// verifica daca am vizitat tot graful, si una care extrage nodul cu d minim
	// si il marcheaza ca vizitat
	int u, v, w;
	j = 0; // indicele din AMA
	while (amVizitatTot(vizitat, dimensiune) == 0) {
		// extrage nodul cu cost minim din coada cu prioritati
		u = ExtrageMin(vizitat, d, dimensiune);
		// introdu muchia in AMA
		if (p[u] != -1) {
			AMA[0][j] = u;
			AMA[1][j] = p[u];
			j++;
		}
		printf("Extrage nodul cu disanta minima: %d\n", u);
		// pentru fiecare nod adiacente
		while (! isQueueEmpty(vector_adiacenta[u])) {
			// extrage element
			v = frontElem(vector_adiacenta[u]);
			w = frontCost(vector_adiacenta[u]);
			dequeue(vector_adiacenta[u]);
			printf("testeaza d[%d] > W%d%d\t", v, u, v);
			if (d[v] > w) {
				// daca distanta folosind aceasta muchie este mai mica decat cea veche
				// actualizeaza d si parintele
				d[v] = w;
				p[v] = u;
				printf("Adevarat => d[%d] = %d si p[%d] = %d\n", v, w, v, u);
			} else {
				printf("Fals\n");
			}
		}
	}
	// printare rezultat
	printf("Arborele minim de acoperire calculat cu algoritmul lui Prim\nse formeaza cu muchiile:\n");
	for(i = 0; i < j; i++) { // afisare
		printf("%c-%c\n", getChar(AMA[0][i]), getChar(AMA[1][i]));
		destroyQueue(vector_adiacenta[i]);
	}
	printf("\n");
	// eliberare memorie alocata dinamic
	free(vector_adiacenta);
	free(d);
	free(p);
	free(vizitat);
}

int amVizitatTot(int *vizitat, int dim) {
	// functia imi returneaza 1 daca am vizitat toate nodurile din graf
	int i;
	for (i = 1; i <= dim; i++) {
		if (vizitat[i] == 0) {
			// inca mai exista cel putin un nod nevizitat
			return 0;
		}
	}
	return 1;
}


int ExtrageMin(int *vizitat, int *d, int dim) {
	// functia returneaza nodul aflat la distanta cea mai mica de AMA curent
	int i, min_dist = INF + 1, nod;
	for (i = 1; i <= dim; i++) {
		if (vizitat[i]) {
			continue;
		}
		// daca am ajuns aici, atunci nodul i nu este vizitat
		if (d[i] < min_dist) {
			min_dist = d[i];
			nod = i;
		}
	}
	vizitat[nod] = 1;
	return nod;
}

char getChar(int n) {
	// decodifica {1, 2, 3, ...} -> {A, B, C, ...}
	char c = 'A';
	c += n - 1;
	return c;
}

void Kruskal() {
	printf("\nKruskal:\n\n");

	int i, j, nr_muchii = 15, dimensiune = 12;
	int **muchii = (int **) malloc(nr_muchii * sizeof(int *));
	// muchii[i][0] - nod; muchii[i][1] - nod
	// muchii[i][2] - costul muchiei
	for(i = 0; i < nr_muchii; i++) {
		muchii[i] = (int *) calloc(3, sizeof(int));
	}
	// adaugarea arcelor din graful orientat
	inserareMuchie(0, muchii, 1, 2, 9); // A->B cost 9
	inserareMuchie(1, muchii, 1, 7, 10); // A->G cost 10
	inserareMuchie(2, muchii, 1, 8, 6); // A->H cost 6
	inserareMuchie(3, muchii, 1, 9, 3); // A->I cost 3
	inserareMuchie(4, muchii, 2, 3, 5); // B->C cost 5
	inserareMuchie(5, muchii, 2, 7, 11); // B->G cost 11
	inserareMuchie(6, muchii, 3, 4, 8); // C->D cost 8
	inserareMuchie(7, muchii, 3, 5, 12); // C->E cost 12
	inserareMuchie(8, muchii, 4, 6, 9); // D->F cost 9
	inserareMuchie(9, muchii, 5, 6, 2); // E->F cost 2
	inserareMuchie(10, muchii, 7, 8, 4); // G->H cost 4
	inserareMuchie(11, muchii, 9, 10, 5); // I->J cost 5
	inserareMuchie(12, muchii, 9, 12, 8); // I->L cost 8
	inserareMuchie(13, muchii, 10, 11, 14); // J->K cost 14
	inserareMuchie(14, muchii, 11, 12, 7); // K->L cost 7
	int **arb = (int **) malloc((dimensiune + 1)* sizeof(int *));
	// arb este o matrice in care voi retine arborele fiecarui nod
	for(i = 0; i <= dimensiune; i++) {
		// initializez totul cu 0
		arb[i] = (int *) calloc(dimensiune + 1, sizeof(int));
		arb[i][i] = i; // arborele unui nod se contine doar pe el insusi
	}
	int **AMA = (int **) malloc(2 * sizeof(int *));	// Arborele minim de acoperire
	AMA[0] = (int *) calloc(dimensiune, sizeof(int));
	AMA[1] = (int *) calloc(dimensiune, sizeof(int));
	// sorteaza muchiile crescator dupa costul lor
	sortare_pi(muchii, 0, 14);
	int u, v;
	for (i = 0, j = 0; i < nr_muchii; i++) { // pentru fiecare muchie
		u = muchii[i][0];
		v = muchii[i][1];
		printf("Extrag muchia %c-%c de cost %d\n", getChar(u), getChar(v), muchii[i][2]);
		if (intersectie(arb, dimensiune, u, v) == 0) {
			printf("Arborii nodurilor nu se intersecteaza, deci adaug muchia in AMA.\n");
			// daca adaugarea muchiei u-v nu creeaza un ciclu
			// reunim arborii si adaugam muchia in AMA
			reuniune(arb, dimensiune, u, v);
			AMA[0][j] = u;
			AMA[1][j] =v;
			j++;
		} else {
			// Arborii nodurilor se intersecteaza, ceea ce ar conduce la un ciclu.
			printf("Nu agaug muchia in AMA.\n");
		}
	}
	// afisare solutie
	printf("\nArborele minim de acoperire calculat cu algoritmul lui Kruskal\nse formeaza cu muchiile:\n\n");
	for(i = 0; i < j; i++) { // afisare
		printf("%c-%c\n", getChar(AMA[0][i]), getChar(AMA[1][i]));
	}
	printf("\n");
	// eliberare memorie alocata dinamic
	for(i = 0; i < nr_muchii; i++) {
		free(muchii[i]);
	}
	free(muchii);
	free(arb[muchii[0][0]]);
	free(AMA[0]);
	free(AMA[1]);
	free(AMA);
	free(arb);
}

void inserareMuchie(int i, int **m, int nodA, int nodB, int c) {
	// Insereaza muchia nodA-nodB de cost = c
	m[i][0] = nodA;
	m[i][1] = nodB;
	m[i][2] = c;
}

int intersectie(int **arb, int dim, int u, int v) {
	// returneaza 1 daca cei doi arbori au cel putin un nod comun
	int i;
	for (i = 1; i <= dim; i++) {
		if (arb[u][i] && arb[v][i]) {
			// contin un nod comun cei doi arbori
			return 1;
		}
	}
	// nu am gasit niciun nod comun
	return 0;
}

void reuniune(int **arb, int dim, int u, int v) {
	// realizeaza reuniunea dintre arb(u) si arb(v)
	int i;
	for (i = 1; i <= dim; i++) {
		if (arb[v][i]) {
			arb[u][i] = 1;
		}
	}
	free(arb[v]);
	arb[v] = arb[u];
}

void interclasare(int **v, int i, int m, int j) {
	// interclasarea a doi vectori sortati
	int iinit = i, h;
	int **u = (int **) calloc(j - i + 1, sizeof(int *));
	for(h = 0; h < j - i + 1; h++) {
		u[h] = (int *) calloc(3, sizeof(int));
	}
	int l = 0;
	int k = m + 1;
	while (i <= m && k <= j) {
		if (v[i][2] < v[k][2]) { // compara costurile
			u[l][0] = v[i][0];
			u[l][1] = v[i][1];
			u[l][2] = v[i][2];
			i++;
			l++;
		}
		else {
			u[l][0] = v[k][0];
			u[l][1] = v[k][1];
			u[l][2] = v[k][2];
			k++;
			l++;
		}
	}
	while (i <= m) {
		u[l][0] = v[i][0];
		u[l][1] = v[i][1];
		u[l][2] = v[i][2];
		i++;
		l++;
	}
	while (k <= j) {
		u[l][0] = v[k][0];
		u[l][1] = v[k][1];
		u[l][2] = v[k][2];
		k++;
		l++;
	}
	l = 0;
	while (iinit <= j) {
		v[iinit][0] = u[l][0];
		v[iinit][1] = u[l][1];
		v[iinit][2] = u[l][2];
		iinit++;
		l++;
	}
	for(h = 0; h < j - i + 1; h++) {
		free(u[h]);
	}
	free(u);
}

void sortare_pi(int **v, int i, int j) {
	if (i < j) {
		int m = (i + j) / 2;
		sortare_pi(v, i, m);
		sortare_pi(v, m + 1, j);
		interclasare(v, i, m, j);
	}
}