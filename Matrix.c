#include <stdio.h>
#include <stdlib.h>

int **createMatrix(int length)
{
	int **matrix = (int**)malloc(sizeof(*matrix)*length);
	for (int i = 0; i < length; i++)
		matrix[i] = (int*)malloc(sizeof(int)*length);
	return matrix;
}

void initMatrix(int** matrix, int length, int number)
{
	int i, j;
	for (i = 0; i < length; i++)
	{
		for (j = 0; j < length; j += 2)
			matrix[i][j] = number;
		for (j = 1; j < length; j += 2)
			matrix[i][j] = abs(number - 1);
	}
}

void displayMatrix(int** matrix, int length)
{
	int i, j;
	for (i = 0; i < length; i++)
	{
		for (j = 0; j < length; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}
}

int **multiplyMatrix(int** left, int** right, int length)
{
	int** result = createMatrix(length);
	int i, j;
	for (i = 0; i < length; i++)
	{
		for (j = 0; j < length; j++)
		{
			result[i][j] = left[i][j] * right[j][i];
		}
	}
	return result;
}

int main()
{
	int length = 4;
	int **left = createMatrix(length);
	int **right = createMatrix(length);
	initMatrix(left, length, 1);
	initMatrix(right, length, 0);
	displayMatrix(left, length);
	printf("\n");
	displayMatrix(right, length);
	printf("\n");
	displayMatrix(multiplyMatrix(left, right, length), length);
	return 0;
}