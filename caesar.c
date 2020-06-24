#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    
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
                        int excess = plaintext[i] + rotate - 'z';
                       
                        if (excess >= 'z' - 'a')
                        {
                            while (excess >= ('z' - 'a'))
                            {
                                excess = excess - (26);
                            }
                            
                            if (plaintext[i] + excess > 'z')
                            {
                                excess = plaintext[i] + excess - 'z';
                                plaintext[i] = 'a' + excess - 1;
                            }
                            else
                            {
                                plaintext[i] = 'a' + excess - 1;
                            }
                        }
                        else
                        {
                                plaintext[i] = 'a' + excess - 1;
                        }
                    }
                    else if (plaintext[i] + rotate <= 'z')
                    {
                        plaintext[i] = plaintext[i] + rotate;
                        
                    }
                }
                else if (isupper(plaintext[i]))
                {
                    if (plaintext[i] + rotate > 'Z')
                    {
                        int excess = plaintext[i] + rotate - 'Z';
                       
                        if (excess >= 'Z' - 'A')
                        {
                            while (excess >= ('Z' - 'A'))
                            {
                                excess = excess - (26);
                            }
                            
                            if (plaintext[i] + excess > 'Z')
                            {
                                excess = plaintext[i] + excess - 'Z';
                                plaintext[i] = 'A' + excess - 1;
                            }
                            else
                            {
                                plaintext[i] = 'A' + excess - 1;
                            }
                        }
                        else
                        {
                                plaintext[i] = 'A' + excess - 1;
                        }
                    }
                    else if (plaintext[i] + rotate <= 'Z')
                    {
                        plaintext[i] = plaintext[i] + rotate;
                        
                    }
                }
            printf("ciphertext: %s\n", plaintext);
        }
    }
    
    else
    {
        printf("Usage: ./caesar key\n");
        printf("1");
        return (1);
    }
}

    else if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        printf("1");
        return (1);
    }
        
        
    
}
