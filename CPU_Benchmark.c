#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *add();
double oneThread();
double twoThreads();
double fourThreads();
double eightThreads();

#define rounds 1000000000
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

int main()
{
  oneThread();
  twoThreads();
  fourThreads();
  eightThreads();
  return 0;
}

double oneThread()
{
  printf("One thread is exeuting, please wait...\n");
  counter = 0;
  clock_t begin = clock();
  while(counter < rounds) { counter++; }
  clock_t end = clock();
  double time = (double)(end-begin) / CLOCKS_PER_SEC;
  double efficiency = (double)(rounds / time);
  printf("One thread finish, counter = %d, benchmark = %f i/s\n", counter, efficiency);
}

double twoThreads()
{
  printf("Two threads are exeuting, please wait...\n");
  
  counter = 0;
  int rc1, rc2;
  pthread_t thread1, thread2;

  clock_t begin = clock();
  if(rc1 = pthread_create(&thread1, NULL, &add, (void*)&thread1))
  {
    printf("thread %d creation failed!\n", rc1);
  }
  if(rc2 = pthread_create(&thread2, NULL, &add, (void*)&thread2))
  {
    printf("thread %d creation failed!\n", rc2);
  }
  
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  clock_t end = clock();
  double time = (double)(end-begin) / CLOCKS_PER_SEC;
  double efficiency = (double)(rounds / time);
  printf("Two threads finish, counter = %d, benchmark = %f i/s\n", counter, efficiency);
}

double fourThreads()
{
  printf("Four threads are exeuting, please wait...\n");
  
  counter = 0;
  int rc1, rc2, rc3, rc4;
  pthread_t thread1, thread2, thread3, thread4;

  clock_t begin = clock();
  if(rc1 = pthread_create(&thread1, NULL, &add, (void*)&thread1))
  {
    printf("thread %d creation failed!\n", rc1);
  }
  if(rc2 = pthread_create(&thread2, NULL, &add, (void*)&thread2))
  {
    printf("thread %d creation failed!\n", rc2);
  }
  if(rc3 = pthread_create(&thread3, NULL, &add, (void*)&thread3))
  {
    printf("thread %d creation failed!\n", rc3);
  }
  if(rc4 = pthread_create(&thread4, NULL, &add, (void*)&thread4))
  {
    printf("thread %d creation failed!\n", rc4);
  }
  
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);
  pthread_join(thread4, NULL);
  clock_t end = clock();
  double time = (double)(end-begin) / CLOCKS_PER_SEC;
  double efficiency = (double)(rounds / time);
  printf("Four threads finish, counter = %d, benchmark = %f i/s\n", counter, efficiency);
}

double eightThreads()
{
  printf("Eight threads are exeuting, please wait...\n");
  
  counter = 0;
  int rc1, rc2, rc3, rc4, rc5, rc6, rc7, rc8;
  pthread_t thread1, thread2, thread3, thread4, thread5, thread6,thread7, thread8;

  clock_t begin = clock();
  if(rc1 = pthread_create(&thread1, NULL, &add, (void*)&thread1))
  {
    printf("thread %d creation failed!\n", rc1);
  }
  if(rc2 = pthread_create(&thread2, NULL, &add, (void*)&thread2))
  {
    printf("thread %d creation failed!\n", rc2);
  }
  if(rc3 = pthread_create(&thread3, NULL, &add, (void*)&thread3))
  {
    printf("thread %d creation failed!\n", rc3);
  }
  if(rc4 = pthread_create(&thread4, NULL, &add, (void*)&thread4))
  {
    printf("thread %d creation failed!\n", rc4);
  }
  if(rc5 = pthread_create(&thread5, NULL, &add, (void*)&thread5))
  {
    printf("thread %d creation failed!\n", rc5);
  }
  if(rc6 = pthread_create(&thread6, NULL, &add, (void*)&thread6))
  {
    printf("thread %d creation failed!\n", rc6);
  }
  if(rc7 = pthread_create(&thread7, NULL, &add, (void*)&thread7))
  {
    printf("thread %d creation failed!\n", rc7);
  }
  if(rc8 = pthread_create(&thread8, NULL, &add, (void*)&thread8))
  {
    printf("thread %d creation failed!\n", rc8);
  }
  
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);
  pthread_join(thread4, NULL);
  pthread_join(thread5, NULL);
  pthread_join(thread6, NULL);
  pthread_join(thread7, NULL);
  pthread_join(thread8, NULL);
  clock_t end = clock();
  double time = (double)(end-begin) / CLOCKS_PER_SEC;
  double efficiency = (double)(rounds / time);
  printf("Eight threads finish, counter = %d, benchmark = %f i/s\n", counter, efficiency);
}

void *add(void *id)
{
  while(counter < rounds)
  {
    pthread_mutex_lock(&mutex1);
    //int *a = (int *) id;
    //printf("thread id = %d, counter = %d\n", *a, counter);
    counter++;
    pthread_mutex_unlock(&mutex1);
  }
}


