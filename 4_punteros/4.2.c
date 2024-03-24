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

int main()
{
    int row1[] = {1, 2};
    int row2[] = {3, 4};
    int row3[] = {5, 6};
    int *matrix[] = {row1, row2, row3};

    imprimirMatriz(matrix, 3, 2);
}