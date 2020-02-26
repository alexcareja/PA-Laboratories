#include <stdlib.h>
#include <stdio.h>

void Hanoi(int n, char a, char b, char c);

int main() {
	Hanoi(3, 'a', 'b', 'c');
}

void Hanoi(int n, char a, char b, char c) {
	if (n > 0) {
		Hanoi(n-1, a, c, b);
		printf("Muta %c -> %c\n", a, b);
		Hanoi(n-1, c, b, a);
	}
}