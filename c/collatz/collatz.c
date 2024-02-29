#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

int collatz(int n);
bool isNumber(char number[]);
int atoi(const char *str);

int main(int argc, string argv[])
{

    if (!isNumber(argv[1]))
    {
        printf("Usage: ./collatz int\n");
        return 1;
    }

    int n = atoi(argv[1]);
    printf("%i\n", collatz(n));
}

int collatz(int n)
{
    if (n == 1)
        return 0;
    else if (n % 2)
        return 1 + collatz(3 * n + 1);
    else
        return = 1 + collatz(n / 2);
}

bool isNumber(char number[])
{
    int i = 0;

    //checking for negative numbers
    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++)
    {
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}

