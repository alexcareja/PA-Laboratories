#include <stdlib.h>
#include <stdio.h>

int cautare_binara(int *v, int i, int j, int x);

int main() {
	int v[] = {0, 1, 2, 3, 44, 222, 321, 900, 901, 902};
	int cautat = 321;
	printf("indexul lui %d este %d\n", cautat, cautare_binara(v, 0, 9, cautat));
	return 0;
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