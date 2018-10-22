#include <stdio.h>

void fun() {
	printf("(^ u ^)~");
}

int main() {
	int i,n;
	printf("How many times? \n");
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		fun();
	}
}
