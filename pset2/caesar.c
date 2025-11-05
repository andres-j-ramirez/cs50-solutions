#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variable used to make ASCII index to an aphabet index (uppercase)
const int A = 65;

// Variable used to make ASCII index to an aphabet index (lowercase)
const int a = 97;

int is_string_digit(string argv);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        printf("Usage: /.caesar key\n");
        return 1;
    }

    // Make sure every character in argv[1] is a digit
    if (is_string_digit(argv[1]) == 1)
    {
        return 1;
    }

    // Convert argv[1] from a 'string' to an 'int'
    int key = atoi(argv[1]);

    // Prompt user for plaintext
    string s = get_string("Plaintext: ");

    // Print chiphertext
    printf("ciphertext: ");

    // For each character in plaintext:
    int k = strlen(s);
    for (int i = 0; i < k; i++)
    {
        if (isalpha(s[i]) != 0)
        {
            // Rotate the character if it's a letter
            if (isupper(s[i]) != 0)
            {
                int l = s[i] - A;
                int m = (l + key) % 26;
                int n = m + A;
                printf("%c", n);
            }
            else
            {
                int l = s[i] - a;
                int m = (l + key) % 26;
                int n = m + a;
                printf("%c", n);
            }
        }
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");
    return 0;
}

int is_string_digit(string argv)
{
    int argument = strlen(argv);
    for (int i = 0; i < argument; i++)
    {
        if (isdigit(argv[i]) == 0)
        {
            printf("Usage: /.caesar key\n");
            return 1;
        }
    }
    return 0;
}

