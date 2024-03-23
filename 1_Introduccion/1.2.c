#include <stdio.h>

int sum_odd(int n)
{
    if (n == 1)
    {
        return 0;
    }

    int sum = 0;

    for (int i = 1; i < n; i++)
    {
        if (i % 2 == 1)
        {
            sum += i;
        }
    }

    return sum;
}

int main()
{
    printf("%i: %i\n", 1, sum_odd(1));
    printf("%i: %i\n", 2, sum_odd(2));
    printf("%i: %i\n", 3, sum_odd(3));
    printf("%i: %i\n", 4, sum_odd(4));
    printf("%i: %i\n", 5, sum_odd(5));
    printf("%i: %i\n", 10, sum_odd(10));
    printf("%i: %i\n", 17, sum_odd(17));
}