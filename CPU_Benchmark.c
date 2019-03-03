#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define GOAL 100000000

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

void *add(void *args);
void executeThread(int number);

int main()
{
  pthread_mutex_init(&mutex1, NULL);
  executeThread(1);
  executeThread(2);
  executeThread(4);
  executeThread(8);
  return 0;
}

void executeThread(int number)
{
  printf("%d threads are executing, please wait...\n", number);
  int i, j;
  counter = 0;
  pthread_t thread_id[number];
  //Set clock.
  clock_t begin = clock();
  for(i = 0; i < number; i++)
  {
    pthread_create(&thread_id[i], NULL, add, &number);
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
  int round = 0;
  int *number = (int*) args;
  while(counter < GOAL && round < GOAL/(*number))
  {
    pthread_mutex_lock(&mutex1);
    round++;
    //printf("%d threads running\n", (*number));
    counter++;
    pthread_mutex_unlock(&mutex1);
  }
}
