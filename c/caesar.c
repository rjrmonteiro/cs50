#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
//validating number of arguments
    if (argc != 2)
    { 
        printf("Usage: ./caesar key\n");
        return 1;
    }
//validating the key
    int n = strlen(argv[1]);
    int resultado = 0;
    for (int i = 0; i < n; i++)
    {
        if (isdigit(argv[1][i]) == false)
        {
            resultado = -1;
            i = n;
        }
    }
    if (resultado < 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
//creating variables
    int key = atoi(argv[1]);
    string plaintext = get_string("plaintext:");
    n = strlen(plaintext);
    int ascii[n];
    int pluscode[n];
    char ciphertext[n];
    
//from letters to ascii

    for (int i =  0; i < n; i++)
    {
        ascii[i] = (int) plaintext[i];
    }
    
//add the secret

    for (int i = 0; i < n; i++)
    {
        if (ascii[i] >= 'a' && ascii[i] <= 'z')
        {
            ascii[i] = (ascii[i] - 'a');
            pluscode[i] = ((ascii[i] + key) % 26) + 'a';

        }
        else if (ascii[i] >= 'A' && ascii[i] <= 'Z')
        {
            ascii[i] = (ascii[i] - 'A');
            pluscode[i] = ((ascii[i] + key) % 26) + 'A';

        }
        else
        {
            pluscode[i] = ascii[i];

        }
    }
    
//from ascii to letters

    printf("ciphertext: ");
    for (int i =  0; i < n; i++)
    {
        ciphertext[i] = pluscode[i];
        printf("%c", ciphertext[i]);
    }
    printf("\n");
}
