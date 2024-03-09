#include "tp1.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

bool is_prime(int x)
{
    if (x == 1 || x == 2)
        return true;

    for (int i = 2; i < x; i++)
    {
        if (x % i == 0)
            return false;
    }
    return true;
}

int storage_capacity(float d, float v)
{
    return (int)floor(d / v);
}

void swap(int *x, int *y)
{
    int x_value = *x;
    *x = *y;
    *y = x_value;
    return;
}

int array_max(const int *array, int length)
{
    if (length == 0)
        return 0;
    int max = array[0];
    for (int i = 1; i < length; i++)
    {
        if (array[i] > max)
            max = array[i];
    }

    return max;
}

void array_map(int *array, int length, int f(int))
{
    if (f == NULL)
        return;

    for (int i = 0; i < length; i++)
    {
        array[i] = f(array[i]);
    }
    return;
}

int *copy_array(const int *array, int length)
{
    if (array == NULL)
        return NULL;

    int *copy = malloc(sizeof(int) * length);

    for (int i = 0; i < length; i++)
    {
        copy[i] = array[i];
    }

    return copy;
}

int **copy_array_of_arrays(const int **array_of_arrays, const int *array_lenghts, int array_amount)
{
    if (array_of_arrays == NULL)
        return NULL;

    long unsigned int required_size = 0;
    for (int i = 0; i < array_amount; i++)
    {
        required_size += (array_lenghts[i] * sizeof(int));
    }

    int **array_copy = (int **)malloc(required_size);

    for (int i = 0; i < array_amount; i++)
    {
        if (array_of_arrays[i] == NULL)
        {
            array_copy[i] = NULL;
            continue;
        }
        array_copy[i] = (int *)malloc(array_lenghts[i] * sizeof(int));
        for (int j = 0; j < array_lenghts[i]; j++)
        {
            array_copy[i][j] = array_of_arrays[i][j];
        }
    }

    return array_copy;
}

void free_array_of_arrays(int **array_of_arrays, int *array_lenghts, int array_amount)
{
    for (int i = 0; i < array_amount; i++)
    {
        free(array_of_arrays[i]);
    }

    free(array_of_arrays);
    free(array_lenghts);
}

void bubble_sort(int *array, int length)
{
    if (array == NULL)
        return;

    int swaps;
    do
    {
        swaps = 0;
        for (int i = 0; i < (length - 1); i++)
        {
            if (array[i] > array[i + 1])
            {
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                swaps++;
            }
        }
    } while (swaps != 0);
}

bool array_equal(const int *array1, int length1, const int *array2, int length2)
{
    if (array1 == NULL || array2 == NULL)
        return array1 == NULL && array2 == NULL;

    if (length1 != length2)
        return false;

    for (int i = 0; i < length1; i++)
    {
        if (array1[i] != array2[i])
            return false;
    }

    return true;
}

bool integer_anagrams(const int *array1, int length1,
                      const int *array2, int length2)
{
    if (array1 == NULL || array2 == NULL || length1 != length2)
        return false;

    for (int i = 0; i < length1; i++)
    {
        int num = array1[i];

        int num_count_in_1 = 0;
        int num_count_in_2 = 0;
        for (int j = 0; j < length1; j++)
        {
            if (array1[j] == num)
            {
                num_count_in_1++;
            }

            if (array2[j] == num)
            {
                num_count_in_2++;
            }
        }

        if (num_count_in_1 != num_count_in_2)
            return false;
    }

    return true;
}