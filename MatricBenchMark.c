#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define DOUBLE  0
#define FLOAT   1

void** answer_global;

struct ARGS
{
  int thread_id;
  void **left;
  void **right;
  void **answer;
  int length;
  int type;
  int start;
  int end;
};


void **createMatrix(int length, int type, void* number);
void displayMatrix(void** matrix, int length, int type);
void **multiplyMatrix(void** left_1, void** right_1, void** answer_1, int length, int type, int start, int end);
void executeThread(int number, void** left_1, void** right_1, void** answer_1, int length, int type);
void *threadTask(void *args);
void initMatrix(void** matrix_1, int length, int type);

int main()
{
  double a = 1, b = 2, c = 0;
  float d = 1, e = 2, f = 0;
  int length = 1000;
  //Create two matrics and answer to hold result.
  void** left = createMatrix(length, DOUBLE, &a);
  void** right = createMatrix(length, DOUBLE, &b);
  void** answer = createMatrix(length, DOUBLE, &c);
  //Executing threads.
  executeThread(1, left, right, answer, length, DOUBLE);
  initMatrix(answer, length, DOUBLE);
  executeThread(2, left, right, answer, length, DOUBLE);
  initMatrix(answer, length, DOUBLE);
  executeThread(4, left, right, answer, length, DOUBLE);
  initMatrix(answer, length, DOUBLE);
  executeThread(8, left, right, answer, length, DOUBLE);

  return 0;
}

void executeThread(int number, void** left_1, void** right_1, void** answer_1, int length, int type)
{
  printf("%d threads are creating, please wait...\n", number);
  pthread_t thread_id[number];
  int begin = 0;
  int slice = length / number;
  struct ARGS *args[number];
  time_t start = time(NULL);
  for(int i = 0; i < number; i++)
  {
    args[i] = (struct ARGS*)malloc(sizeof(struct ARGS));
    args[i]->thread_id = i+1;
    args[i]->left = left_1;
    args[i]->right = right_1;
    args[i]->answer = answer_1;
    args[i]->length = length;
    args[i]->type = type;
    args[i]->start = begin;
    args[i]->end = begin + slice - 1;
    begin += slice;
    pthread_create(&thread_id[i], NULL, threadTask, args[i]);
  }
  for(int i = 0; i < number; i++)
  {
    pthread_join( thread_id[i], NULL);
  }
  time_t end = time(NULL);
  //displayMatrix(answer_global, length, type);
  printf("\n");
  double time = (double)(end-start);
  double efficiency = (length*length) / 1000000000 / time;
  printf("%d threads finish, benchmark = %f giga/s\n", number, time);
}

void *threadTask(void *args)
{
  struct ARGS *parameters = (struct ARGS*) args;
  answer_global = multiplyMatrix(parameters->left, parameters->right, 
                   parameters->answer, parameters->length, parameters->type, 
                   parameters->start, parameters->end);
  //displayMatrix(answer_global, parameters->length, parameters->type);
  //printf("\n");
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
         martrix[i][j] = element;
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
        martrix[i][j] = element;
    }
    return (void**)martrix;
  }
  return NULL;
}

void initMatrix(void** matrix_1, int length, int type)
{
  if(type == DOUBLE)
  {
    double** matrix = (double**) matrix_1;
    for(int i = 0 ; i < length; i++)
    {
      for(int j = 0; j < length; j++)
        matrix[i][j] = 0;
    }
    return;
  }
  if(type == FLOAT)
  {
    float** matrix = (float**) matrix_1;
    for(int i = 0 ; i < length; i++)
    {
      for(int j = 0; j < length; j++)
        matrix[i][j] = 0;
    }
    return;
  }
  return;
 
}

void displayMatrix(void** matrix, int length, int type)
{
  if (type == DOUBLE)
  {
    double** answer = (double**)matrix;
    for (int i = 0; i < length; i++)
    {
      for (int j = 0; j < length; j++)
        printf("%.1f\t", answer[i][j]);
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
        printf("%.1f\t", answer[i][j]);
      printf("\n");
    }
    return;
  }
  printf("Error: unknow type!");
}

void **multiplyMatrix(void** left_1, void** right_1, void** answer_1, int length, int type, int start, int end)
{
  if (type == DOUBLE)
  {
    double **left = (double**)left_1;
    double **right = (double**)right_1;
    double number = 0;
    double **answer = (double**)answer_1;
    int i, j, k;
    for (i = start; i <= end; i++)
    {
      for (j = 0; j < length; j++)
      {
        answer[i][j] = 0;
          for (k = 0; k < length; k++)
            answer[i][j] += left[i][k] * right[k][j];
      }
    }
      return (void**)answer;
  }

  if (type == FLOAT)
  {
    float **left = (float**)left_1;
    float **right = (float**)right_1;
    float number = 0;
    float **answer = (float**)answer_1;
    int i, j, k;
    for (i = start; i < end; i++)
    {
      for (j = 0; j <= length; j++)
      {
        answer[i][j] = 0;
        for (k = 0; k < length; k++)
          answer[i][j] += left[i][k] * right[k][j];
      }
    }
    return (void**)answer;
  }
  return NULL;
}
