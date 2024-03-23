#include <stdio.h>

void print_arr(int *arr, int size)
{
    if (size == 0)
    {
        return;
    }

    printf("%d\n", arr[size - 1]);

    print_arr(arr, size - 1);
}

int main()
{
    int arr[6] = {1,
                  2,
                  3,
                  4,
                  5,
                  6};

    print_arr(arr, 6);
}