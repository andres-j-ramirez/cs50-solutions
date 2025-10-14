#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int BLOCK = 512;

int main(int argc, char *argv[])
{
    // Accept only one CLI argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Only continue the program if we can open the file, if so this opens the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Forensic image cannot be opened for reading\n");
        return 1;
    }

    // Read 512 bytes into a buffer/ Create that buffer
    uint8_t buffer[BLOCK];

    // Point to an output image
    FILE *img = NULL;

    // Start counter for images recovered
    int count = 0;

    // Limit how many slots used for name convention
    char name[8];

    // Repeat until end of card:
    while (fread(buffer, 1, BLOCK, card) == BLOCK)
    {
        // If start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xF0) == 0xE0)
        {
            // If 1st JPEG start filename at 000.jpeg
            if (img == NULL)
            {
                sprintf(name, "%03i.jpg", count);
                img = fopen(name, "w");
                fwrite(buffer, 1, BLOCK, img);
                count++;
            }
            // Else close that last file and open up new one
            else if (img != NULL)
            {
                fclose(img);
                sprintf(name, "%03i.jpg", count);
                img = fopen(name, "w");
                fwrite(buffer, 1, BLOCK, img);
                count++;
            }
        }
        // Else if already found JPEG, keep writing to that same file
        else
        {
            if (img != NULL)
            {
                fwrite(buffer, 1, BLOCK, img);
            }
        }
    }

    // Close remaining files
    fclose(card);
    if (img != NULL)
    {
        fclose(img);
    }

    return 0;
}
