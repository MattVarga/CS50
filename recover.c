#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main(int argc, char *argv[])
#define BUFFER_SIZE 512

//int main(void)
{
    // open input file
    FILE *input = fopen("card.raw", "r");
    if (input == NULL)
    {
        printf("unable to open card.raw.\n");
        return 1;
    }
    
    // creates new buffer of 512 bytes
    unsigned char buffer[BUFFER_SIZE];
    
    // creates an integer filenum for file names
    int filenum = 0;
    
    FILE *pic = NULL; 
    
    int new_pic = 0; 
    
    // loops through memory until complete
    while (fread(buffer, BUFFER_SIZE, 1, input) == 1)
    {
        // read first 4 bytes to see if it is the start of a jpg signature 
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
        {
            if (new_pic == 1)
            {
                // found the beginning of a new pic
                fclose(pic);
            }
            else
            {
                // jpg found
                new_pic = 1;
            }
            
            char filename[8];
            sprintf(filename, "%03i.jpg", filenum);
            pic = fopen(filename, "w");
            filenum++;
        }
        
        if (new_pic == 1)
        {
            // write 512 bytes at a time to file if pic found until the next pic is found
            fwrite(&buffer, BUFFER_SIZE, 1, pic);
        }
        return 0;
        
    }

    // close all files
    fclose(input);
    fclose(pic);

    return 1;
}
