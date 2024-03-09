#include <stdio.h>

void ordenar(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        int min = arr[i];
        for (int j = i; j < size; j++)
        {
            if (arr[j] < min)
            {
                min = arr[j];
            }
        }

        arr[i] = min;
    }
}

int main()
{
    int nums[10] = {1,
                    6,
                    4,
                    3,
                    3,
                    2,
                    6,
                    8,
                    4,
                    3};
    ordenar(nums, 10);

    for (int i = 0; i < 10; i++)
    {
        printf("%d", nums[i]);
    }
    printf("\n");
}