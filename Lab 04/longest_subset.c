#include <stdlib.h>
#include <stdio.h>

#define INF 2147483647

void print_sol(int *v, int i, int *D, int *S);

int main() {
	int S[] = {6, 1, 2, 9, 3, 8, 4,  7};
	int *v = (int *) calloc(8, sizeof(int));
	int *D = (int *) calloc(8, sizeof(int));
	int i, j, mx, k;
	for (i = 0; i < 8; i++) {
		mx = 0;
		for (j = 0; j < i; j++) {
			if (S[i] > S[j] && D[j] > mx) {
				mx = D[j];
				k = j;
			}
		}
		v[i] = k;
		D[i] = mx + 1;
	}
	mx = 0;
	for (i = 0; i < 8; i++) {
		if (D[i] > mx) {
			mx = D[i];
			k = i;
		}
	}
	printf("Cel mai lung subsir crescator are lungime %d si este : ", mx);
	print_sol(v, k, D, S);
	printf("\n");
	return 0;
}

void print_sol(int *v, int i, int *D, int *S) {
	int ok = 1;
	if (D[i] == 1) {
		ok = 0;
	}
	if (ok) {
		print_sol(v, v[i], D, S);
	}
	printf("%d ", S[i]);
}