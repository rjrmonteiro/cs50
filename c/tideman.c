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
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool loop_check(int start, int end, int cycle_start);

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
    for (int k = 0; k < candidate_count; k++)
    {
        if (!strcmp(candidates[k], name))
        {
            ranks[rank] = k;
            printf("candidato %i adicionado ao lugar %i\n", k, rank);
            return true;
        }
    }
   
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int l = 0; l < candidate_count; l++)
        {   
            if (l > i)
            {
                preferences[ranks[i]][ranks[l]]++;
                printf("i = %i l = %i logo %i\n", ranks[i], ranks[l], preferences[ranks[i]][ranks[l]]);
            }
        }
        
    }
    

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
                printf("this %i over that %i\n", i, j);
                printf("winner - %i looser %i\n", pairs[pair_count].winner, pairs[pair_count].loser);
                printf("%i\n", pair_count);
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
                printf("else this %i over that %i\n", i, j);
                printf("elsewinner - %i looser %i\n", pairs[pair_count].winner, pairs[pair_count].loser);
                printf("else %i\n", pair_count);
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int swap_counter = 1;
    int strenght_par_i;
    int strenght_par_iplus1;

    while (swap_counter != 0)
    {
        swap_counter = 0;
        for (int i = 0; i < pair_count - 2; i++)
        {
            strenght_par_i = (preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner]);
            strenght_par_iplus1 = (preferences[pairs[i + 1].winner][pairs[i + 1].loser] - preferences[pairs[i + 1].loser][pairs[i + 1].winner]);

            if (strenght_par_i < strenght_par_iplus1)
            {
                pair swap = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = swap;
                swap_counter++;
            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!loop_check(pairs[i].winner, pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    for (int i = 0; i < pair_count; i ++)
    {
        printf("%d\n", locked[i][i]);
    }
    return;
}

// Tests for a loop by checking for a arrow coming into a given candidate
bool loop_check(int start, int end, int cycle_start)
{
    bool boolean = true;
    if (end == cycle_start)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[end][i])
        {
            if (loop_check(end, i, cycle_start))
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{

    for (int i = 0; i < candidate_count; i++)
    {
        int counter = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                counter++;
            }
        }
        if (counter == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

