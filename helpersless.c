#include "helpers.h"
#include <math.h>



// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //average
            float average = round(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;
            //save the pixels
            image[i][j].rgbtRed = round(average);
            image[i][j].rgbtGreen = round(average);
            image[i][j].rgbtBlue = round(average);
        }
    }
    return;
}


// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //edit the pixels
            float newred = (0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue);
            float newgreen = (0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue);
            float newblue = (0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue);
            //round up
            newred = roundf(newred);
            newgreen = roundf(newgreen);
            newblue = roundf(newblue);
            //make sure no pixel is more then 255
            if (newred > 255)
            {
                newred = 255;
            }
            if (newgreen > 255)
            {
                newgreen = 255;
            }
            if (newblue > 255)
            {
                newblue = 255;
            }
            //save the pixels
            image[i][j].rgbtRed = (int)newred;
            image[i][j].rgbtGreen = (int)newgreen;
            image[i][j].rgbtBlue = (int)newblue;
        }
    }
    return;
}

// Reflect image horizontally

void reflect(int height, int width, RGBTRIPLE image[height][width])
{


    for (int i = 0; i < height; i++)
    {
        //create a temp variable
        RGBTRIPLE temp;
        //swap the pixels
        for (int j = 0; j < width / 2; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create a new struct
    RGBTRIPLE blur[height][width];
    //Preparing average variables
    float averageRed;
    float averageGreen;
    float averageBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //bluring the inside
            if (i > 0 & i < height - 1 & j > 0 & j < width - 1)
            {
                averageRed = round(image[i][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed +
                                   image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed +
                                   image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9;

                averageGreen = round(image[i][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                                     image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen +
                                     image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                     image[i + 1][j + 1].rgbtGreen) / 9;

                averageBlue = round(image[i][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                    image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue +
                                    image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9;

                blur[i][j].rgbtRed = round(averageRed);
                blur[i][j].rgbtGreen = round(averageGreen);
                blur[i][j].rgbtBlue = round(averageBlue);
            }
            //bluring corner (up - left)
            else if (i == 0 & j == 0)
            {
                averageRed = round(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed +
                                   image[i + 1][j + 1].rgbtRed) / 4;

                averageGreen = round(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                     image[i + 1][j + 1].rgbtGreen) / 4;

                averageBlue = round(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                    image[i + 1][j + 1].rgbtBlue) / 4;

                blur[i][j].rgbtRed = round(averageRed);
                blur[i][j].rgbtGreen = round(averageGreen);
                blur[i][j].rgbtBlue = round(averageBlue);
            }
            //bluring corner (down - left)
            else if (i == height - 1 & j == 0)
            {
                averageRed = round(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed +
                                   image[i - 1][j + 1].rgbtRed) / 4;

                averageGreen = round(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                     image[i - 1][j + 1].rgbtGreen) / 4;

                averageBlue = round(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                    image[i - 1][j + 1].rgbtBlue) / 4;

                blur[i][j].rgbtRed = round(averageRed);
                blur[i][j].rgbtGreen = round(averageGreen);
                blur[i][j].rgbtBlue = round(averageBlue);
            }
            //bluring corner (down - right)
            else if (i == height - 1 & j == width - 1)
            {
                averageRed = round(image[i][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed +
                                   image[i][j - 1].rgbtRed) / 4;

                averageGreen = round(image[i][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                     image[i][j - 1].rgbtGreen) / 4;

                averageBlue = round(image[i][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                    image[i][j - 1].rgbtBlue) / 4;

                blur[i][j].rgbtRed = round(averageRed);
                blur[i][j].rgbtGreen = round(averageGreen);
                blur[i][j].rgbtBlue = round(averageBlue);

            }
            //bluring corner (up - right)           
            else if (i == 0 & j == width - 1)
            {
                averageRed = round(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
                                   image[i + 1][j].rgbtRed) / 4;

                averageGreen = round(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                                     image[i + 1][j].rgbtGreen) / 4;

                averageBlue = round(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                                    image[i + 1][j].rgbtBlue) / 4;

                blur[i][j].rgbtRed = round(averageRed);
                blur[i][j].rgbtGreen = round(averageGreen);
                blur[i][j].rgbtBlue = round(averageBlue);
            }
            //bluring first row
            else if (i == 0 & j > 0 & j < width - 1)
            {
                averageRed = round(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
                                   image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed) / 6;

                averageGreen = round(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                                     image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen) / 6;

                averageBlue = round(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                                    image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue) / 6;

                blur[i][j].rgbtRed = round(averageRed);
                blur[i][j].rgbtGreen = round(averageGreen);
                blur[i][j].rgbtBlue = round(averageBlue);
            }
            //bluring last row
            else if (i == height - 1 & j > 0 & j < width - 1)
            {
                averageRed = round(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed +
                                   image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed) / 6;

                averageGreen = round(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                                     image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen) / 6;

                averageBlue = round(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                                    image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue) / 6;

                blur[i][j].rgbtRed = round(averageRed);
                blur[i][j].rgbtGreen = round(averageGreen);
                blur[i][j].rgbtBlue = round(averageBlue);
            }
            //bluring first column
            else if (i > 0 & i < height - 1 & j == 0)
            {
                averageRed = round(image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                   image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed) / 6;

                averageGreen = round(image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                     image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen) / 6;

                averageBlue = round(image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                    image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue) / 6;

                blur[i][j].rgbtRed = round(averageRed);
                blur[i][j].rgbtGreen = round(averageGreen);
                blur[i][j].rgbtBlue = round(averageBlue);
            }
            //bluring last column
            else if (i > 0 & i < height - 1 & j == width - 1)
            {
                averageRed = round(image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed +
                                   image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed) / 6;

                averageGreen = round(image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                                     image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen) / 6;

                averageBlue = round(image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                                    image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue) / 6;

                blur[i][j].rgbtRed = round(averageRed);
                blur[i][j].rgbtGreen = round(averageGreen);
                blur[i][j].rgbtBlue = round(averageBlue);
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blur[i][j].rgbtRed;
            image[i][j].rgbtGreen = blur[i][j].rgbtGreen;
            image[i][j].rgbtBlue = blur[i][j].rgbtBlue;
        }
    }
    return;
}
