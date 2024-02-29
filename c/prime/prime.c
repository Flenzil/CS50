#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if ((i % 2) || (i == 2)) // skip 1 and even numbers except 2
        {
            if (prime(i) && i != 1)
            {
                printf("%i\n", i);
            }
        }
    }
}

bool prime(int number)
{
    for (int i = 2; i < number; i++)
    {
        if (number % 2) // All primes > 2 are odd, no need to check for even factors.
        {
            if (!(number % i)) // Exit if even one factor is found, no need to check higher numbers.
            {
                return false;
            }
        }
    }
    return true;
}
