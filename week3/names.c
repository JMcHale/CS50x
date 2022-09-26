#include <stdio.h>
#include <string.h>

int main(void)
{
    char names[][10] = {"Barry", "Charlie", "Frankie" , "Zopper"};

    struct Person
    {
        char name[10];
        char number[50];
    }
    person;

    strcpy(person.name, "frankie");
    strcpy(person.number, "01977 620332");

    printf("The person %s has the number %s\n", person.name, person.number);

    struct Thing
    {
        char namey[25];
        int age;
    }
    thang;

    //Declare an array dang, of length 5, and data type of Thing (which contains the namey and age variables)
    struct Thing dang[5];
    strcpy(dang[0].namey, "Frankie");
    dang[0].age = 52;

    printf("%s is %i years old\n", dang[0].namey, dang[0].age);

}