#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //sorts if 2 arguments are presented
    if (argc == 2)
    {
        //gets the value of how many digits to rotate by
        const int rotate = atoi(argv[1]);
        bool valid = true;
        int length = strlen(argv[1]);
        for (int i = 0;  i < length; i++)
        {
            //exits if a digit is present
            if (isdigit(argv[1][i]) == false)
            {
                valid = false;
                i = length;
            }

        }
        if (valid)
        {
            //gets text to encrypt
            string plaintext = get_string("plaintext: ");
            int plaintextlength = strlen(plaintext);
            //sorts each character 
            for (int i = 0; i < plaintextlength; i++)
            {
                //rotates lower case characters
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
                //rotates upper case characters
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
                //prints encoded version of plain text
                printf("ciphertext: %s\n", plaintext);
            }
        }
        //crates an error message if there is a problem with the key 
        else
        {
            printf("Usage: ./caesar key\n");
            printf("1");
            return (1);
        }
    }
    //crates an error message if there is a problem with the key
    else if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        printf("1");
        return (1);
    }



}
