#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{

    for (int i = 0; i < MAX; i++)
    {
        if (candidates[i].name == NULL)
        {
            return false;
        }
        if (!strcasecmp(name, candidates[i].name))
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int check = 0;
    candidate swap;
    int count = -1;

    /*
    for (int i = 0; i < MAX; i++)
    {
        printf("%s, %i", candidates[i].name, candidates[i].votes);
    }
    printf("\n");
    */

    while (count != 0)
    {
        count = 0;
        for (int i = 0; i < MAX - 1; i++)
        {
            if (candidates[i].votes > candidates[i + 1].votes)
            {
                swap = candidates[i];
                candidates[i] = candidates[i + 1];
                candidates[i + 1] = swap;
                count++;
            }
        }
    }
    /*
    for (int i = 0; i < MAX; i++)
    {
        printf("%s, %i", candidates[i].name, candidates[i].votes);
    }
    printf("\n");
    */
    printf("%s\n", candidates[MAX - 1].name); // Print candidate with most votes

    for (int i = MAX - 2; i > 0; i--) // Checks if other candidates have same # votes as winner
    {
        if (candidates[i].votes == candidates[MAX - 1].votes && candidates[i].votes != 0)
        {
            printf("%s\n", candidates[i].name);
        }
        else
        {
            return;
        }
    }
}
