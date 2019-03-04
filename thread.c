#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define GOAL 100000000

void executeThread(int number, char* type);
void *addDouble(void *args);
void *addFloat(void *args);

struct ARGS
{
  int thread_id;
  long rounds;
};


int main()
{
  printf("Double test\n");
  executeThread(1, "double");
  executeThread(2, "double");
  executeThread(4, "double");
  executeThread(8, "double");
  printf("\n");
  printf("Float test\n");
  executeThread(1, "float");
  executeThread(2, "float");
  executeThread(4, "float");
  executeThread(8, "float");
  
  return 0;
}

void executeThread(int number, char* type)
{
  printf("%d threads are creating, please wait...\n", number);
  pthread_t thread_id[number];
  struct ARGS *args[number];
  clock_t begin = clock();
  if(strcmp(type, "double") == 0)
  {
    for(int i = 0; i < number; i++)
    {
      args[i] = (struct ARGS*)malloc(sizeof(struct ARGS));
      args[i]->thread_id = i+1;
      args[i]->rounds = GOAL/number;
      printf("Thread %d, GOAL %d, number %d, round is %ld\n", args[i]->thread_id, GOAL, number, args[i]->rounds);
      pthread_create(&thread_id[i], NULL, addDouble, args[i]);
    }
  }
  else
  {
    for(int i = 0; i < number; i++)
    {
      args[i] = (struct ARGS*)malloc(sizeof(struct ARGS));
      args[i]->thread_id = i+1;
      args[i]->rounds = GOAL/number;
      printf("Thread %d, GOAL %d, number %d, round is %ld\n", args[i]->thread_id, GOAL, number, args[i]->rounds);
      pthread_create(&thread_id[i], NULL, addFloat, args[i]);
    }
  }

  for(int i = 0; i < number; i++)
  {
    pthread_join( thread_id[i], NULL);
  }
  clock_t end = clock();
  double time = (double)(end-begin) / CLOCKS_PER_SEC;
  double efficiency = (double)(GOAL / time / 1000000000);
  printf("%d threads finish, benchmark = %f giga/s\n", number, efficiency);
}

void *addFloat(void *args)
{
  struct ARGS *parameters = (struct ARGS*) args;
  int thread_id = parameters->thread_id;
  long rounds = parameters->rounds;
  float local_float = 0;
  for(long i = 0; i < rounds; i++)
  {
    local_float++;
  }
  printf("Therad %d finish, local_float: %f\n", thread_id, local_float);
}

void *addDouble(void *args)
{
  struct ARGS *parameters = (struct ARGS*) args;
  int thread_id = parameters->thread_id;
  long rounds = parameters->rounds;
  double local_double = 0;
  for(long i = 0; i < rounds; i++)
  {
    local_double++;
  }
  printf("Therad %d finish, local_double: %f\n", thread_id, local_double);
}
