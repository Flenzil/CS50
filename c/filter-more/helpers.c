#include "helpers.h"
#include <math.h>
#include <stdio.h>

void Sobel(int sum[3], int height, int width, int G[3][3], RGBTRIPLE image[height][width], int h, int w);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Renaming for brevity, making sure to copy the pointer so future changes are reflected in the originals.
            BYTE *red = &image[h][w].rgbtRed;
            BYTE *blue = &image[h][w].rgbtBlue;
            BYTE *green = &image[h][w].rgbtGreen;

            // Calculate average of rgb channels.
            int avg = (int) round((*red + *blue + *green) / 3.0);

            // Assign average to each rgb channel
            *red = avg;
            *blue = avg;
            *green = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE swap;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++)
        {
            // Swap leftmost pixels with rightmost pixels.
            swap = image[h][width - 1 - w];
            image[h][width - 1 - w] = image[h][w];
            image[h][w] = swap;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Arrays to store averages. Avoid storing averages directly into image until all averages are completed.
    float avgr[height][width];
    float avgg[height][width];
    float avgb[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Loops to create sum values for each colour to create average.
            int sumr = 0;
            int sumg = 0;
            int sumb = 0;

            float den = 0; // Denominator for average calculation.
            for (int i = -1; i <= 1; i++)
            {
                if (h + i < 0 || h + i >= height)
                    continue;

                for (int j = -1; j <= 1; j++)
                {
                    if (w + j < 0 || w + j >= width)
                        continue;

                    // For each pixel sums all adjacent pixel values
                    sumr += image[h + i][w + j].rgbtRed;
                    sumg += image[h + i][w + j].rgbtGreen;
                    sumb += image[h + i][w + j].rgbtBlue;
                    den++;
                }
            }
            // Calculate averages.
            avgr[h][w] = (int) round(sumr / den);
            avgg[h][w] = (int) round(sumg / den);
            avgb[h][w] = (int) round(sumb / den);
        }
    }

    // Fill image with averaged pixels.
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtRed = avgr[h][w];
            image[h][w].rgbtGreen = avgg[h][w];
            image[h][w].rgbtBlue = avgb[h][w];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Define kernels
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE sum[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {

            int sumx[3];
            int sumy[3];

            // Fills sumx and sumy with Sobel values.
            Sobel(sumx, height, width, Gx, image, h, w);
            Sobel(sumy, height, width, Gy, image, h, w);

            // Calculates final values for r, g and b channels
            int gr = round(pow(pow(sumx[0], 2) + pow(sumy[0], 2), 0.5));
            int gg = round(pow(pow(sumx[1], 2) + pow(sumy[1], 2), 0.5));
            int gb = round(pow(pow(sumx[2], 2) + pow(sumy[2], 2), 0.5));

            // Sets maximum value to 255
            sum[h][w].rgbtRed = (gr > 255) ? 255 : gr;
            sum[h][w].rgbtGreen = (gg > 255) ? 255 : gg;
            sum[h][w].rgbtBlue = (gb > 255) ? 255 : gb;
        }
    }
    // Assigns values to final image.
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = sum[h][w];
        }
    }
    return;
}

void Sobel(int sum[3], int height, int width, int G[3][3], RGBTRIPLE image[height][width], int h, int w)
{
    // For each pixel (h, w), applies Sobel operator. Treats edge cases as though image is surrounded by black pixels.
    RGBTRIPLE im;
    RGBTRIPLE black_pixels;

    int sumr = 0;
    int sumg = 0;
    int sumb = 0;

    black_pixels.rgbtRed = 0;
    black_pixels.rgbtGreen = 0;
    black_pixels.rgbtBlue = 0;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (w + j < 0 || w + j >= width || h + i < 0 || h + i >= height)
            {
                im = black_pixels;
            }
            else
            {
                im = image[h + i][w + j];
            }

            sumr += G[i + 1][j + 1] * im.rgbtRed;
            sumg += G[i + 1][j + 1] * im.rgbtGreen;
            sumb += G[i + 1][j + 1] * im.rgbtBlue;
        }
    }

    sum[0] = sumr;
    sum[1] = sumg;
    sum[2] = sumb;
}