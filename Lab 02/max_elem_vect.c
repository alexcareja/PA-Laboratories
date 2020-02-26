#include <stdlib.h>
#include <stdio.h>

#define max(a, b) (((a) < (b)) ? (b) : (a))

int max_elem_vect(int *v, int i, int j);

int main() {
	int v[] = {3, 82, 4, 82, -2, 82, 101, 7, 900, 82};
	printf("Max = %d\n", max_elem_vect(v, 0, 9));
	return 0;
}

int max_elem_vect(int *v, int i, int j) {
	if (i == j) {
		return v[i];
	}
	int m = (i + j) / 2;
	return max(max_elem_vect(v, i, m), max_elem_vect(v, m + 1, j));
}