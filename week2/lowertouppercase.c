#include <stdio.h>
#include <string.h>

int main(void)
{
    char word[25];
    printf("Before:");
    scanf("%s", word);

    for (int i = 0, na = strlen(word); i < na; i++)
    {
        //printf("%c\n", word[i]);
        //printf("Letter: %i\n", i);
        if (word[i] >= 'a' && word[i] <= 'z')
        {
            printf("%c", word[i] - 32);
        }
        else
        {
            printf("%c", word[i]);
        }
    }
    printf("\n");

    printf("After: %s\n", word);
}