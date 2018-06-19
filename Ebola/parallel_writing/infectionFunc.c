#include "infectionFunc.h"
#include "neighborCheckFunc.c"
#include "stateCheckFunc.c"

void createThreads() {
  threadHandles = malloc(threadCount * sizeof(pthread_t));

  for (thread = 0; thread < threadCount; thread++)
    pthread_create(threadHandles, NULL, &runIteration, (void *)thread);
}

/*
 * If cell state is "Infected, "Recovered", or "Dead", don't check.
 * Else, check when "Susceptible".
 */
void beAffectedByNeighbors (int x, int y) {
  cell c = cells[x][y];

  lastDead = currentDead;
  lastRecovered = currentRecovered;

  /*
   * If recovered or dead, don't bother.
   */
  if (c.currentState == 2 || c.currentState == 3)
    return;

  /*
   * See neighborCheckFunc.c
   */
  if (isLong == 1)
    cells[x][y] = longCheck(c);
  else
    cells[x][y] = shortCheck(c);
}

/*
 * If no cells are left alive, end the program.
 * Else for each cell, be affected by neighbors.
 *
 * If cells are unchanged for 100 iterations, end the program.
 * Else update the states and iterate.
 */
void *runIteration(void *param) {
  if (hasEnded == 0)
    checkEnd();

  if (hasEnded == 1)
    return;

  long rank = (long)param;
  /*
   * Vertical slices rather than squares in each corner.
   */
  int minX = (cellCount / threadCount) * rank;
  int maxX = (cellCount / threadCount) * (rank + 1);

  /*
   * If we did 8 threads. Four above - four below.
  int minY = (rank < threadCount / 2) ? 0 : cellCount / 2;
  int maxY = (rank < threadCount / 2) ? cellCount / 2 : cellCount;
  */

  int x, y;
  for (x = minX; x < maxX; x++)
    for (y = 0; y < cellCount; y++)
      beAffectedByNeighbors (x, y);

  if(rank == 0)
    isReady0++;
  else if(rank == 1)
    isReady1++;
  else if(rank == 2)
    isReady2++;
  else if(rank == 3)
    isReady3++;

  if(isReady0+isReady1+isReady2+isReady3 == 4) {
    isReady0 = 0;
    isReady1 = 0;
    isReady2 = 0;
    isReady3 = 0;

    writeToFile();

    int i;
    for (i = 0; i < threadCount; i++)
      runIteration((void *)i);
  }
}

void writeToFile() {
  char name[20];
  sprintf(name, "textfiles/%d.txt", currentIteration);
  
  /*
   * w = write
   * a = append
   */
  FILE *f = fopen(name, "w");

  /*
   * Write each value to file.
   */
  int x, y;
  for (x = 0; x < cellCount; x++)
    for (y = 0; y < cellCount; y++)
      fprintf(f, "%d", cells[x][y].currentState);

  int alive = totalCells - currentDead;
  int inf = alive - currentRecovered;
  fprintf(f, "\n\n%d Susceptible \n%d Infected \n%d Recovered \n%d Dead", alive, inf, currentRecovered, currentDead);
  fclose(f);

  updateCellStates();
  currentIteration++;
}

void checkEnd() {
  if (lastRecovered == currentRecovered && lastDead == currentDead) {
    numOfUnchangedIterations++;
    if (numOfUnchangedIterations == 500)
      endProgram();
  } else {
    numOfUnchangedIterations = 0;
  }
}

/*
 * Print last iteration, and cells that recovered.
 */
void endProgram() {
  hasEnded = 1;

  /*
   * Segmentation Fault
  for (thread = 0; thread < threadCount; thread++)
    pthread_join(threadHandles[thread], NULL);
  */

  free(threadHandles);

  /* Prints iteration with final 500 from unchangedIterations*/
  //printf("%c%d\t%c%d\t%c%d\n", 'I', currentIteration, 'D', currentDead, 'R', currentRecovered);

  /* Prints iteration when we see the program end */
  printf("%c%d\t%c%d\t%c%d\n", 'I', currentIteration - 500, 'D', currentDead, 'R', currentRecovered);
}
