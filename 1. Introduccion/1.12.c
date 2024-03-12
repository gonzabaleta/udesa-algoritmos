#include <stdio.h>
#include <stdbool.h>

bool twoSum(int *arr, int size, int target)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (arr[i] == arr[j])
                continue;
            if (arr[i] + arr[j] == target)
                return true;
        }
    }

    return false;
}