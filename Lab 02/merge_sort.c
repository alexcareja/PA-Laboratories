#include <stdlib.h>
#include <stdio.h>

void afisare_vect(int *v, int n);
void interclasare(int *v, int i, int m, int j);
void sortare_pi(int *v, int i, int j);

int main() {
	int v[] = {3, 82, 4, 82, -2, 82, 101, 7, 900, 82};
	sortare_pi(v, 0, 9);
	afisare_vect(v, 9);
	return 0;
}

void afisare_vect(int *v, int n) {
	int i = 0;
	for (; i <= n; i++) {
		printf("v[%d] = %d\n ", i, v[i]);
	}
}

void interclasare(int *v, int i, int m, int j) {
	int iinit = i;
	int *u = (int *) calloc(j - i + 1, sizeof(int));
	int l = 0;
	int k = m + 1;
	while (i <= m && k <= j) {
		if (v[i] < v[k]) {
			u[l++] = v[i++];
		}
		else {
			u[l++] = v[k++];
		}
	}
	while (i <= m) {
		u[l++] = v[i++];
	}
	while (k <= j) {
		u[l++] = v[k++];
	}
	l = 0;
	while (iinit <= j) {
		v[iinit++] = u[l++];
	}
	free(u);
}

void sortare_pi(int *v, int i, int j) {
	if (i < j) {
		int m = (i + j) / 2;
		sortare_pi(v, i, m);
		sortare_pi(v, m + 1, j);
		interclasare(v, i, m, j);
	}
}