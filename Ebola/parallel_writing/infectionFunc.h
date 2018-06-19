#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void createThreads();
void beAffectedByNeighors(int x, int y);
void *runIteration(void *);
void writeToFile();
void checkEnd();
void endProgram();

int threadCount = 4;
int isReady0 = 0;
int isReady1 = 0;
int isReady2 = 0;
int isReady3 = 0;

long thread;
pthread_t *threadHandles;
