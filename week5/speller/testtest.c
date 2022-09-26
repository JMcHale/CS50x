#include <strings.h>
#include <stdio.h>

int main(void)
{
    char *word = "choco";

    char *word2 = "choco     ";

    printf("The match is: %i\n", strcasecmp(word,word2));

}