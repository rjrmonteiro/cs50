#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)

{
    float dollars;
    int quarters;
    int dimes;
    int nickles;
    int pennies;
    int coins; 
//ask for change
    do
    {
        dollars = get_float("Change own:\n");
    }
    while (dollars < 0);
//convert dollars to cents
    int cents = round(dollars * 100); 
//split the change into coins
    quarters = cents / 25;
    dimes = (cents % 25) / 10;
    nickles = ((cents % 25) % 10) / 5;
    pennies = (((cents % 25) % 10) % 5) / 1;
//sum the coins
    coins = quarters + dimes + nickles + pennies;
//print the number of coins
    printf("%i coins\n", coins);
}
