#include <stdlib.h>
#include <stdio.h>

void permutari(int );
int validare_permutari(int *, int );
void submultimi(int );
int mai_exista(int *, int, int);
void regine(int );
int validare_regina(int *, int);

int main() {
	permutari(3);
	submultimi(3);
	regine(4);
	return 0;
}

void permutari(int N) {
	printf("Permutari(%d):\n", N);
	int max = N; // Valoarea maxima a unui numar
	int *sol = (int *) malloc(N * sizeof(int)); // Vectorul solutie
	int i, k; // i = indice in sol, k = contor
	int valid; // 0->invalid; 1->valid
	int init_val = 0; // valoarea de initializare
	for(k = 0; k < N; k++) {
		sol[k] = init_val; // initializare vector solutii
	}
	i = 0; // incepe de la primul element
	while(i >= 0) {
		valid = 0;
		while(!valid && sol[i] <= max) { // cat timp nu am gasit o solutie valida si nu am depasit valoarea maxima
			sol[i] = sol[i] + 1; // incrementare numar curent
			valid = validare_permutari(sol, i); // verifica daca solutia partiala este corecta
		}
		if(sol[i] <= max) { // daca solutia partiala curenta este valida
			if(i == N - 1) { // daca solutia este finala (am general N numere)
				for(k = 0; k < N; k++) { // afisare solutie
					printf("%d ", sol[k]);
				}
				printf("\n");
			}
			else { // solutia nu este finala => trecem la urmatorul numar
				i++;
			}
		}
		else { // daca solutia curenta nu este valida, resetam elementul curent si ne intoarcem inapoi
			sol[i] = init_val; // resetez elementul curent
			i--; // ma intorc la elementul anterior
		}
	}
	printf("\n");
}

int validare_permutari(int *sol, int i) {
	int j;
	for(j = 0; j < i; j++) { // caut daca exista deja numaru sol[i] deja in solutie
		if(sol[j] == sol[i]) {
			return 0; // returnez 0 daca mai exista sol[i]
		}
	}
	return 1; // returnez 1 daca starea curenta este valida
}

void submultimi(int N) {
	printf("Submultimi(%d):\n", N);
	int *A = (int *) malloc(N * sizeof(int)); // vector ce contine numerele 1...N
	int *v = (int *) malloc(N * sizeof(int)); // vector de alegere 0/1
	int i, k; // i = indicele in v, k = contor
	int init_val = -1; // valoare initiala
	int max = 1; // valoarea maxima (adica poate lua doar 0 sau 1)
	for(i = 0; i < N; i++) {
		v[i] = init_val;
	}
	for(i = 1; i <= N; i++) { // Genereaza multimea de numere de la 1 la N
		A[i-1] = i;
	}
	i = 0; // incepem de la indicele 0
	while(i >= 0) {
		if(v[i] <= max) { // daca nu am depasit maximul (adica 1)
			v[i] = v[i] + 1; // incrementeaza elementul curent
		}
		if(v[i] <= max) { // daca maximul nu este depasit
			if(i == N - 1) { // daca am ajuns la o solutie finala
				printf("{");
				for(k = 0; k < N; k++) { // pentru fiecare element din A
					if(v[k]) { // daca avem in v 1 pe pozitia k, atunci afiseaza A[k]
						printf("%d", A[k]);
						if(mai_exista(v, k, N)) { // daca mai exisa cel putin un 1 in v dupa indicele k, atunci printeaza o virgula
							printf(", ");
						}
					}
				}
				printf("}\n");
			}
			else{ // daca nu am ajuns la o solutie finala, incrementeaza i (genereaza urmatorul numar)
				i++;
			}
		}
		else{ // daca am depasit maximul, resetaza v[i] si mergi inapoi la i-1
			v[i] = init_val;
			i--;
		}

	}
	printf("\n");
}

int mai_exista(int *v, int k, int N) {
	// verifica daca mai exisa vreun element setat pe 1 dupa indicele k
	for(k = k + 1; k < N; k++) {
		if(v[k]) {
			return 1;
		}
	}
	return 0;
}

void regine(int N) {
	printf("Regine(%d):\n", N);
	int max = N - 1; // valoarea maxima a liniei pe care plasez o regina (0...N-1)
	int *v = (int *) malloc(N * sizeof(int)); // vectorul solutii
	int i, k; // i = indicele in v, k = contor
	int valid; // 0 -> invalid; 1 -> valid
	int init_val = -1; // valoare de initializare
	for(k = 0; k < N; k++) {
		v[k] = init_val; // initializare vector solutii
	}
	i = 0; // incepe de la prima coloana
	while(i >= 0) {
		valid = 0; // initializeaza valid cu 0 ca sa intre in while
		while(!valid && v[i] <= max) {
			v[i] = v[i] + 1; // incrementeaza linia
			valid = validare_regina(v, i); // verifica daca este o pozitionare valida
		}
		if(v[i] <= max) { // daca nu a depasit max
			if(i == N - 1) { // daca am ajuns la o solutie finala
				for(k = 0; k < N; k++) { // afisare
					printf("%d ", v[k]);
				}
				printf("\n");
			}
			else { // daca nu e solutie finala, treci la urmatorul element
				i++;
			}
		}
		else { // daca a depasit max
			v[i] = init_val; // reseteaza la init val
			i--; // intoarce-te la elementul anterior
		}
	}
}

int validare_regina(int *v, int k) {
	int i;
	for(i = 0; i < k; i++) {
		if(v[i] == v[k] || k - i == abs(v[i]-v[k])) {
			return 0;
		}
	}
	return 1;
}

int abs(int x) {
	if(x < 0) {
		return -x;
	}
	return x;
}