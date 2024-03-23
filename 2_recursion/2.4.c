#include <stdio.h>

int mypow(int a, int n)
{
    if (n == 0)
    {
        return 1;
    }

    return a * mypow(a, n - 1);
}

int main()
{
    printf("%d\n", mypow(3, 0));
    printf("%d\n", mypow(3, 1));
    printf("%d\n", mypow(3, 2));
    printf("%d\n", mypow(3, 3));
    printf("%d\n", mypow(3, 4));
    printf("%d\n", mypow(3, 5));
    printf("%d\n", mypow(3, 6));
    printf("%d\n", mypow(3, 7));
}