// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{

    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open file input.wav, in read only mode hence fopen(argv[1], "r"), create the pointer *input to this file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    //Initialise an array to store the data in the WAV file header
    //uint8_t is a data type that stores an 8 bit unsigned (not negative) integer, this means it takes up 1 byte
    int n = HEADER_SIZE;
    uint8_t header[n];

    //We then need to read what's in the input.wav header and put that in this header
    //this doesn't need to be assigned as fread does this itself, essentially this means read the value of the file input and write it into the array header, in increments of 1 byte, with "n" of elements
    fread(header, sizeof(uint8_t), n, input);


    //Lets see what's in the header! (integer values)
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", header[i]);
    }

    //We then need to write this into the output file, this either has to be done by a loop or ALL AT ONCE, as header is an array. Otherwise it doesn't copy correctly
    fwrite(header, n, 1, output);

    //To test fread and fwrite
    /*
    FILE *testtxt;
    int testc[] = {5, 4, 3, 2, 1};
    int buffer[5];
    for (int i = 0; i < 5; i++)
    {
        printf("%i", testc[i]);
    }
    testtxt = fopen("file.txt", "w+");
    fwrite(testc, sizeof(int), 5, testtxt);
    fseek(testtxt, 0, SEEK_SET);
    fread(buffer, sizeof(int), 5, testtxt);
    for (int i = 0; i < 5; i++)
    {
        printf("%i", buffer[i]);
    }
    */

    // TODO: Read samples from input file and write updated data to output file
    //We need to read each sample from the input WAV file, then write this to the output file
    //Need a way to loop through the samples in the WAV, so we need a way to determine number of samples
    //make a buffer variable that fits an int16_t


    int16_t buffer;
    while(fread(&buffer, sizeof(int16_t), 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }





    // Close files
    fclose(input);
    fclose(output);
}
