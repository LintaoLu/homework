#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define GOAL 2000000000

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

void *add(void *args);
void executeThread(int number);

int main()
{
  pthread_mutex_init(&mutex1, NULL);
  printf("1 threads are executing, please wait...\n");
  clock_t begin = clock();
  while(counter < GOAL)
  {
    counter++;
  }
  clock_t end = clock();
  double time = (double)(end-begin) / CLOCKS_PER_SEC;
  double efficiency = (double)(GOAL / time);
  printf("1 threads finish, counter = %d, benchmark = %f i/s\n", counter, efficiency);
  executeThread(2);
  executeThread(4);
  executeThread(8);
  return 0;
}

void executeThread(int number)
{
  printf("%d threads are executing, please wait...\n", number);
  counter = 0;
  pthread_t thread_id[number];
  int i, j;
  clock_t begin = clock();
  for(i = 0; i < number; i++)
  {
    pthread_create(&thread_id[i], NULL, add, &thread_id[i]);
  }

  for(j = 0; j < number; j++)
  {
    pthread_join( thread_id[j], NULL);
  }
  clock_t end = clock();
  double time = (double)(end-begin) / CLOCKS_PER_SEC;
  double efficiency = (double)(GOAL / time);
  printf("%d threads finish, counter = %d, benchmark = %f i/s\n", number, counter, efficiency);
}

void *add(void *args)
{
  pthread_mutex_lock(&mutex1);

  int round = 0;
  int *thread_args = (int*) args;
  printf("This is thread: %d\n", *thread_args);
  while(counter < GOAL && round < GOAL/2)
  {
    round++;
    counter++;
  }

  pthread_mutex_unlock(&mutex1);
}
