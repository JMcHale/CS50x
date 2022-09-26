#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    //Since we know sizes in BYTES, define a new type to easily represent this
    typedef uint8_t BYTE;

    int imagecount = 0;


    //Check if input is in correct form
    if (argc >= 3 || argc == 1)
    {
        printf("Please enter in the form: ./recover <filetorecover>\n");
        return 1;
    }

    printf("Reading: %s\n", argv[1]);

    //Open the specified file, and call it "raw_file"
    FILE *raw_file = fopen(argv[1], "r");

    fseek(raw_file, 0, SEEK_END); // seek to end of file
    int file_size = ftell(raw_file); // get current file pointer
    fseek(raw_file, 0, SEEK_SET); //seek back to beginning

    printf("File is: %i BYTES long\n", file_size);

    //Allocate memory for copied file, the size of what we're going to read in
    BYTE *copy_file = malloc(sizeof(BYTE)*512);

    //To store the name of a file, max 7 characters plus the null
    char filename[8];

    //Need to initialise img pointer now because C is silly
    FILE *img = NULL;

    //read one batch of file, until the end of the file
    while (fread(copy_file, sizeof(BYTE)*512, 1, raw_file) == 1)
    {
        //Check if the "block" of 512 is a new image in the form of JPEG
        if(copy_file[0] == 0xff && copy_file[1] == 0xd8 && copy_file[2] == 0xff && (copy_file[3] & 0xf0) == 0xe0)
        {
            //Block is a new image
            imagecount++;

            //If this is the first image then start copying from here
            if(imagecount == 1)
            {
                //create a new file in the correct format
                sprintf(filename, "%03i.jpg", imagecount - 1);
                img = fopen(filename, "w");

                //write the "mid" buffer file of 512 bytes to the new image
                fwrite(copy_file, sizeof(BYTE)*512, 1, img);

            }
            //if this is not the first image then close the old one, and start a new image
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", imagecount - 1);
                img = fopen(filename, "w");

                //write the "mid" buffer file of 512 bytes to the new image
                fwrite(copy_file, sizeof(BYTE)*512, 1, img);
            }

        }
        //Block is not a new image and as such continue copying the old image from this block, but only if we've found the first image!
        else if (imagecount > 0)
        {
            fwrite(copy_file, sizeof(BYTE)*512, 1, img);
        }
    }

    fclose(img);
    fclose(raw_file);
    free(copy_file);

    printf("There are %i images\n", imagecount);

    return 0;

    //Find the first JPEG indentifier before doing anything else
    /*
    for (int i = 0; i < (file_size / 4); i++)
    {
        if (JPEG identifier found)
        {
            int jpegstart = i;
        }
    }
    */

    /*
    //Find where the header address is that specifies it as a JPEG
    //Do this by checking whether each 512 block of bytes starts with the header identifier
    //If header does start with identifier, record the old image that was being copied, start a new one
    if (header starts with JPEG identifier)
    {
        //write the old image and complete it
        fwrite(oldimagethatwasbeingcopied);

        //create new image file to record
    }
    //If header doesn't start with identifier continue to copy
    else
    {
        //allocate the memory needed to store the file

        //Read the file to an intermediary, this reads it in batches of 512 bytes, the size of an FAT block. This needs to be done ONLY until another JPEG header is found
        fread (&MEMORYADDRESS, sizeof(BYTE), 512, raw_file);
    }
    */

}