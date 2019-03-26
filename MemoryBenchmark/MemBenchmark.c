#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

//Size. 1GB.
#define SIZE 1073741824
//Copy 100GB data.
#define ROUNDS 100
//Latency test.
#define LATENCY_TEST 100000000
#define SEQUENCE 0
#define RANDOM 1

char *FROM;
char *TO; 
long *random_num_array = NULL;

struct ARGS
{
  int thread_id;
  char *start;
  char *destination;
  long workload;
  long block;
};

void createThreads(int number, long block, int type, long size);
void executeThreads(char *from, char *to, int number, long workload, int type, long size);
long *generateRandomNum(long loops, long workload, long block);
char *createBlock(long size);
void *scopy(void *args);
void *rcopy(void *args);
void latencyTest();
void memoryTest();

int main()
{ 
  FROM = createBlock(SIZE);
  TO = createBlock(SIZE); 
  memoryTest();
  free(FROM);
  free(TO); 
  FROM = createBlock(LATENCY_TEST);
  TO = createBlock(LATENCY_TEST); 
  latencyTest()
  free(FROM);
  free(TO); 
  return 0;
}	

//This method is used by Randomlty copy, becasue geneate random
//address may cost too much time.
long *generateRandomNum(long loops, long workload, long block)
{
  long *randomNumberArray = (long*)malloc(sizeof(long)*loops);
  for(long i = 0; i < loops; i++)
  {
    *(randomNumberArray+i) = (long)rand()%(workload-block+1);
  }
  return randomNumberArray;
}

//Sequential copy.
void *scopy(void *args)
{
  struct ARGS *parameters = (struct ARGS*) args;
  int thread_id = parameters->thread_id;
  char *start = parameters->start;
  char *destination = parameters->destination;
  long workload = parameters->workload;
  long block = parameters->block;
  printf("thread %d, from = %p, to = %p\n", thread_id, start, destination);
  long loops = workload/block;
  for(int i = 0; i < ROUNDS; i++)
  {
    for(long j = 0; j < loops; j++)
    {
      memcpy(start, destination, block);
      start += block;
      destination += block;
    }
    start = parameters->start;
    destination = parameters->destination;
  }
  printf("Thread %d finish! Workload = %ld bytes, Block = %ld bytes\n", thread_id, workload, block);
}

//Random copy.
void *rcopy(void *args)
{
  struct ARGS *parameters = (struct ARGS*) args;
  int thread_id = parameters->thread_id;
  char *start = parameters->start;
  char *destination = parameters->destination;
  long workload = parameters->workload;
  long block = parameters->block;
  printf("thread %d, from = %p, to = %p\n", thread_id, start, destination);
  long loops = workload/block;
  for(int i = 0; i < ROUNDS; i++)
  {
    for(long j = 0; j < loops; j++)
    {
      long offset = *(random_num_array + j);
      memcpy(start+offset, destination+offset, block);
    }
  }
  printf("Thread %d finish! Workload = %ld bytes, Block = %ld bytes\n", thread_id, workload, block);
}

void createThreads(int number, long block, int type, long size)
{
  //Each time I allocate a new memory space for test.
  char *from = FROM;
  char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 
                     'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
                     'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
                     'y', 'z', '!', '@', '$', '#', '&', '*'};
  int index = 0;
  for(long i = 0; i < size; i++)
  {
    if(index <= 31) *(from+i) = alphabet[index++];
    else
    {
      index = rand()%(16);
      *(from+i) = alphabet[index++];
    }
  }
  char *to = TO;
  executeThreads(from, to, number, block, type, size);
}

void executeThreads(char *from, char *to, int number, long block, int type, long size)
{
  if(type == SEQUENCE) printf("---------------------------Sequential Copy, %ld bytes-------------------------\n", block);
  else printf("---------------------------Random Copy, %ld bytes-------------------------\n", block);
  printf("%d threads are creating, please wait...\n", number);
  printf("from = %p to = %p\n", from, to);
  pthread_t thread_id[number];
  int offset = 0;
  //size is the number of bytes that should be assigned to each thread.
  long workload = size/number;
  //Create an array that holds pointers of our structures.
  struct ARGS *args[number];
  if(type == RANDOM)
  {
    random_num_array = generateRandomNum(workload/block, workload, block);
  }
  struct timeval t1, t2;
  double elapsedTime;
  gettimeofday(&t1, NULL);
  for(int i = 0; i < number; i++)
  {
    args[i] = (struct ARGS*)malloc(sizeof(struct ARGS));
    args[i]->thread_id = i+1;
    args[i]->start = from + offset;
    args[i]->destination = to + offset;
    args[i]->workload = workload;
    args[i]->block = block;
    offset += workload;
    printf("thread%d, workload = %ld bytes\n", args[i]->thread_id, args[i]->workload);
    if(type == SEQUENCE) pthread_create(&thread_id[i], NULL, scopy, args[i]);
    else pthread_create(&thread_id[i], NULL, rcopy, args[i]);
  }

  for(int i = 0; i < number; i++)
  {
    pthread_join(thread_id[i], NULL);
  }
  gettimeofday(&t2, NULL);
  elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
  elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0/1000.0;   // us to s
  double throughput = (double) ROUNDS/(elapsedTime/1000.0);
  double latency = (double) elapsedTime*10/SIZE;
  printf("----------------------------------------------------------------------------\n");
  printf("| time = %f s, throughput = %f giga/s, latency = %f us |\n", elapsedTime/1000.0, throughput, latency);
  printf("----------------------------------------------------------------------------\n\n\n");
  //Though struct array that holds pointers to our structures is 
  //stored in stack, but structures are saved in heap. So we must
  //relase those memory.
  for(int i = 0; i < number; i++) free(args[i]);
  //Don't forget to free random_num_array.
  free(random_num_array);
}

void memoryTest()
{
  long block[] = {1024, 1048576, 10485760};
  int thread_number[] = {1, 2, 4, 8};
  
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      createThreads(thread_number[j], block[i], SEQUENCE, SIZE);
    }
  }
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      createThreads(thread_number[j], block[i], RANDOM, SIZE);
    }
  }
}

void latencyTest()
{
  int thread_number[] = {1, 2, 4, 8};
  for(int i = 0; i < 4; i++)
  {
    createThreads(thread_number[i], 1, SEQUENCE, LATENCY_TEST);
  }
  for(int i = 0; i < 4; i++)
  {
    createThreads(thread_number[i], 1, RANDOM, LATENCY_TEST);
  }
}

char *createBlock(long size)
{
  char *block = (char*)malloc(sizeof(char)*size);
  return block;
}
