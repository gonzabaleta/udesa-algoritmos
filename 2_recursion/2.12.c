#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int *buscarRangoN(int *arr, int size, int target)
{
    int *range = malloc(sizeof(int) * 2);
    bool inRange = false;

    for (int i = 0; i < size; i++)
    {
        bool foundTarget = arr[i] == target;
        if (foundTarget && !inRange)
        {
            inRange = true;
            range[0] = i;
        }

        if (!foundTarget && inRange)
        {
            inRange = false;
            range[1] = i - 1;
        }
    }

    return range;
}

int *buscarRangoLog(int *arr, int size, int target)
{
    int *range = malloc(sizeof(int) * 2);
    bool inRange = false;

    for (int i = 0; i < size; i++)
    {
        bool foundTarget = arr[i] == target;
        if (foundTarget && !inRange)
        {
            inRange = true;
            range[0] = i;
        }

        if (!foundTarget && inRange)
        {
            inRange = false;
            range[1] = i - 1;
        }
    }

    return range;
}

int main()
{
    int arr[] = {5,
                 7,
                 7,
                 8,
                 8,
                 8,
                 10};

    int *n = buscarRangoN(arr, 7, 8);
    int *log = buscarRangoLog(arr, 7, 8);

    printf("[%d, %d]\n", n[0], n[1]);
    printf("[%d, %d]\n", log[0], log[1]);
}