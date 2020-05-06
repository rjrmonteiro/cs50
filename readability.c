#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

float average(float a, float b);
float coleman(float a, float b);

int main(void)

{
    int letters = 0;
    int words = 1;
    int sentences = 0;
    
    
    string text = get_string("Text:");
    
    
    for (int i = 0; i < strlen(text); i++)
    {
//Number of words
        if (text[i] == ' ')
        {
            words++;
        }
//Number of letters
        else if (text[i] >= 'a' && text[i] <= 'z')
        {
            letters++;
        }
        else if (text[i] >= 'A' && text[i] < 'Z')
        {
            letters++;
        }
//Number of symbols
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
//avarages and indexes
    float l = average(letters, words);
    float s = average(sentences, words);
    float index = coleman(l, s);
    int result = round(index);
//ifs
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 1 && index <= 16)
    {
        printf("Grade %i\n", result);
    }
    else
    {
        printf("Grade 16+\n");
    }
    
}

float average(float a, float b)
{
    return (a * 100) / b;
}

float coleman(float a, float b)
{
    return (0.0588 * a - 0.296 * b - 15.8);
}