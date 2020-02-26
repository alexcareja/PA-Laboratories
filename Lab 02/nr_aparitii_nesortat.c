#include <stdlib.h>
#include <stdio.h>

int nr_aparitii_nesortat(int *v, int i, int j, int x);

int main() {
	int v[] = {3, 82, 4, 82, -2, 82, 101, 7, 900, 82};
	int cautat = 82;
	printf("numarul de aparitii ale lui %d in vectorul nesortat este %d\n", cautat, nr_aparitii_nesortat(v, 0, 9, cautat));
	return 0;
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