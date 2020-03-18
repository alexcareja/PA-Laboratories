#include <stdlib.h>
#include <stdio.h>

void k_garduri(int k, int N);
void rest_3();
void print_sums(int n, int k, int s);

int V[] = {3, 1, 2, 4};
int DIM = 4;

int main() {

	k_garduri(2, 6);
	rest_3();
	return 0;
}

void k_garduri(int k, int N) {
	int *D = (int *) calloc(N + 1, sizeof(int));	// Vectorul in care retinem solutiile
	int i, j, o, x;	// contori
	for (i = 0; i <= k; i++) {	// Cazul de baza merge pana la "inaltimea" gardului
		D[i] = i;	// Initializare cazuri de baza: D[0] = 0, D[1] = 1, ... D[k] = k
	}
	for (i = k + 1; i <= N; i++) {	// Generam numarul de posilitati incepand de la dimensiunea k pana la dimensiunea problemei, adica N
		D[i] = D[i-1] + D[i-k];	// Formula de recurenta pentru 
	}
	for (i = 1; i <= N; i++){	// Afisare solutii
		printf("D[%d] = %d\n", i, D[i]);
		for (j = i; j >= 1; j -= k) {	// j = numarul de scanduri ce se pot pozitiona pe verticala
			o = (i - j) / k;	// o = Numarul de grupuri de k scanduri asezate pe orizontala (echivalentul a cate "=" sunt in 2-garduri)
			if (o) {
				printf("permutari de %d scaduri pozitionate vertical si %d grupuri de %d scaduri grupate orizontale\n", j, o, k);
			}
			else {
				printf("%d scanduri pozitionate vertical\n", j);
			}
		}
	}
}

void rest_3 (){
	int **D = (int **) malloc((DIM + 1) * sizeof(int **));
	int i;	// contor
	for (i = 0; i <= DIM; i++) {
		D[i] = (int *) malloc(3 * sizeof(int));

	}
	// Initializare cazul de baza
	D[0][0] = 0;
	D[0][1] = 0;
	D[0][2] = 0;
	for (i = 1; i <= DIM; i++) {
		if (V[i - 1] % 3 == 0) {	// 3k
			// numarul de sume cu rest 0 este 1 pentru numarul curent + numarul vechi de sume cu rest 0 + inca o data numarul vechi de sume cu rest 0
			D[i][0] = 1 + 2 * D[i-1][0];
			// numarul de sume cu rest 1 este de 2 ori numarul vechi de sume cu rest 1 (deoarece pot adauga la fiecare suma elementul curent si am tot rest 1)
			D[i][1] = 2 * D[i-1][1];
			// numarul de sume cu rest 1 este de 2 ori numarul vechi de sume cu rest 1 (deoarece pot adauga la fiecare suma elementul curent si am tot rest 1)
			D[i][2] = 2* D[i-1][2];
		}
		if (V[i - 1] % 3 == 1) {	// 3k + 1
			// numarul de sume cu rest 0 este numarul vechi de sume cu rest 0 + numarul vechi de sume cu rest 2 (deoarece pot adauga la fiecare din ele elementul curent si sa am tot rest 0)
			D[i][0] = D[i-1][0] + D[i-1][2];
			// numarul de sume cu rest 1 este 1 pentru numarul curent + numarul vechi de sume cu rest 1 + numarul vechi de sume cu rest 0 (la ele pot adauga elem curent) 
			D[i][1] = 1 + D[i-1][1] + D[i-1][0];
			// numarul de sume cu rest 2 este numarul vechi de sume cu rest 2 + numarul vechi de sume cu rest 1 (la ele pot adauga elementul curent)
			D[i][2] = D[i-1][2] + D[i-1][1];
		}
		if (V[i - 1] % 3 == 2) {	// 3k + 2
			// numarul de sume cu rest 0 este numarul vechi de sume cu rest 0 + numarul vechi de sume cu rest 1 (la ele pot adauga elementul curent)
			D[i][0] = D[i-1][0] + D[i-1][1];
			// numarul de sume cu rest 1 este numarul vechi de sume cu rest 1 + numarul vechi de sume cu rest 2 (la ele pot adauga elementul curent)
			D[i][1] = D[i-1][1] + D[i-1][2];
			// numarul de sume cu rest 2 este 1 pentru numarul curent + numarul vechi de sume cu rest 2 + numarul vechi de sume cu rest 0 (la ele pot adauga elem curent)
			D[i][2] = 1 + D[i-1][0] + D[i-1][2];
		}

		printf("D[%d][0] = %d : ", i, D[i][0]);
		print_sums(i - 1, 0, 0);	// printare sume
		printf("\n");
		printf("D[%d][1] = %d : ", i, D[i][1]);
		print_sums(i - 1, 1, 0);	// printare sume
		printf("\n");
		printf("D[%d][2] = %d : ", i, D[i][2]);
		print_sums(i - 1, 2, 0);	// printare sume
		printf("\n");
	}
}

void print_sums(int n, int k, int s) {	// generare toate sumele care dau rest k folosind elementele de la 0 la n-1 din vector
	if ((s + V[n]) % 3 == k) {
		printf("%d ", s + V[n]);
	}
	if (n == 0) {
		return;
	}
	print_sums(n-1, k, s);
	print_sums(n-1, k, s + V[n]);
}