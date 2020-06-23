#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int count_letters(char *text);
int words(char *text);
int sentence(string text);

int main(void)
{
    char *text = get_string("text: ");
    int letters= count_letters(text);
    int num_words =  words(text);
    int num_sentence =  sentence(text);
    float index;
    int grade;


    //printf("%i letter(s)\n", letters);
    //printf("%i word(s)\n", num_words );
    //printf("%i sentence(s)\n", num_sentence);

    float L = (float)letters / num_words * 100;
    float S = (float)num_sentence / num_words * 100;

    index = 0.0588 * L - 0.296 * S - 15.8;
    
    grade = round(index);
        if (grade < 1)
        {
           printf("Before Grade 1\n");
        }
        else if (grade >= 16)
        {
            printf("Grade 16+\n");
        }
        else
        {
            printf("Grade %i\n", grade );
        }
}

int count_letters(char *text)
{
    int i;
    int count = 0;

        for (i=0; text[i]; i++)
        {
            if ((text[i] >= 'a' &&  text[i]   <= 'z') || (text[i] >= 'A' &&  text[i]   <= 'Z'))
            //if (text[i] != ' ' && text[i] != '!' && text[i] != '?' && text[i] != '"' && text[i] != ','  && text[i] != '.' && text[i] != ':' && text[i] != '\'' && text[i] != '-'  && text[i]!= ';')
            {
                count++;
            }
        }
        return count;
}

int words(string text)
{
    int j;
    int counted = 0;

    for (j=0; text[j]; j++)
        {
            if (text[j] == ' ' )
            {
                counted++;
            }
        }
        return counted +1;
}

int sentence(string text)
{
    int k;
    int counted = 0;

    for (k=0; text[k]; k++)
        {
            if (text[k] == '.'  || text[k] == '?' || text[k] == '!' )
            {
                counted++;
            }
        }
        return counted ;
}

