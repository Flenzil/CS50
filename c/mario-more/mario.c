#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int row = 0; row < height; i++)
    {
        for (int j = height - row - 1; j > 0; j--)
        {
            printf(" ");
        }
        for (int k = 0; k <= row; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int l = 0; l <= row; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}
