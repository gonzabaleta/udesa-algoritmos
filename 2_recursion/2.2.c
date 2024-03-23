#include <stdio.h>

int sum(int n)
{
    if (n <= 0)
    {
        return 0;
    }

    return n + sum(n - 1);
}

int main()
{
    printf("%d\n", sum(1));
    printf("%d\n", sum(2));
    printf("%d\n", sum(3));
    printf("%d\n", sum(4));
    printf("%d\n", sum(5));
    printf("%d\n", sum(6));
    printf("%d\n", sum(7));
    printf("%d\n", sum(8));
}