#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if(argc != 2)
    {
    printf("Usage: ./caesar key\n");
    return(1);
    }
    
    if (argc == 2)
    {
        const int rotate = atoi(argv[1]);
        bool valid = true;
        int length = strlen(argv[1]);
        for (int i=0;  i < length; i++)
        {
            if (isdigit(argv[1][i]) == false)
            {
                valid = false;
                i = length;
            }
        
        }
        if (valid)
        {
            string plaintext = get_string("plaintext: ");
            int plaintextlength = strlen(plaintext);
            for(int i=0; i < plaintextlength; i++)
            {
                if (islower(plaintext[i]))
                {
                    if (plaintext[i] + rotate > 'z')
                    {
                        int excess = plaintext[i] + rotate;
                        plaintext[i] = 'a' + excess - 1;
                        
                    }
                    else if (plaintext[i] + rotate <= 'z')
                    {
                        plaintext[i] = plaintext[i] + rotate + 1;
                    }
                }
                
                else if (isupper(plaintext[i]))
                {
                    if (plaintext[i] + rotate > 'Z')
                    {
                        int excess = plaintext[i] + rotate;
                        plaintext[i] = 'A' + excess - 1;
                        
                    }
                    else if (plaintext[i] + rotate <= 'Z')
                    {
                        plaintext[i] = plaintext[i] + rotate;
                    }
                    
                    
                }
                //printf("cyphertext: %s\n", plaintext);
            }
            printf("cyphertext: %s\n", plaintext);
            return 0;
        
        
        }
    }
}