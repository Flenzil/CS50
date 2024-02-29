#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int SIG_SIZE = 32;
int BLOCK_SIZE = 512;
typedef uint8_t BYTE;

int jpeg_header(BYTE buffer[]);
void next_filename(int *file_a, int *file_b, int *file_c);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    BYTE *buffer = malloc(BLOCK_SIZE);

    int start = 0; // Signals whether the first image has been found.
    int file_num = 0; // Name of file : file_num.jpg

    FILE *fileout;
    char filename[10];

    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        if (!jpeg_header(buffer) && !start) // Skips all steps until first jpeg is found, never runs again.
            continue;

        if (jpeg_header(buffer) && start) // Closes file, if one is open. Iterates name.
        {
            fclose(fileout);
            file_num++;
        }

        if (jpeg_header(buffer)) // Creates output jpeg for the first time, never runs again.
        {
            if (file_num < 10)
                sprintf(filename, "00%i.jpg", file_num);
            else if (file_num < 100)
                sprintf(filename, "0%i.jpg", file_num);
            else
                sprintf(filename, "%i.jpg", file_num);

            fileout = fopen(filename, "w");

            if (fileout == NULL)
            {
                fclose(fileout);
                printf("Could not create %s.\n", filename);
                return 1;
            }
        }

        fwrite(buffer, 1, BLOCK_SIZE, fileout);
        start = 1;
    }

    fclose(fileout);
    fclose(file);
    free(buffer);
}

int jpeg_header(BYTE buffer[])
{
    return (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef);
}
