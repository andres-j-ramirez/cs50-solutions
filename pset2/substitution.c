#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void encipher(string text, string key);
int key_check(string key);

int main(int argc, string argv[])
{
    // Get Key - done through command-line argument

    // Validate argument length
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        // Key validation for length, alphabetic characters, and uniquness
        int result = key_check(argv[1]);
        if (result != 0)
        {
            printf("Invalid Key Error: %i\n", result);
            return 1;
        }
    }
    // Get plaintext
    string text = get_string("plaintext: ");

    // Encipher
    encipher(text, argv[1]);

    // Print ciphertext
    return 0;
}

int key_check(string key)
{
    // Check if key length is 26 characters
    if (strlen(key) != 26)
    {
        printf("Key must be 26 characters in length.\n");
        return 2;
    }
    // Check if key is alphabetical characters only
    for (int i = 0; i < 26; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            printf("Key must contain alphabetical characters only.\n");
            return 3;
        }
    }
    // Check if every character appears only once
    for (int i = 0; i < 26; i++)
    {

        for (int j = i + 1; j < 26; j++)
        {
            if (tolower(key[i]) == tolower(key[j]))
            {
                printf("Each letter in the key must be unique.\n");
                return 4;
            }
        }
    }
    return 0;
}

void encipher(string text, string key)
{
    printf("ciphertext: ");
    int textlength = strlen(text);
    for (int i = 0; i < textlength; i++)
    {
        // Check to see if letter is non-alphabetical
        if (!isalpha(text[i]))
        {
            printf("%c", text[i]);
        }
        else
        {
            // Check to see if letter is uppercase
            if (!islower(text[i]))
            {
                // Alphabet zero index - uppercase letter
                int letter = text[i] - 65;
                // Map to key
                char cipher = toupper(key[letter]);
                // Encipher character
                printf("%c", cipher);
            }
            // Cipher lowercase letters
            else
            {
                int letter = text[i] - 97;
                char cipher = tolower(key[letter]);
                printf("%c", cipher);
            }
        }
    }
    printf("\n");
}

