#include <stdio.h>

void crearArreglo(int v)
{
    int arr[8];
    printf("[");

    for (int i = 0; i < 8; i++)
    {
        arr[i] = v;
        if (i == 7)
        {
            printf("%i", v);
        }
        else
        {
            printf("%i, ", v);
        }
    }

    printf("]\n");
}

int *crearArregloDin(int n, int v)
{
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = v;
    }

    return arr;
}

void mostrarMemoria(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Elemento: %d, Dirección: %d\n", i, &arr[i]);
    }
}

int main()
{
    crearArreglo(7);
    crearArreglo(20);

    mostrarMemoria(crearArregloDin(5, 5), 5);
}