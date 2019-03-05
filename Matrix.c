#include <stdio.h>
#include <stdlib.h>

int **createMatrix(int length);
void initMatrix(int** matrix, int length);
void setMatrix(int **matrix, int length, int number);
void displayMatrix(int** matrix, int length);
int **multiplyMatrix(int** left, int** right, int length);

int main()
{
  int length = 4;
  int **left = createMatrix(length);
  int **right = createMatrix(length);
  setMatrix(left, length, 2);
  setMatrix(right, length, 1);
  displayMatrix(left, length);
  printf("\n");
  displayMatrix(right, length);
  printf("\n");
  displayMatrix(multiplyMatrix(left, right, length), length);
  return 0;
}

int **createMatrix(int length)
{
  int **matrix = (int**)malloc(sizeof(*matrix)*length);
  for (int i = 0; i < length; i++)
    matrix[i] = (int*)malloc(sizeof(int)*length);
  initMatrix(matrix, length);
  return matrix;
}

void initMatrix(int** matrix, int length)
{
  int i, j;
  for (i = 0; i < length; i++)
  {
    for (j = 0; j < length; j++)
      matrix[i][j] = 0;
  }
}

void setMatrix(int **matrix, int length, int number)
{
  if (number == 0) return;
  int i, j;
  for (i = 0; i < length; i++)
  {
    if (number % 2 == 0)
    {
      for (j = 0; j < length; j += 2)
        matrix[i][j] = number;
    }
    else
    {
      for (j = 1; j < length; j += 2)
        matrix[i][j] = number;
    }
  }
}

void displayMatrix(int** matrix, int length)
{
  int i, j;
  for (i = 0; i < length; i++)
  {
    for (j = 0; j < length; j++)
      printf("%d\t", matrix[i][j]);
    printf("\n");
  }
}

int **multiplyMatrix(int** left, int** right, int length)
{
  int** result = createMatrix(length);
  int i, j, k, temp = 0;
  for (i = 0; i < length; i++)
  {
    for (k = 0; k < length; k++)
    {
      for (j = 0; j < length; j++)
        temp += (left[i][j] * right[j][i]);
          result[i][k] = temp;
          temp = 0;
    }
  }
  return result;
}
