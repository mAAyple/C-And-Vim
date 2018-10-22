#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
int main(){
	char home[20];
	char away[20];
	char type;
	int count;
	int inning;
	int i;
	int j;
	char score[3][10] = {0};
	score[0][9] = 'R';
	srand(time(0));
	printf("---------------------------------------------------------------------------\n");
	printf("                               ISU BASEBALL                                \n");
	printf("---------------------------------------------------------------------------\n");
	printf("Enter a home team of your choosing: \n");
	scanf("%s", home);
	printf("Enter a away team of your choosing: \n");
	scanf("%s", away);
	printf("Would you like manual(M) or automatic(A) \n");
	scanf(" %c", &type);
	if(type == 'm' || type == 'M'){
		while(count != '0'){
			printf("What inning would you like to edit? \n");
			scanf("%d", &inning);
			printf("What is the score for %s for inning %d ? \n", home, inning);
			scanf("%d", &i);
			score[1][inning] = i;
			printf("Inning:	");
			for(count = 1; count < 10 ; count++){
				score[0][count] = count;
				printf(" %d ", score[0][count]);
			}

			printf(" %d ", score[0][9]);

			printf("\n");
			printf("%s	", home);
			for(count = 1; count < 10 ; count++){
				printf(" %d ", score[1][count]);
			}
			printf("\n");
			printf("%s 	", away);
			for(count = 1; count < 10 ; count++){
				printf(" %d ", score[2][count]);
			}
			printf("\n");
			printf("What is the score for %s for inning %d ? \n", away, inning);
			scanf("%d", &j);
			score[2][inning] = j;
			printf("Inning:	");
			for(count = 1; count < 10 ; count++){
				score[0][count] = count;
				printf(" %d ", score[0][count]);
			}
			printf("%c", score[0][9]);
			printf("\n");
			printf("%s	", home);
			for(count = 1; count < 10 ; count++){
				printf(" %d ", score[1][count]);
			}
			printf("\n");
			printf("%s 	", away);
			for(count = 1; count < 10 ; count++){
				printf(" %d ", score[2][count]);
			}
			printf("\n");
			printf("Enter 0 to save and quit, or enter 1 to continue");
			scanf("%d", &count);
			if((count) == '0') {
				printf("The final score:");
				return count == '0';
			}
		}
	}
	else if(type == 'a' || type == 'A'){
		for(count = 0; count <= 9; count++) {
			score[1][count] = fabs(rand() % 10);
			score[2][count] = fabs(rand() % 10);
			score[0][count] = count;
		}
			printf("Inning:	");
			for(count = 1; count < 10 ; count++){
				score[0][count] = count;
				printf(" %d ", score[0][count]);
			}
			printf("%c", score[0][9]);
			printf("\n");
			printf("%s	", home);
			for(count = 1; count < 10 ; count++){
				printf(" %d ", score[1][count]);
			}
			printf("\n");
			printf("%s 	", away);
			for(count = 1; count < 10 ; count++){
				printf(" %d ", score[2][count]);
			}
			printf("\n");

	}
}


