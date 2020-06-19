#include<cs50.h>
#include<stdio.h>

int main(void)
{
    int n;
    int i;
    int j;
    int x;
    
    do
    n = get_int("please enter a hight between 1 and 8:");
    while (n<0 || n>9);
    
        for (i=0; i<n+1; i++){
            for (x = (n - i); x >= 0; x--){
            printf(" ");
                
            }
            for (j=0; j<i; j++)
                {
                printf("%s","#");
                }   
                printf("\n");
        }
}