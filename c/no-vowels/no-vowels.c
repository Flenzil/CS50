// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string word);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }
    string wordnv;
    wordnv = replace(argv[1]);
    printf("%s\n", wordnv);
}

string replace(string word)
{
    for (int letter = 0; letter < strlen(word); letter++)
    {
        char l = word[letter];
        if (l == 'a')
        {
            l = '6';
        }
        if (l == 'e')
        {
            l = '3';
        }
        if (l == 'i')
        {
            l = '1';
        }
        if (l == 'o')
        {
            l = '0';
        }
        word[letter] = l;
    }
    return word;
}
