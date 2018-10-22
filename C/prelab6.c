#include <stdio.h>
#include <math.h>
int main() { 
    int num = 1;
    float res;
    float fres;
    int count;
    while(num >= 1){ 
    	printf("Enter your non-zero number, enter 0 to quit! \n\n");
    	scanf("%d", &num);
	res = res + num;
	count++;
    }
    fres = res / count;
    printf("Here is your average! \n\n");
    printf("%f", fres);
}
