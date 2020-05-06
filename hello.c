#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //ask for the name
    string name = get_string("What's your name?\n");
    //print the name
    printf("Hello, %s.\n", name);
}
