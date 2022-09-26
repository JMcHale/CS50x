#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

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

    //populates candidates array, and sets all votes to 0
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
    // TODO
    //loop through the candidates and add 1 to their vote total if string name = candidate name
    for (int i = 0; i < candidate_count; i++)
    {
        printf("Checking %s for a match to %s\n", candidates[i].name, name);
        if (!strcmp(candidates[i].name, name))
        {
            printf("One vote for %s\n", candidates[i].name);
            candidates[i].votes++;
            printf("%s has %i votes\n", candidates[i].name, candidates[i].votes);
            return true;
        }
    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    // Need to find who has the most votes, can do this by comparing each and "sorting them"
    for (int i = 0; i < candidate_count; i++)
    {
        int mid = 0;
        string midstr;

        //start at 1 or we would be trying to compare the last candidate with the candidate after the last, obviously impossible and this gives a Segmentation fault
        int runs = 1;

        for (int j = 0; j < candidate_count - runs; j++)
        {
            if (candidates[j].votes < candidates[j + 1].votes)
            {
                mid = candidates[j].votes;
                candidates[j].votes = candidates[j + 1].votes;
                candidates[j + 1].votes = mid;

                midstr = candidates[j].name;
                candidates[j].name = candidates[j + 1].name;
                candidates[j + 1].name = midstr;
            }
        }

        runs++;
    }

    printf("%s\n", candidates[0].name);

    //print the winner, then loop through for anyone equal to the winner. End printing winners when no one else is equal
    for (int i = 0; i < candidate_count; i++)
    {

        if(candidates[i].votes == candidates[i + 1].votes)
        {
            printf("%s\n", candidates[i + 1].name);
        }
        else
        {
            return;
        }
    }


    return;
}

