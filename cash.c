#include<cs50.h>
#include<stdio.h>
#include<math.h>

int main(void)
{
    float total;
    int totalPennies;
    int newTotal;
    int quarters;
    int dimes;
    int nickles;
    int pennies;

    do
    total = get_float("how much change is owed?\n");
    while (total < 0);
    totalPennies = round(total * 100);
    quarters = totalPennies / 25;
    newTotal = totalPennies - (quarters * 25);
    dimes = newTotal / 10;
    newTotal = (totalPennies - ((quarters * 25) + (dimes * 10)));
    nickles = newTotal / 5;
    newTotal = (totalPennies - ((quarters * 25) + (dimes * 10) + (nickles * 5)));
    pennies = newTotal;


printf("%i\n", (quarters + dimes + nickles + pennies));
//printf("pennies = %i\n",totalPennies);
//printf("quarters = %i\n", quarters);
//printf("dimes = %i\n", dimes);
//printf("nickles = %i\n", nickles);
//printf("pennies = %i\n", pennies);
}
