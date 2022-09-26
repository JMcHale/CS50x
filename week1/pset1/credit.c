#include <stdio.h>
#include <string.h>

//initialise get_card_number function
long get_card_number(void);
int check_valid(long check_valid);


int main(void)
{
    //get the users card number input
    char card_make[20];
    long card_number_value = get_card_number();

    //check if the card is valid according to formula
    printf("Checking card number: %li\n", card_number_value);
    int valid_check = check_valid(card_number_value);

    if (valid_check == 0)
    {
        printf("INVALID\n");
        return(0);
    }

    int startnumber = 0;
    int digitnumber = 1;
    long card_number = card_number_value;

    do
    {
        card_number = card_number / 10;
        digitnumber++;
        printf("Card Number is: %li\n", card_number);
    }
    while(card_number > 10);

    startnumber = card_number;

    printf("The startnumber is: %i\n", startnumber);

    printf("There are %i Digits\n", digitnumber);

    printf("Start Number in main is: %i\n", startnumber);

    if (digitnumber == 15)
    {
        //printf("First Digit Is: %li\n", card_number_value / 100000000000000 % 10);
        //printf("Second Digit Is: %li\n", card_number_value / 10000000000000 % 10);
        if((card_number_value / 100000000000000 % 10 == 3) && ((card_number_value / 10000000000000 % 10 == 7) || (card_number_value / 10000000000000 % 10 == 4)))
        {
            //printf("First Digit Is: %li", card_number_value / 100000000000000 % 10);
        strcpy(card_make, "AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (digitnumber == 13)
    {
        if(card_number_value / 1000000000000 % 10 == 4)
        {
           strcpy(card_make, "VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }

    }
    else if (digitnumber == 16)
    {
        if (startnumber == 4)
        {
            strcpy(card_make, "VISA\n");
        }
        else
        {
            if((card_number_value / 1000000000000000 % 10 == 5) && ((card_number_value / 100000000000000 % 10 == 1) || (card_number_value / 100000000000000 % 10 == 2) || (card_number_value / 100000000000000 % 10 == 3) || (card_number_value / 100000000000000 % 10 == 4) || (card_number_value / 100000000000000 % 10 == 5)))
            {
            strcpy(card_make, "MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }
    else
    {
        printf("INVALID\n");
    }

    printf("%s", card_make);

}



//Prompt the user for input until a card number is entered in a number format
long get_card_number(void)
{

    long card_number_input;
    do
    {
        printf("Please enter card number: ");
        scanf("%li", &card_number_input);
    }
    while(card_number_input<0);
    return card_number_input;
}

int check_valid(long check_valid)
{
    int even_sum = 0;
    int odd_sum = 0;
    int valid = 1;

    /*
    int digit1 = check_valid % 10;
    int digit2 = (check_valid % 100 - check_valid % 10) / 10;
    int digit3 = (check_valid % 1000 - check_valid % 100 + check_valid % 10) / 100;
    int digit4 = check_valid % 10000 - check_valid % 1000 + check_valid % 100 + check_valid % 10;
    int digit5 = check_valid % 100000;
    int digit6 = check_valid % 1000000;
    int digit7 = check_valid % 10000000;
    int digit8 = check_valid % 100000000;
    int digit9 = check_valid % 1000000000;
    int digit10 = check_valid % 10000000000;
    int digit11 = check_valid % 100000000000;
    int digit12 = check_valid % 1000000000000;
    int digit13 = check_valid % 10000000000000;
    int digit14 = check_valid % 100000000000000;
    int digit15 = check_valid % 1000000000000000;
    int digit16 = check_valid % 10000000000000000;
    */

    for (int x = 1; x < 17; x++)
    {
        //get digits
        int digit = check_valid % 10;
        check_valid = check_valid / 10;
        printf("Digit %i is: %i\n", x, digit);

        //Add the digits of the digits of every other digit, multipled by 2
        //% 2 checks if the digit is even or not
        if (x % 2 == 0)
        {
            even_sum = even_sum + ((digit * 2) % 10) + (((digit * 2) / 10) % 10);
        }
        else
        {
            odd_sum = odd_sum + (digit % 10) + ((digit / 10) % 10);
        }

        printf("Sum of every other digit doubled is: %i\n", even_sum);
        printf("Sum of every odd digit is: %i\n", odd_sum);
        printf("Total is: %i\n", even_sum + odd_sum);

    }

    if ((even_sum + odd_sum) % 10 == 0)
    {
        valid = 1;
    }
    else
    {
        valid = 0;
    }

    return valid;
}