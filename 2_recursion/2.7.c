#include <stdio.h>

int max(int *arr, int n)
{
    if (n == 0)
    {
        return 0;
    }

    if (n == 1)
    {
        return arr[0];
    }

    int potential_max = max(arr + 1, n - 1);

    return arr[0] > potential_max ? arr[0] : potential_max;
}

int main()
{
    int arr[9] = {1,
                  2,
                  5,
                  7,
                  2,
                  4,
                  8,
                  2,
                  78};

    printf("%d\n", max(arr, 9));
}