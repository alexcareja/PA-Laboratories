#include <stdlib.h>
#include <stdio.h>

#define max(a, b) (((a) < (b)) ? (b) : (a))

void Hanoi(int n, char a, char b, char c);
int max_elem_vect(int *v, int i, int j);
void interclasare(int *v, int i, int m, int j);
void sortare_pi(int *v, int i, int j);
void afisare_vect(int *v, int n);
int cautare_binara(int *v, int i, int j, int x);
int nr_aparitii_element(int *v, int i, int j, int x);
int cautare_binara_prima_aparitie(int *v, int i, int j, int x);
int cautare_binara_ultima_aparitie(int *v, int i, int j, int x);
int nr_aparitii_nesortat(int *v, int i, int j, int x);


int main() {
	int v[] = {3, 82, 4, 82, -2, 82, 101, 7, 900, 82};
	// Hanoi(3, 'a', 'b', 'c');
	// printf("Max = %d\n", max_elem_vect(v, 0, 9));
	// sortare_pi(v, 0, 9);
	int cautat = 82;
	//sortare_pi(v, 0, 9);
	afisare_vect(v, 9);
	// printf("indexul lui %d este %d\n", cautat, cautare_binara(v, 0, 9, cautat));
	//printf("numarul de aparitii ale lui %d in vectorul sortat este %d\n", cautat, nr_aparitii_element(v, 0, 9, cautat));
	printf("numarul de aparitii ale lui %d in vectorul nesortat este %d\n", cautat, nr_aparitii_nesortat(v, 0, 9, cautat));
}

void Hanoi(int n, char a, char b, char c) {
	if (n > 0) {
		Hanoi(n-1, a, c, b);
		printf("Muta %c -> %c\n", a, b);
		Hanoi(n-1, c, b, a);
	}
}

int max_elem_vect(int *v, int i, int j) {
	if (i == j) {
		return v[i];
	}
	int m = (i + j) / 2;
	return max(max_elem_vect(v, i, m), max_elem_vect(v, m + 1, j));
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

void afisare_vect(int *v, int n) {
	int i = 0;
	for (; i <= n; i++) {
		printf("v[%d] = %d\n ", i, v[i]);
	}
}

int cautare_binara(int *v, int i, int j, int x) {
	if (i > j) {
		return -1;
	}
	else {
		int m = (i + j) / 2;
		if (v[m] == x) {
			return m;
		}
		else {
			if (v[m] > x) {
				return cautare_binara(v, i, m - 1, x);
			}
			else {
				return cautare_binara(v, m + 1, j, x);
			}
		}
	}
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

int nr_aparitii_nesortat(int *v, int i, int j, int x) {
	if (i > j) {
		return 0;
	}
	else {
		int m = (i + j) / 2;
		if (v[m] == x) {
			return 1 + nr_aparitii_nesortat(v, i, m - 1, x) + nr_aparitii_nesortat(v, m + 1, j, x);
		}
		else {
			return nr_aparitii_nesortat(v, i, m - 1, x) + nr_aparitii_nesortat(v, m + 1, j, x);
		}
	}
}