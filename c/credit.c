#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)

{
    long cardnumber;
    int odd = 0;
    long rest;
    int even;
    int multiply = 0;
    int total = 0;
    int counter = 0;
    int checksum;
//get card number
    do
    {
        cardnumber = get_long("Card Number:");
    }
    while (cardnumber <= 0);
    
    long tipe = cardnumber;
//Loop for the checksum and the digits counter
    while (cardnumber != 0)
    {
        odd = odd + cardnumber % 10;
        cardnumber = cardnumber / 10;
        counter++;
        if (cardnumber != 0)
        {
            even = cardnumber % 10;
            multiply = even * 2;
            if (multiply >= 10)
            {
                total = total + (multiply % 10);
                total = total + (multiply / 10);
            }
            else
            {
                total = total + multiply;
            }
            cardnumber = cardnumber / 10;
            counter++;
        }
//preparing checksum
    }
    even = total;
    total = even + odd;
    checksum = total % 10;
    if (checksum != 0)
    {
        printf("INVALID\n");
    }
//sorting through the diferent tipes of cards
    else
    {
        while (tipe > 56)
        {
            tipe = tipe / 10;
        }
//AMERICAN EXPRESS
        if (tipe == 34 || tipe == 37)
        {   
            if (counter == 15)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
            
        }
//VISA
        else if (tipe >= 40 && tipe <= 49)
        {
            if (counter == 13 || counter == 16)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
//MASTERCARD
        else if (tipe > 50 && tipe < 56)
        {
            if (counter == 16)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else 
        {
            printf("INVALID\n");
        }
    } 
}
