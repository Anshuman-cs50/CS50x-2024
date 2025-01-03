#include <cs50.h>
#include <stdio.h>

int digit(long int n);
int fdigit(long int f, int d);
bool checksum(long int c, int e);

int main()
{
    // input from user
    long int num;
    do
    {
        num = get_long("Enter your Credit Card Number: ");
    }
    while (num <= 0);

    int digits = digit(num);
    int fdigits = fdigit(num, digits);
    bool valid = checksum(num, digits);

    if (valid)
    {

        if (digits == 15)
        {
            if (fdigits == 34 || fdigits == 37)
            {
                // AMEX
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        else if (digits == 13 || digits == 16)
        {
            if (digits == 16)
            {
                if ((fdigits == 51 || fdigits == 52) || ((fdigits == 53 || fdigits == 54) || fdigits == 55))
                {
                    // MC
                    printf("MASTERCARD\n");
                    return 0;
                }
                else if (fdigits / 10 == 4)
                {
                    // VISA
                    printf("VISA\n");
                    return 0;
                }
                else
                {
                    printf("INVALID\n");
                    return 0;
                }
            }
            else if (fdigits / 10 == 4)
            {
                // VISA
                printf("VISA\n");
                return 0;
            }
            else
            {
                printf("INVALID\n");
                return 0;
            }
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }
}

int digit(long int n)
{
    // counting the number of digits of the credit card number
    int count = 0;

    do
    {
        n /= 10;
        count++;
    }
    while (n != 0);

    return count;
}

int fdigit(long int f, int d)
{
    // to count the first two digits of the number
    int l = d - 2; // for first two digits

    for (int i = 0; i < l; i++)
    {
        f /= 10;
    }

    return f;
}

bool checksum(long int c, int e)
{
    // checksum based on Luhn's algorithm
    int sum2, sum = 0, Sum = 0;
    for (int i = 0; i < (e / 2) + 1; i++)
    {

        sum += c % 10;
        c /= 10;

        sum2 = (c % 10) * 2;
        c /= 10;

        if (sum2 > 9)
        {
            Sum += sum2 % 10;
            sum2 /= 10;
            Sum += sum2;
        }
        else
        {
            Sum += sum2;
        }
    }

    int total = sum + Sum;

    if ((total % 10) == 0)
    {
        return true;
    }
    else
        return false;
}
