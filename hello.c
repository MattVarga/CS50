#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //asks for your name
    string name = get_string("What is your name?\n");
    //replies with hello and your name
    printf("hello, %s\n", name);
}