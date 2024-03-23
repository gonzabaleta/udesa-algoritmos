#include <stdio.h>

int fibo(int n)
{
    if (n == 0)
    {
        return 0;
    }
    if (n == 1 || n == 2)
    {
        return 1;
    }

    return fibo(n - 1) + fibo(n - 2);
}

int main()
{
    printf("%d\n", fibo(1));
    printf("%d\n", fibo(2));
    printf("%d\n", fibo(3));
    printf("%d\n", fibo(4));
    printf("%d\n", fibo(5));
    printf("%d\n", fibo(6));
    printf("%d\n", fibo(7));
}