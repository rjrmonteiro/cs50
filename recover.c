#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

//define a BYTE struct
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //check for the 2 arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover infile\n");
        return 1;
    }
    //create a string with the file name
    char *infile = argv[1];
    //allocate space in memory for the 512bytes
    BYTE *buffer = malloc(512 * sizeof(BYTE));
    //open file
    FILE *card = fopen(infile, "r");
    //create a variable for the image name
    char *filename = malloc(8 * sizeof(char));
    //initializing the pointer to the new file
    FILE *copy = NULL;
    //validating the input file
    if (card == NULL)
    {
        fprintf(stderr, "Could not open %s\n", infile);
        return 2;
    }
    //initializing the counter
    int counter = 0;
    //searching for images
    while (true)
    {
        //read a chunk of 512 bytes from the card
        fread(buffer, sizeof(BYTE), 512, card);
        //checking for the end of the file
        if (feof(card))
        {
            break;
        }
        //finding a new image
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //if already found an image
            if (copy != NULL)
            {
                fclose(copy);
                counter++;
                sprintf(filename, "%03i.jpg", counter);
                copy = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), 512, copy);

            }
            //if it's the first image
            if (copy == NULL)
            {
                sprintf(filename, "%03i.jpg", counter);
                copy = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), 512, copy);
            }
        }
        //continuing to write on the copy
        else
        {
            if (copy != NULL)
            {
                fwrite(buffer, sizeof(BYTE), 512, copy);
            }

        }
    }
    //close files
    fclose(copy);
    fclose(card);
    //free memory
    free(filename);
    free(buffer);

    return 0;

}
