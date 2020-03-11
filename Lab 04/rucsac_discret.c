#include <stdlib.h>
#include <stdio.h>

#define INF 2147483647

int cap = 50;
int M[] = {10, 30, 20};
int V[] = {60, 120, 100};
int D(int i, int cp, int *ob);
int max(int a, int b);

int main() {
	int *o = (int *) calloc(4, sizeof(int));
	printf("Valoarea maxima = %d\n", D(2, cap, o));
	int i = 0;
	printf("Am ales obiectele: ");
	for (; i < 3; i++) {
		if (o[i]) {
			printf("%d ", i);
		}
	}
	return 0;
}

int max(int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}

int D(int i, int cp, int *ob) {
	if (cp == 0) {
		return 0;
	}
	if (cp < 0) {
		return -INF;
	}
	if (i == 0) {
		if (cp - M[i] >= 0) {
			return V[0];
		}
		else {
			return 0;
		}
	}
	if (D(i-1, cp, ob) > D(i - 1, cp - M[i], ob) + V[i]) {
		return D(i - 1, cp, ob);
	}
	else {
		ob[i] = 1;
		return D(i - 1, cp - M[i], ob) + V[i];
	}
}