   1 #include <stdio.h>
   2 #include <math.h>
   3 int main() { 
   4     char ch;
   5     //char chr;
   6     double inp1;
   7     double inp2;
   8     double inp3;
   9     double inp4;
  10     float res;
  11     printf("Would you like to average 4 numbers, or enter 4 numbers for a suprise! \n\n");
  12     printf("Enter 1 for averages, 2 for suprise: \n");
  13     scanf("%c", &ch);
  14     if ((ch) ==  '1') { 
  15         printf("Enter your first non-zero number\n\n");
  16         scanf(" %lf", &inp1);
  17   
  18         printf("Enter your second non-zero number\n\n");
  19         scanf(" %lf", &inp2);
  20 
  21         printf("Enter your third non-zero number\n\n");
  22         scanf(" %lf", &inp3);
  23 
  24         printf("Enter your last non-zero number\n\n");
  25         scanf(" %lf", &inp4);
  26 
  27         res = (inp1 + inp2 + inp3 + inp4) / 4;
  28 
  29         printf("Here is your average! \n\n");
  30         printf("%f", res);
  31     } 
  32     else if ((ch) == '2') { 
  33           
  34     } 
  35 }
