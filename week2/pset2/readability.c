#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    char line[400];
    int length = 0;
    int letters1 = 0;
    int letters = 0;
    int spaces = 0;
    int sentances = 0;

    printf("Text: ");
    fgets(line, sizeof(line), stdin);

    //printf("Text is: %s\n", line);

    //Find where text ends
    for (int i = 0, size = sizeof(line); i < size; i++)
    {
        if (line[i] == '\0')
        {
            break;
        }
        else
        {
            length++;
        }
    }

    /*
    printf("Text is ACTUALLY: %lu\n", strlen(line));
    */

    //printf("Text is of length: %i\n", length);

    for (int i = 0; i < length; i++)
    {
        if (isalpha(line[i]))
        {
            letters1++;
        }
        else if (isspace(line[i]))
        {
            spaces++;
        }
        else if (line[i] == '!' || line[i] == '?' || line[i] == '.')
        {
            sentances++;
        }
    }

    //printf("%i letter(s)\n", letters1);
    //printf("%i word(s)\n", spaces);
    //printf("%i sentances(s)\n", sentances);

    float lperw = (float) letters1 / ((float) spaces / 100);
    //printf("L is: %f\n", lperw);

    float sperw = (float) sentances / ((float) spaces / 100);
    //printf("S is: %f\n", sperw);

    float index = 0.0588 * lperw - 0.296 * sperw - 15.8;

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
       printf("Grade %i\n", (int) round(index));
    }
    /*
    for (int i = 0; i < length; i++)
    {
        if (line[i] == ' ' || line[i] == ',' || line[i] == '!' || line[i] == '?' || line[i] == '\'' || line[i] == '.' || line[i] == ';')
        {

        }
        else
        {
            letters++;
        }
    }

    printf("There are %i letters in the text\n", letters);
    */
}