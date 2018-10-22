#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){
	int inpn;
	int count;
	srand(time(0));
	int trial = 0;
	printf("Enter positive number of trails: \n\n");
	scanf("%d", &inpn);
	for(count = 0; count < inpn; count++){
		int ra = rand() % 100000;
		printf("The random: %d ", ra);
		trial = 0;
		while(ra > 1){
			if((ra % 2) == 1) {
				trial++;
				ra = (3 * ra) + 1;
				
			}
			else if((ra % 2) == 0){
				trial++;
				ra =  ra / 2;
				
			}
		}
	printf(" Trial: %d \n\n", trial);
	}

}
