#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            BYTE *blue = &image[h][w].rgbtBlue;
            BYTE *red = &image[h][w].rgbtRed;
            BYTE *green = &image[h][w].rgbtGreen;

            if (*blue == 0x00 && *red == 0x00 && *green == 0x00)
            {
                *blue = 0x00;
                *red = 0x00;
                *green = 0x00;
            }
            else
            {
                *blue = 0x00;
                *red = 0xFF;
                *green = 0xFF;
            }
        }
    }
}
