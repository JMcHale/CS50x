#include "helpers.h"
#include <math.h>

// Convert image to grayscale
// To convert an individual pixel to its grayscale equivalent... we can use how "close" the colour is to black. For example, #0000FF is fully blue, and fully bright, if we set the other colours to max among them, it should greyscale it?
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int max;

    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            /*
            //To find what the maximum value of RGB is!
            if (image[i][k].rgbtBlue >= image[i][k].rgbtRed && image[i][k].rgbtBlue >= image[i][k].rgbtGreen)
            {
                max = image[i][k].rgbtBlue;
            }
            else if (image[i][k].rgbtRed >= image[i][k].rgbtBlue && image[i][k].rgbtRed >= image[i][k].rgbtGreen)
            {
                max = image[i][k].rgbtRed;
            }
            else
            {
                max = image[i][k].rgbtGreen;
            }
            */

            //To find the average rbg

            max = round(((float) image[i][k].rgbtBlue + (float) image[i][k].rgbtRed + (float) image[i][k].rgbtGreen) / (float) 3);

            image[i][k].rgbtBlue = max;
            image[i][k].rgbtRed = max;
            image[i][k].rgbtGreen = max;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    int sepiaRed;
    int sepiaGreen;
    int sepiaBlue;

    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {

            //Algos to convert red to sepia red, etc... these values are all stored in the intermediary values of sepiaColour
            //Also check if these values are greater than 255, if they are set them to just 255 (algorithm can return numbers that are over 255)

            sepiaRed = round(.393 * (float)image[i][k].rgbtRed + .769 * (float)image[i][k].rgbtGreen + .189 * (float)image[i][k].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            sepiaGreen = round(.349 * (float)image[i][k].rgbtRed + .686 * (float)image[i][k].rgbtGreen + .168 * (float)image[i][k].rgbtBlue);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            sepiaBlue = round(.272 * (float)image[i][k].rgbtRed + .534 * (float)image[i][k].rgbtGreen + .131 * (float)image[i][k].rgbtBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }


            image[i][k].rgbtBlue = sepiaBlue;
            image[i][k].rgbtRed = sepiaRed;
            image[i][k].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    //To reflect a pixel at position (0,0) we have to change its position in the array, to the other end of the full width, don't have to change colour
    for (int i = 0; i < height; i++)
    {
        //We only do this up to width / 2 or we would swap all values again???
        for (int k = 0; k < (width / 2); k++)
        {
            //need to store in a middle value, swap the pixel colour values, and do this for every pixel
            RGBTRIPLE midvalue;

            //store first pixel in midvalue
            midvalue = image[i][k];

            //set first pixel to value of "opposite pixel", the pixel that is the same distance from the end as this one as to the start
            //distance from start is k
            //distance from end (or position of it) is width - (k + 1). Has to be k + 1 to account for the fact width does not start counting at 0, it starts at 1
            image[i][k] = image[i][width - (k + 1)];

            //change the "opposie pixel" to the midvalue
            image[i][width - (k + 1)] = midvalue;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create image copy array
    RGBTRIPLE imageblur[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {

            //First, we have to get an average of all the colour values around a pixel,
            //It would be more efficient to keep a copy of a number of rows (so we're only blurring based on the original colour values), then translating these to the original pixels. To make sure no incorrect blurring occurs lets try 6 rows

            //get an average of the colour values around a pixel (i, k)
            int sumred = 0;
            int sumblue = 0;
            int sumgreen = 0;
            int pix = 0;
            //Height first
            for (int y = -1; y < 2; y++)
            {
                //Then width
                for (int x = -1; x < 2; x++)
                {
                    //check if pixel is valid, if not skip pixel
                    if((i + y) < 0 || (k + x) < 0 || (i + y) >= height || (k + x) >= width)
                    {

                    }
                    else
                    {
                        sumblue += image[i + y][k + x].rgbtBlue;
                        sumred += image[i + y][k + x].rgbtRed;
                        sumgreen += image[i + y][k + x].rgbtGreen;
                        pix++;
                    }
                }
            }

            int avgred = round( (float)sumred / (float)pix);
            int avgblue = round( (float)sumblue / (float)pix);
            int avggreen = round( (float)sumgreen / (float)pix);

            //Copy this to the "new image", while keeping the original intact for now, into pixel position (i, k)
            imageblur[i][k].rgbtBlue = avgblue;
            imageblur[i][k].rgbtRed = avgred;
            imageblur[i][k].rgbtGreen = avggreen;
        }
    }

    //after a whole image copy is done, translate this all back to the original

    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            image[i][k] = imageblur[i][k];
        }
    }

    return;
}
