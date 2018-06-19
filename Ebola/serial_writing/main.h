#include <gtk/gtk.h>
#include "cell.h"

/*
 * Ebola stuff
 */
cell cells[200][200];
int cellCount = 200;
int totalCells;

int currentIteration = 0, currentDead, currentRecovered, lastDead, lastRecovered;
int numOfUnchangedIterations = 0;

int hasEnded = 0, hasWindow = 1, isLong = 1;
