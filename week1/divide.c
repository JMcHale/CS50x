#include <stdio.h>

int main(void){
    int x;
    int y;
    printf("X: ");
    scanf("%i", &x);
    printf("Y: ");
    scanf("%i", &y);
    float z = (float) x / (float) y;
    printf("Answer is: %f\n", z);

}