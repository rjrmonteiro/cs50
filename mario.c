#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do 
    {
        height = get_int("height:"); 
    }
    while (height < 1 || height > 8);        
    // each line
    for (int j = 0; j < height; j++)
    {
//spaces
        for (int i = 1; i <= height - (j + 1); i++)
        {
            printf(" ");
        }
//hastags    
        for (int k = 0; k <= j; k++)
        {
            printf("#");
        }    
//two spaces
        printf("  ");
//hastags
        for (int k = 0; k <= j; k++)
        {
            printf("#");
        }
//new line
        printf("\n");
    }
}
