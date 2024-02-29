#include <cs50.h>
#include <stdio.h>

int function(int num);

int main(void)
{
    long credit_number = get_long("Number: ");
    long n = credit_number;
    int checksum = 0;

    int length = 0;
    n = credit_number;
    int firstnums = 0;
    while (n > 0)
    {
        length++;
        n /= 10;
        if (n < 100 && n > 10)
        {
            firstnums = n;
        }
    }
    n = credit_number;
    if (length < 13 || length > 16 || firstnums / 10 < 2 || firstnums / 10 > 5)
    {
        printf("INVALID\n");
    }
    else
    {
        while (n > 0)
        {
            long digit = 2 * (n % 100 / 10); // Extracts last but one number and doubles

            if (digit > 9)
            {
                checksum += 1 + digit % 10; // digit ranges from 0 to 18, so double digits always begin with 1
            }
            else
            {
                checksum += digit;
            }
            checksum += n % 10; // Extracts last number and adds to sum
            n /= 100;
        }
        // printf("Checksum: %i\n", checksum);
        // printf("Length: %i\n", length);
        // printf("First Numbers: %i\n", firstnums);
        if (!(checksum % 10))
        {
            if (length == 15 && (firstnums == 34 || firstnums == 37))
            {
                printf("AMEX\n");
            }
            else if (length == 13 && firstnums / 10 == 4)
            {
                printf("VISA\n");
            }
            else if (length == 16)
            {
                if (firstnums / 10 == 4)
                {
                    printf("VISA\n");
                }
                else if (firstnums / 10 == 5 && firstnums % 10 <= 5 && firstnums % 10 != 0)
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
        else
        {
            printf("INVALID\n");
        }
    }
}
