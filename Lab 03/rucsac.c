#include <stdlib.h>
#include <stdio.h>

int main() {
	int R = 50;
	int dim = 3;
	int m[] = {10, 30, 20};
	double v[] = {60, 120, 100};
	int indexes[] = {0, 1, 2};
	int i, j, k;
	for(i = 0; i < dim; i++) {
		for(j = i + 1; j < dim; j++) {
			if(v[indexes[i]] / m[indexes[i]] < v[indexes[j]] / m[indexes[j]]) {
				k = indexes[i];
				indexes[i] = indexes[j];
				indexes[j] = k;
			}
		}
	}
	// for(i = 0; i < dim; i++) {
	// 	printf("%d ", indexes[i]);
	// }
	int current_mass = 0;
	double value = 0;
	for(i = 0; i < dim; i++) {
		if(current_mass + m[indexes[i]] > R) {
			printf("Folosesc obiectul %d in proportie de %f\n", indexes[i] + 1, (R - current_mass) * 1.0 / m[indexes[i]]);
			value += v[indexes[i]] * (R - current_mass) / m[indexes[i]];
			current_mass = R;
			break;
		}
		else {
			current_mass += m[indexes[i]];
			value += v[indexes[i]];
			printf("FOlosesc obiectul %d in totalitate\n", indexes[i] + 1);
		}
	}
	printf("Valoarea optima este: %f", value);
	return 0;
}