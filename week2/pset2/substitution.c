#include <stdio.h>
#include <string.h>
#include <ctype.h>

char transformtext(char letter, char *key[]);

int main(int argc, char *argv[])
{

    //Check the right number of inputs are present
    if (argc != 2)
    {
        printf("Please input a key for encryption\n");
        return 1;
    }

    //initialise variables
    int n = strlen (argv[1]);
    int lettersum = 0;
    char line[500];
    int nl = 0;

    //Check the key is exactly 26 characters
    printf("Key input is: %s\n", argv[1]);

    if (n != 26)
    {
        printf("Please input 26 characters for the key\n");
        return 1;
    }

    //Check the key is alphabetical
    for (int i = 0; i < n; i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
            printf("Please input only alphabetical letters!\n");
            return 1;
        }
        else
        {

        }
    }

    //Transform key to UPPERCASE
    for (int i = 0; i < n; i++)
    {
        if (isupper(argv[1][i]) == 0)
        {
            argv[1][i] = argv[1][i] - 32;
        }
        else
        {

        }
    }

    printf("Key input all upper is: %s\n", argv[1]);

    //To check each letter is here once we can sum all the letters, this should equal 2015
    for (int i = 0; i < n; i++)
    {
        lettersum = lettersum + argv[1][i];
    }

    //If not the correct total, reject
    if (lettersum != 2015)
    {
        printf("Please input each letter exactly once!\n");
        return 1;
    }

    printf("Letter sum total is: %i\n", lettersum);


    //Get text input from user
    printf("plaintext: ");

    //remember fgets includes NEW LINE \n at the end
    fgets(line, sizeof(line), stdin);

    //printf("Text input is: %s", line);

    nl = strlen(line);
    printf("Text Length is: %i\n", nl);

    for (int i = 0; i < nl; i++)
    {
        line[i] = transformtext(line[i], argv);
    }

    printf("ciphertext: %s\n", line);
}

//transform ONLY letters via the key, and retain case sensitivity
char transformtext(char letter, char *key[])
{

    //first find what key to use to transform the letter in the line
    //loop through the line
    int letterstart = 65;
    int cn = 0;

    //loop through the alphabet to find what key to use
    for (int z = 0; z < 26; z++)
    {
        //if uppercase match
        if (letter == letterstart + z)
        {
            printf("Letter %c is number %i of the alphabet (minus 1)\n", letter, z);
            cn = z;
            printf("Before, %c ", letter);
            letter = letter + (key[1][cn] - letter);
            printf("After, %c\n", letter);n                                                                                         b
            return letter;
        }
        //if lowercase match
        else if (letter == letterstart + z + 32)
        {
            printf("Letter %c is number %i of the alphabet (minus 1)\n", letter, z);
            cn = z;
            printf("Before, %c ", letter);
            letter = letter + (key[1][cn] - letter) + 32;
            printf("After, %c\n", letter);
            return letter;
        }
    }

    return letter;
}
