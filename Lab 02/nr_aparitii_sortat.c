#include <stdlib.h>
#include <stdio.h>

int nr_aparitii_element(int *v, int i, int j, int x);
int cautare_binara_prima_aparitie(int *v, int i, int j, int x);
int cautare_binara_ultima_aparitie(int *v, int i, int j, int x);

int main() {
	int v[] = {0, 1, 2, 2, 2, 3, 4, 5, 6, 8, 9};
	int cautat = 2;
	printf("numarul de aparitii ale lui %d in vectorul sortat este %d\n", cautat, nr_aparitii_element(v, 0, 9, cautat));
	return 0;
}

int nr_aparitii_element(int *v, int i, int j, int x) {
	return cautare_binara_ultima_aparitie(v, i, j, x) - cautare_binara_prima_aparitie(v, i, j, x) + 1;
}

int cautare_binara_prima_aparitie(int *v, int i, int j, int x) {
	if (i > j) {
		return -1;
	}
	else {
		int m = (i + j) / 2;
		if (v[m] == x) {
			if (m - 1 >= 0 && v[m - 1] == x) {
				return cautare_binara_prima_aparitie(v, i, m - 1, x);
			}
			else {
				return m;
			}
		}
		else {
			if (v[m] > x) {
				return cautare_binara_prima_aparitie(v, i, m - 1, x);
			}
			else {
				return cautare_binara_prima_aparitie(v, m + 1, j, x);
			}
		}
	}
}

int cautare_binara_ultima_aparitie(int *v, int i, int j, int x) {
	if (i > j) {
		return -1;
	}
	else {
		int m = (i + j) / 2;
		if (v[m] == x) {
			if (m + 1 <= j && v[m + 1] == x) {
				return cautare_binara_ultima_aparitie(v, m + 1, j, x);
			}
			else {
				return m;
			}
		}
		else {
			if (v[m] > x) {
				return cautare_binara_ultima_aparitie(v, i, m - 1, x);
			}
			else {
				return cautare_binara_ultima_aparitie(v, m + 1, j, x);
			}
		}
	}	
}