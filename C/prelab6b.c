#include <stdio.h>
int main() {
	int inp;
	int count = 0;
	int fib1;
	int fib2 = 0;
	int fib3 = 1;
	int res = 0;
	int res2 = 1;
	printf("Enter in a non-zero number: \n\n");
	scanf("%d", &inp);
	for(count = 1; count <= inp; ++count) {
		res = count + res;
	}
	for(count = 1; count <= inp; ++count) {
		res2 = count * res2;
	}
	if((inp == 0)) {
		fib1 = 0;
	}
	else if((inp == 1)){
		fib1 = 1;
	}
	else if((inp == 2)){
		fib1 = 1;
	}
	else if(inp != 0 && inp != 1 && inp != 2){
		for(count = 2; count < inp; ++count) {
			fib1 = fib2 + fib3;
			fib2 = fib3;
			fib3 = fib1;
		}
	}
	printf("+=================================================+");
	printf("\n\n Here is your Sum of the range:\n");
	printf("%d \n\n\n", res);
	printf("Here is your factorial: \n\n");
	printf("%d \n\n\n", res2);
	printf("Here is the nth number in the fibonacci sequence: \n\n");
	printf("%d \n\n\n", fib1);
	

}

