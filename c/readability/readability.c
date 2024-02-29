#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    float L = (float) letters / (float) words * 100;
    float S = (float) sentences / (float) words * 100;
    float index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}

int count_letters(string text)
{
    int letters = 0;
    for (int letter = 0, n = strlen(text); letter < n; letter++)
    {
        if (isalpha(text[letter]))
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string text)
{
    int words = 0;
    for (int letter = 0, n = strlen(text); letter < n; letter++)
    {
        if (isspace(text[letter]))
        {
            words++;
        }
    }
    return words + 1;
}

int count_sentences(string text)
{
    int sentences = 0;
    for (int letter = 0, n = strlen(text); letter < n; letter++)
    {
        if (text[letter] == '.' || text[letter] == '!' || text[letter] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}
