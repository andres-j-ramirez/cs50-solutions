#include <cs50.h>
#include <stdio.h>
// Declare custom functions
int get_positive_int(void);
void pyramid(int n);
// Main code
int main(void)
{
    int n = get_positive_int();
    pyramid(n);
}
// Do while loop till number b/w 1 and 8 inclusive
int get_positive_int(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    return n;
}
// build pyramid
void pyramid(int n)
{ // print f with\n that makes rows
    int row;
    for (row = 0; row < n; row++)
    { // we're adding proper spaces on left hand side
        int spaces;
        for (spaces = 0; spaces < n - row - 1; spaces++)
        {
            printf(" ");
        }
        // how many hashes on left
        int col;
        for (col = 0; col < row + 1; col++)
        {
            printf("#");
        }
        // space in between two sets of hashes
        int spacebtw;
        for (spacebtw = 0; spacebtw < 2; spacebtw++)
        {
            printf(" ");
        }
        // hashes on left hand side, right-aligned
        int col2;
        for (col2 = 0; col2 < row + 1; col2++)
        {
            printf("#");
        }

        printf("\n");
    }
}
