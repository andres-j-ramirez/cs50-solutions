#include <cs50.h>
#include <stdio.h>

// Letting C know we have custom functions
int get_positive_int(void);
void pyramid(int n);

// Main code
int main(void)
{
    // Getting input from user
    int n = get_positive_int();
    // Using that input to make the pyramid
    pyramid(n);
}

// Prompt to get positive integer
int get_positive_int(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    // Makes sure we get positive integer smaller than 100
    while (n < 1 || n > 100);
    return n;
}

// Fuction creating the pyramid
void pyramid(int n)
{
    // Create the rows
    int row;
    for (row = 0; row < n; row++)
    {
        // Add spaces needed for right-aligned
        int spaces;
        for (spaces = 0; spaces < n - row - 1; spaces++)
        {
            printf(" ");
        }

        // Print # per row aka columns
        int col;
        for (col = 0; col < row + 1; col++)
        {
            printf("#");
        }

        printf("\n");
    }
}
