// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool upper = false;
    bool lower = false;
    bool number = false;
    bool symbol = false;
    for (int i = 0; i < strlen(password); i++)
    {
        char letter = password[i];
        if (!upper)
        {
            upper = isupper(letter);
        }
        if (!lower)
        {
            lower = islower(letter);
        }
        if (!number)
        {
            number = isdigit(letter);
        }
        if (!symbol)
        {
            symbol = ispunct(letter);
        }
    }
    if (upper + lower + symbol + number == 4)
    {
        return true;
    }
    return false;
}
