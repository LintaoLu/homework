#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DOUBLE 0
#define FLOAT  1

void **createMatrix(int length, int type, void* number);
void displayMatrix(void** matrix, int length, int type);
void **multiplyMatrix(void** left_1, void** right_1, int length, int type);

int main()
{
	double a = 1, b = 2;
	float c = 1;
	int length = 5;
	double** left = (double**)createMatrix(length, DOUBLE, &a);
	displayMatrix((void**)left, length, DOUBLE);
	printf("\n");
	double** right = (double**)createMatrix(length, DOUBLE, &b);
	displayMatrix((void**)right, length, DOUBLE);
	printf("\n");
	double** answer = (double**)multiplyMatrix((void**)left, (void**)right, length, DOUBLE);
	displayMatrix((void**)answer, length, DOUBLE);
	return 0;
}

void **createMatrix(int length, int type, void* number)
{
	if (type == DOUBLE)
	{
		double element = *((double*)number);
		double **martrix = (double**)malloc(sizeof(*martrix)*length);
		for (int i = 0; i < length; i++)
		{
			martrix[i] = (double*)malloc(sizeof(double)*length);
			for (int j = 0; j < length; j++)
				martrix[i][j] = element++;
		}
		return (void**)martrix;
	}
	if (type == FLOAT)
	{
		float element = *((float*)number);
		float **martrix = (float**)malloc(sizeof(*martrix)*length);
		for (int i = 0; i < length; i++)
		{
			martrix[i] = (float*)malloc(sizeof(float)*length);
			for (int j = 0; j < length; j++)
				martrix[i][j] = element++;
		}
		return (void**)martrix;
	}
	return NULL;
}

void displayMatrix(void** matrix, int length, int type)
{
	if (type == DOUBLE)
	{
		double** answer = (double**)matrix;
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
				printf("%f\t", answer[i][j]);
			printf("\n");
		}
		return;
	}

	if (type == FLOAT)
	{
		float** answer = (float**)matrix;
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
				printf("%f\t", answer[i][j]);
			printf("\n");
		}
		return;
	}
	printf("Error: unknow type!");
}

void **multiplyMatrix(void** left_1, void** right_1, int length, int type)
{
	if (type == DOUBLE)
	{
		double **left = (double**)left_1;
		double **right = (double**)right_1;
		double number = 0;
		double **answer = (double**)createMatrix(length, type, &number);
		int i, j, k;
		for (i = 0; i < length; i++)
		{
			for (k = 0; k < length; k++)
			{
				for (j = 0; j < length; j++)
					number += (left[i][j] * right[j][i]);
				answer[i][k] = number;
				number = 0;
			}
		}
		return (void**)answer;
	}

	if (type == FLOAT)
	{
		float **left = (float**)left_1;
		float **right = (float**)right_1;
		float number = 0;
		float **answer = (float**)createMatrix(length, type, &number);
		int i, j, k;
		for (i = 0; i < length; i++)
		{
			for (k = 0; k < length; k++)
			{
				for (j = 0; j < length; j++)
					number += (left[i][j] * right[j][i]);
				answer[i][k] = number;
				number = 0;
			}
		}
		return (void**)answer;
	}
	return NULL;
}

