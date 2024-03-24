#include <stdio.h>

void imprimirMatriz(int **matrix, int filas, int columnas)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            printf("%d, ", matrix[i][j]);
        }
    }
    printf("\n");
}

void traspuesta(int **matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
        }
    }
}

int main()
{
    int row1[] = {1, 2, 3};
    int row2[] = {4, 5, 6};
    int row3[] = {7, 8, 9};
    int *matrix[] = {row1, row2, row3};

    imprimirMatriz(matrix, 3, 3);
}