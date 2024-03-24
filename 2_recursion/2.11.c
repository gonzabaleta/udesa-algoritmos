#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool search(int *arr, int len, int elem)
{
    int middle = (int)floor(len / 2);

    if ((len == 1 && arr[0] != elem) || len == 0)
    {
        return false;
    }

    if (arr[middle] == elem)
    {
        return true;
    }

    if (search(arr, middle, elem) || search(arr + middle, len - middle, elem))
    {
        return true;
    };

    return false;
}

int main()
{
    int arr[10] = {1,
                   2,
                   2,
                   4,
                   5,
                   6,
                   7,
                   8,
                   9,
                   10};

    printf("%s\n", search(arr, 10, 11) ? "true" : "false");
}
