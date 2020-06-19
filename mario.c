#include<cs50.h>
#include<stdio.h>

int main(void)
{
    int n;
    int i;
    int j;
    int x;
    
    do
    {
        //asks for height
        n = get_int("please enter a hight between 1 and 8:");
    }
    //sorts and rejects input
    while (n <= 0 || n >= 9);
    
    for (i = 1; i < n + 1; i++)
    {
        //corrects the spacing
        for (x = (n - i); x > 0; x--)
        {
            printf(" ");
                
        }
        for (j = 0; j < i; j++)
        {
            printf("#");
        }   
        printf("\n");
    }
}