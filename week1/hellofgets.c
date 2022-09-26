#include <stdio.h>

int main(void){
    char name[25];
    printf("What's your name? \n");
    fgets(name, 25, stdin);
    printf("Hello, %s\n", name);
}
