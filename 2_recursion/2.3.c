#include <stdio.h>

int fact(int n)
{
    if (n <= 1)
    {
        return 1;
    }

    return n * fact(n - 1);
}

int main()
{
    printf("%d\n", fact(1));
    printf("%d\n", fact(2));
    printf("%d\n", fact(3));
    printf("%d\n", fact(4));
    printf("%d\n", fact(5));
    printf("%d\n", fact(6));
    printf("%d\n", fact(7));
    printf("%d\n", fact(8));
}