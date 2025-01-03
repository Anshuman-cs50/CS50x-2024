#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int start_of_jpeg(uint8_t buff[4]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        printf("Couldn't open %s.\n", argv[1]);
        return 1;
    }

    uint8_t buffer[512];

    // JPEG files counter
    int n_jpeg = 0;

    // file pointer will initially point to NULL
    FILE *img = NULL;

    // while it's not EOF
    while (fread(buffer, 1, 512, card) == 512)
    {
        // if it is a start of a new jpeg file
        if (start_of_jpeg(buffer))
        {
            // if no file is open
            if (img != NULL)
            {
                fclose(img);
            }

            char *filename = malloc(8 * sizeof(char));

            sprintf(filename, "%03i.jpg", n_jpeg);

            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Couldn't open the file %s.", filename);
                fclose(card);
                return 1;
            }

            fwrite(buffer, 512, 1, img);

            n_jpeg++;

            free(filename);
        }

        // if it is not a start of a jpeg file
        else
        {
            // if a file is already opened
            if (img != NULL)
            {
                // write the buffer data to the file
                fwrite(buffer, 512, 1, img);
            }
        }
    }

    // closing img
    if (img != NULL)
    {
        fclose(img);
    }

    // closing card
    fclose(card);

    return 0;
}

int start_of_jpeg(uint8_t buff[4])
{
    return (buff[0] == 0xff && buff[1] == 0xd8 && buff[2] == 0xff && (buff[3] & 0xf0) == 0xe0);
}
