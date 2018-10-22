#include <stdio.h>
#include <math.h>
int main() {
    int sidea;
    int sideb;
    float sidec;
    float anga;
    float angb;
    float pi = 3.14159263;
    printf("Enter Side Length A \n");
    scanf("%d", &sidea);
    printf("Enter Side Length B \n");
    scanf("%d", &sideb);
    sidec = sqrt(pow(sidea, 2) + pow(sideb, 2));
    printf("Here is your side Length C \n");
    printf("%f \n", sidec);
    printf("Here is your Angel A: \n");
    anga = (atan(sideb / sidea)) * (180 / pi);
    angb = (180 - (anga + 90));
    printf("%f \n", anga);
    printf("And Your angel B: \n");
    printf("%f \n", angb);
}
