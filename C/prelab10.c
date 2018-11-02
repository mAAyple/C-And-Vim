#include <stdio.h>
#include <stdlib.h>

struct cato{
	char catbreed[20];
	char name[20];
	char color[20];
	char eye_color[20];
	int num_legs;
};

int main(){
	struct cato ct;
	printf("What is your cat's breed? \n\n");
	scanf("%s", ct.catbreed);

	printf("What is your cat's name? \n\n");
	scanf("%s", ct.name);

	printf("What is your cat's color? \n\n");
	scanf("%s", ct.color);


	printf("What is the color of your cat's eyes? \n\n");
	scanf("%s", ct.eye_color);


	printf("How many legs does your cat have? \n\n");
	scanf("%d", &ct.num_legs);

	printf("%s\n", ct.catbreed);

	printf("%s\n", ct.name);

	printf("%s\n", ct.color);

	printf("%s\n", ct.eye_color);

	printf("%d\n", ct.num_legs);
}
