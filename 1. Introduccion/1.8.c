#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int maximo(int *arr, int size)
{
    int max = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    return max;
}

void sumador(int *arr, int size, int c)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] += c;
    }
}

char *copiar(char *arr)
{
    int length = strlen(arr);
    char copy[length];

    for (int i = 0; i < length; i++)
    {
        copy[i] = arr[i];
    }

    return copy;
}

int *reverso(int *arr, int size)
{
    int *reverse = malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++)
    {
        reverse[i] = arr[size - 1 - i];
    }

    return reverse;
}

bool estaOrdenado(int *arr, int size)
{
    bool isCreciente = true;
    bool isDecreciente = true;

    for (int i = 0; i < (size - 1); i++)
    {
        int a = arr[i];
        int b = arr[i + 1];

        if (a <= b)
        {
            isDecreciente = false;
        }

        if (a >= b)
        {
            isCreciente = false;
        }

        return isDecreciente || isCreciente;
    }
}

int main()
{
    int nums[] = {1,
                  2,
                  3,
                  4,
                  5,
                  4,
                  4,
                  3,
                  2,
                  5};
    int size = 10;

    // MAX
    printf("MAX: %d\n", maximo(nums, size));

    // SUMADOR
    sumador(nums, size, 3);
    printf("SUMADOR: [");
    for (int i = 0; i < size; i++)
    {
        printf("%d", nums[i]);
    }
    printf("]\n");

    // COPIAR
    char *nombre = "GONZALO";
    char *nombre_copy = copiar(nombre);
    printf("COPIAR: %c%c%c\n", nombre_copy[0], nombre_copy[1], nombre_copy[2]);

    // REVERSO
    printf("REVERSO: ");
    int *reverse = reverso(nums, size);
    for (int i = 0; i < size; i++)
    {
        printf("%d", reverse[i]);
    }

    free(reverse);

    // ESTA ORDENADO
    int ordered[5] = {1, 2, 3, 4, 5};
    int ordered2[5] = {5, 4, 3, 2, 1};
    int unordered[5] = {1, 1, 2, 3, 4};
    int unordered2[5] = {5, 5, 2, 6, 7};
    printf("\nORDENADO: %s ", estaOrdenado(ordered, 5) ? "true" : "false");
    printf("%s ", estaOrdenado(ordered2, 5) ? "true" : "false");
    printf("%s ", estaOrdenado(unordered, 5) ? "true" : "false");
    printf("%s ", estaOrdenado(unordered2, 5) ? "true" : "false");
}