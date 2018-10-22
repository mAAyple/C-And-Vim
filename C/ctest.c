#include <stdio.h>

void hello() {
	printf("Hello Benjamin! \n\n");
}

int main() {
	int i,n;
	printf("How many times? \n");
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		hello();
	}
}
