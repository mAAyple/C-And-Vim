#include <stdio.h>
#include <string.h>
int main() {
  char str[6] = {' ', ' ', ' ', ' ', ' ', '\0'};
  printf("Enter a five letter string! \n");
  printf("Enter the first Letter\n");
  scanf("%s", &str[0]);
  printf("Enter the second Letter\n");
  scanf("%s", &str[1]);
  printf("Enter the third Letter\n");
  scanf("%s", &str[2]);
  printf("Enter the fourth Letter\n");
  scanf("%s", &str[3]);
  printf("Enter the fifth Letter\n");
  scanf("%s", &str[4]);
  printf("Here is your string!\n");
  printf("%s\n", str);
}
