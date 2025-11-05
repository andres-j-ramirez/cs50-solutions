// Run Luhn's algorithm on Credit Card Numbers
#include <cs50.h>
#include <math.h>
#include <stdio.h>

long get_ccnumber(void);
int sum_every_other_digit(long ccnumber);
int complete_luhns(long ccnumber);
int length_count(long ccnumber);
int length_check(int count);
void final_check(int final_total, long ccnumber);

int main(void)
{
    // Take input for CC number
    long ccnumber = get_ccnumber();

    // Sum every other after *2
    int total = sum_every_other_digit(ccnumber);

    // Sum every other not counted in above
    int second_total = complete_luhns(ccnumber);

    // Put them together
    int final_total;
    {
        final_total = total + second_total;
    }

    // Make sure the number is long enough to be a credit card
    int count;
    count = length_count(ccnumber);
    length_check(count);

    // Decide what to do with that result
    if (length_check(count) == 0)
    {
        printf("INVALID\n");
        return 0;
    }
    else
    {
        // Final check and print result
        final_check(final_total, ccnumber);
    }
}

// Get CC number from user
long get_ccnumber(void)
{
    long ccnumber;
    do
    {
        ccnumber = get_long("Number: ");
    }
    while (ccnumber < 0);
    return ccnumber;
}

// start at second to last, multiply by two, add sums of those digits to total, skip every other, do
// the same thing over until no more numbers, return that total
int sum_every_other_digit(long ccnumber)
{
    int total = 0;
    while (ccnumber > 0)
    {
        // Drop the last number
        long dividecc;
        {
            dividecc = ccnumber / 10;
        }

        // Take the second to last number and double it
        long secondtolastdigit;
        {
            secondtolastdigit = dividecc % 10;
            secondtolastdigit = secondtolastdigit * 2;
        }

        // Take number and add it's digits together
        int parseandadd;
        {
            parseandadd = ((secondtolastdigit / 10) % 10) + (secondtolastdigit % 10);
        }

        // Update ccnumber and add to total
        ccnumber = ccnumber / 100;
        total = total + parseandadd;
    }
    return total;
}

int complete_luhns(long ccnumber)
{
    int second_total = 0;
    while (ccnumber > 0)
    {
        long i;
        {
            i = ccnumber % 10;
        }

        second_total = second_total + i;

        ccnumber = ccnumber / 100;
    }
    return second_total;
}

int length_count(long ccnumber)
{
    int count;
    for (count = 0; ccnumber > 0; count++)
    {
        ccnumber = ccnumber / 10;
    }
    return count;
}

int length_check(int count)
{
    if (count == 13 || count == 15 || count == 16)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void final_check(int final_total, long ccnumber)
{
    // find out the cc length to divide accordingly later
    int count;
    count = length_count(ccnumber);

    if ((final_total % 10) == 0)
    {
        if (count == 13)
        {
            ccnumber = ccnumber / pow(10, 11);
            if (ccnumber == 34 || ccnumber == 37)
            {
                printf("INVALID\n");
            }
            else if (ccnumber == 22 || ccnumber == 51 || ccnumber == 52 || ccnumber == 53 ||
                     ccnumber == 54 || ccnumber == 55)
            {
                printf("MASTERCARD\n");
            }
            else if (ccnumber == 40 || ccnumber == 41 || ccnumber == 42 || ccnumber == 49)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        else if (count == 15)
        {
            ccnumber = ccnumber / pow(10, 13);
            if (ccnumber == 34 || ccnumber == 37)
            {
                printf("AMEX\n");
            }
            else if (ccnumber == 22 || ccnumber == 51 || ccnumber == 52 || ccnumber == 53 ||
                     ccnumber == 54 || ccnumber == 55)
            {
                printf("MASTERCARD\n");
            }
            else if (ccnumber == 40 || ccnumber == 41 || ccnumber == 42 || ccnumber == 49)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        else if (count == 16)
        {
            ccnumber = ccnumber / pow(10, 14);
            if (ccnumber == 34 || ccnumber == 37)
            {
                printf("INVALID\n");
            }
            else if (ccnumber == 22 || ccnumber == 51 || ccnumber == 52 || ccnumber == 53 ||
                     ccnumber == 54 || ccnumber == 55)
            {
                printf("MASTERCARD\n");
            }
            else if (ccnumber == 40 || ccnumber == 41 || ccnumber == 42 || ccnumber == 49)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        else
        {
            printf("INVALID\n");
        }
    }

    else
    {
        printf("INVALID\n");
    }
}
