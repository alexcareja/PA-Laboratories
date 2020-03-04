#include <stdlib.h>
#include <stdio.h>

int main() {
	int dim = 8;
	int l[] = {3, 2, 3, 1, 6, 4, 3, 1};
	char c[] = {'a', 'b', 'c', 'a', 'b', 'c', 'a', 'b'};
	int indexes[] = {0, 1, 2, 3, 4, 5, 6, 7};
	int i , j , k;
	char current_colour;
	for(i = 0; i < dim; i++) {
		for(j = 0; j < dim; j++) {
			if(l[indexes[i]] > l[indexes[j]]) {
				k = indexes[i];
				indexes[i] = indexes[j];
				indexes[j] = k;
			}
		}
	}

	for(i = 0; i < dim;) {
		printf("Cubul de l=%d si culoare %c\n", l[indexes[i]], c[indexes[i]]);
		current_colour = c[indexes[i]];
		while(i < dim && c[indexes[i]] == current_colour) {
			i++;
		}
	}

	return 0;
}
