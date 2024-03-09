#include <stdio.h>
#include <stdbool.h>

bool is_prime(int n)
{
    if (n == 1)
    {
        return true;
    }

    bool is_prime = true;

    for (int i = 2; i < n; i++)
    {
        if (n % i == 0)
        {
            is_prime = false;
        }
    }

    return is_prime;
}

int main()
{
    printf("%i: %s", 1, is_prime(1) ? "true\n" : "false\n");
    printf("%i: %s", 2, is_prime(2) ? "true\n" : "false\n");
    printf("%i: %s", 3, is_prime(3) ? "true\n" : "false\n");
    printf("%i: %s", 4, is_prime(4) ? "true\n" : "false\n");
    printf("%i: %s", 5, is_prime(5) ? "true\n" : "false\n");
    printf("%i: %s", 10, is_prime(10) ? "true\n" : "false\n");
    printf("%i: %s", 17, is_prime(17) ? "true\n" : "false\n");
}