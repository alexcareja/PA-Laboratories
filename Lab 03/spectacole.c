#include <stdlib.h>
#include <stdio.h>

int main() {
	int dim = 6;
	int s[] = {10, 11, 12, 14, 16, 17};
	int t[] = {11, 13, 13, 18, 17, 19};
	int indexes[] = {0, 1, 2, 3, 4, 5};
	int i , j, k, end;
	for(i = 0; i < dim; i++) {
		for(j = i + 1; j < dim; j++) {
			if(t[j] < t[i]) {
				k = indexes[i];
				indexes[i] = indexes[j];
				indexes[j] = k;
			}
		}
	}
	for(i = 0; i < dim;) {
		printf("Rulez film de la ora %d la ora %d\n", s[indexes[i]], t[indexes[i]]);
		end = t[indexes[i]];
		while (i < dim && s[indexes[i]] < end) {
			i++;
		}
	}

	return 0;
}