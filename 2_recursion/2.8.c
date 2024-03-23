#include <stdio.h>

int ocurrencias(int *arr, int n, int elem)
{
    if (n == 0)
    {
        return 0;
    }
    int iteration_count = arr[0] == elem ? 1 : 0;

    return iteration_count + ocurrencias(arr + 1, n - 1, elem);
}

int main()
{
    int arr[10] = {1, 2, 2, 2, 2, 2, 2, 3, 2};

    printf("%d\n", ocurrencias(arr, 10, 2));
}