#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){
	char home[20] = { };
	char away[20] = { };
	char type;
	int count;
	int inning;
	int i;
	int j;
	char score[3][10] = {0};
	score[1][10] = 'R';
	srand(time(0));
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
			printf("What is the score for ");
			printf("%s ", home);
			printf("for inning  ");
			printf("%d", inning);
			printf(" ? \n");
			scanf("%d", &i);
			score[2][inning] = i;
			printf("Inning: ");
			for(count = 1; count < 10 ; count++){
				score[1][count] = count;
				printf(" %c ", score[1][count]);
			}
			printf("\n");
			printf("%s", home);
			for(count = 1; count < 10 ; count++){
				printf("%c ", score[2][count]);
			}
			printf("\n");
			printf("%s", away);
			for(count = 1; count < 10 ; count++){
				printf(" %c ", score[3][count]);
			}
			printf("\n");
			printf("What is the score for ");
			printf("%s ", away);
			printf("for inning  ");
			printf("%d", count);
			printf(" ? \n");
			scanf("%d", &j);
			score[3][count] = j;
			for(count = 1; count < 10 ; count++){
				printf(" %c ", score[1][count]);
			}
			printf("\n");
			printf("%s", home);
			for(count = 1; count < 10 ; count++){
				printf(" %c ", score[2][count]);
			}
			printf("\n");
			printf("%s", away);
			for(count = 1; count < 10 ; count++){
				printf(" %c ", score[3][count]);
			}
			printf("Enter 0 to save and quit, or enter c to continue");
			scanf("%d", &count);
		}
	}
	else if(type == 'a' || type == 'A'){
		for(count = 1; count <= 9; count++) {
			score[2][count] = rand() % 1000;
			score[3][count] = rand() % 1000;
			score[1][count] = count;
		}
		for(count = 1; count < 10 ; count++){
			printf(" %c ", score[1][count]);
		}

		for(count = 1; count < 10 ; count++){
			printf(" %c ", score[2][count]);
		}

		for(count = 1; count < 10 ; count++){
			printf(" %c ", score[3][count]);
		}
	}
}


