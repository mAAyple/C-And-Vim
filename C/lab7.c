#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int main() {
	int i;
	int j;
	int tmp;
	int random[99];
	srand(time(0));
	printf("\n\n_________________________________________________________________________________________\n");
	printf("                                     Random Numbers\n");
	printf("_________________________________________________________________________________________\n");

	for(i = 0; i < 100; i ++){
		random[i] = rand() % 50;
		printf("%d  ", random[i]);
	}
	printf("\n");
	//for(i = 0; i < 100; i++){
	//	printf(" %d ", random[i]);
	//}
	for (i = 0; i < 100; i++){
		for (j = 0; j < 100; j++){
			if (random[j] < random[i]){
				tmp = random[i];
				random[i] = random[j];
				random[j] = tmp;
			}
		}
	}

	printf("\n\n_________________________________________________________________________________________\n");
	printf("                                    Sorted Numbers\n");
	printf("_________________________________________________________________________________________\n");

	for(i = 0; i < 100; i++){
		printf("%d  ", random[i]);
	}
	tmp = 0;
	for(i = 0; i < 99; i++){
		j = i + 1;
		if (random[i] == random[j]){
				tmp++;
		}
	}

	printf("\n\n_________________________________________________________________________________________\n");
	printf("                            Here are the number of pairs                                 \n");
	printf("_________________________________________________________________________________________\n");
	printf("                                          %d                                             \n", tmp);
	printf("_________________________________________________________________________________________\n");


}
