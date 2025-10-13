#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green and blue
            int average = round(
                (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / (float) 3);

            // Update pixel values
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute sepia values 1. round each calculation 2. make sure nothing is > 255.
            int sepiaRed;
            int sepiaGreen;
            int sepiaBlue;

            sepiaRed = round((image[i][j].rgbtRed * .393) + (image[i][j].rgbtGreen * .769) +
                             (image[i][j].rgbtBlue * .189));

            if (sepiaRed > 255)
                sepiaRed = 255;

            sepiaGreen = round((image[i][j].rgbtRed * .349) + (image[i][j].rgbtGreen * .686) +
                               (image[i][j].rgbtBlue * .168));

            if (sepiaGreen > 255)
                sepiaGreen = 255;

            sepiaBlue = round((image[i][j].rgbtRed * .272) + (image[i][j].rgbtGreen * .534) +
                              (image[i][j].rgbtBlue * .131));

            if (sepiaBlue > 255)
                sepiaBlue = 255;

            // Update each pixel accordingly
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // Blur the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;
            int count = 0;

            if (i - 1 >= 0 && j - 1 >= 0)
            {
                sumR += copy[i - 1][j - 1].rgbtRed;
                sumG += copy[i - 1][j - 1].rgbtGreen;
                sumB += copy[i - 1][j - 1].rgbtBlue;
                count++;
            }

            if (i - 1 >= 0)
            {
                sumR += copy[i - 1][j].rgbtRed;
                sumG += copy[i - 1][j].rgbtGreen;
                sumB += copy[i - 1][j].rgbtBlue;
                count++;
            }

            if (i - 1 >= 0 && j + 1 < width)
            {
                sumR += copy[i - 1][j + 1].rgbtRed;
                sumG += copy[i - 1][j + 1].rgbtGreen;
                sumB += copy[i - 1][j + 1].rgbtBlue;
                count++;
            }

            if (i >= 0 && j - 1 >= 0)
            {
                sumR += copy[i][j - 1].rgbtRed;
                sumG += copy[i][j - 1].rgbtGreen;
                sumB += copy[i][j - 1].rgbtBlue;
                count++;
            }

            sumR += copy[i][j].rgbtRed;
            sumG += copy[i][j].rgbtGreen;
            sumB += copy[i][j].rgbtBlue;
            count++;

            if (i >= 0 && j + 1 >= 0 && j + 1 < width)
            {
                sumR += copy[i][j + 1].rgbtRed;
                sumG += copy[i][j + 1].rgbtGreen;
                sumB += copy[i][j + 1].rgbtBlue;
                count++;
            }

            if (i + 1 >= 0 && i + 1 < height && j - 1 >= 0)
            {
                sumR += copy[i + 1][j - 1].rgbtRed;
                sumG += copy[i + 1][j - 1].rgbtGreen;
                sumB += copy[i + 1][j - 1].rgbtBlue;
                count++;
            }

            if (i + 1 < height)
            {
                sumR += copy[i + 1][j].rgbtRed;
                sumG += copy[i + 1][j].rgbtGreen;
                sumB += copy[i + 1][j].rgbtBlue;
                count++;
            }

            if (i + 1 >= 0 && i + 1 < height && j + 1 >= 0 && j + 1 < width)
            {
                sumR += copy[i + 1][j + 1].rgbtRed;
                sumG += copy[i + 1][j + 1].rgbtGreen;
                sumB += copy[i + 1][j + 1].rgbtBlue;
                count++;
            }

            image[i][j].rgbtRed = round(sumR / (float) count);
            image[i][j].rgbtGreen = round(sumG / (float) count);
            image[i][j].rgbtBlue = round(sumB / (float) count);
        }
    }
    return;
}

