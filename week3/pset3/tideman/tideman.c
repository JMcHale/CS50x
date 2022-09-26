#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool cycle(int start, int end);

bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;

            }
        }

        //check which number candidate is in each array
        for (int z = 0; z < candidate_count; z++)
            {
                printf("%i ", ranks[z]);
            }

        printf("\n");

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    //first check if it's a valid name
    for (int i = 0; i < candidate_count; i++)
    {
        //printf("Testing %s\n", name);

        //check if name is valid then record it as "rank i", and candidate number i
        if (strcmp(name, candidates[i]) == 0)
        {
            //printf("Valid name\n");

            ranks[rank] = i;

            return true;
        }
        else
        {
            //printf("%s is not the same as %s\n", candidates[i], name);
        }
    }

    //if no valid names on the list reject and return false (though this will exit???? CS50 however says to do this)
    //printf("Name not on list\n");

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    //ranks[0], ranks[1], ranks[2].... contain the number candidate in each on the ranks array
    //preferences will record what each voter prefers
    //The number of people who prefer each person over each person will be recorded in a 2D array
    //this can be done by inputting the number candidates into the array
    //WE DO NOT WANT THESE TO BE THE SAME CANDIDATE, but this can't happen if we aren't taking the same rank[i], because each candidate shouldn't be input more than once
    /*
    A   B   C
A   0   1   1

B   1   0   1

C   1   1   0

    preferences[rank[i]][rank[j]] = preferences[rank[i]][rank[j]] + 1;

    If voter voted in the order c a b, then the top rank is c, then a. So rank[0] is c, rank[1] is a. So preferances[c][a] is increased by 1.
    One voter prefers c over a
    */

    //each pair is represented by i, but we also need to compare if they prefer the first over the third
    for (int i = 0; i < candidate_count; i++)
    {
        //find next candidate to compare for preferences
        //then also record the voter prefers the candidate i, over all the following candidates!
        for (int j = i + 1; j < candidate_count; j++)
        {
            //if voter prefers c over a, this increases [c][a] by one
            preferences[ranks[i]][ranks[j]] = preferences[ranks[i]][ranks[j]] + 1;
        }


    }

    //displaying a preferences array for the purpose of debugging
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i", preferences[i][j]);
        }
        printf("\n");
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Check each preferences and if wins then add that to pairs recording which wins
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {

            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
            else
            {
                //printf("No Winner for %i pair versus %i\n", i, j);
            }
        }
    }

    for (int i = 0; i < pair_count; i++)
    {
        //printf("Pair %i is: %i won over %i\n", i, pairs[i].winner, pairs[i].loser);
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    //stores strength of pair i
    int strength[pair_count];

    //get all the strengths into strength array
    for (int i = 0; i < pair_count; i++)
    {
        strength[i] = preferences[pairs[i].winner][pairs[i].loser];
    }

    for (int i = 0; i < pair_count; i++)
    {
        //printf("Pair %i has strength %i\n", i, strength[i]);
    }

    int pairsortloops = 1;

    //loop through strengths using bubble sort, search through each value and shift up if it's greater than the value before it. It works backwards to a normal bubble sort, the smallest number "bubbling" to the end of the array
    //this could be improved by exiting if no swaps occur (currently left out)
    //Merge sort would work better for large arrays, but these are quite small with a MAX of 9
    for (int j = 0; j < pair_count; j++)
    {
        for (int i = 0; i < pair_count - pairsortloops; i++)
        {

            if (strength[i] < strength[i + 1])
            {
                pair midpair;
                int mid = 0;

                mid = strength[i];
                strength[i] = strength[i + 1];
                strength[i + 1] = mid;

                //Also change where the pair is located or the actual pair array won't be sorted according to strength
                midpair = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = midpair;
            }
        }

        //increment pairsortloops because the greatest number will no longer be at i to i - pairsortloops, it would of had to of been sorted
        pairsortloops++;
    }

    for (int i = 0; i < pair_count; i++)
    {
        //printf("Pair %i has strength %i\n", i, strength[i]);
        //printf("Pair %i winner is %i, loser is %i\n", i, pairs[i].winner, pairs[i].loser);
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO

    //loop once for each start candidate
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycle(pairs[i].loser, pairs[i].winner))
        {
            printf("Locked the pair %i and %i\n", pairs[i].winner, pairs[i].loser);
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        else
        {
            printf("Cycle found!\n");
        }
    }

    return;
}

//function to check for a cycle
bool cycle(int end, int start)
{
    printf("Checking for a cycle between %i and %i\n", start, end);
    //if there is a return to the start point then a cycle is formed
    if (end == start)
    {
        //return that a cycle is present
        printf("Cycle found between %i and %i\n", end, start);
        return true;
    }

    //check for any connections between other candidates, if so we'll also need to check those for a cycle
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[end][i])
        {
            printf("Found a locked edge between %i and %i\n", end, i);
            if (cycle(i, start))
            {
                printf("Cycle found between %i and %i\n", i, start);
                return true;
            }
        }
    }

    //There is no cycle!
    return false;

}

// Print the winner of the election
void print_winner(void)
{
    // If the candidate is the true winner they will have no arrows pointing to them
    // They will not have any locked[end][start] as no arrows must stop on them
    for (int i = 0; i < candidate_count; i++)
    {
        int false_cand = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                // if the is no locked edge, there is no arrow from that cand to this one
                false_cand++;

            }
        }

        //Finally print if this cand has no arrows pointing to it (could result in multiple outputs if it's a tie???)
        if (false_cand == candidate_count)
            {
                printf("%s\n", candidates[i]);
            }
    }
    return;
}

