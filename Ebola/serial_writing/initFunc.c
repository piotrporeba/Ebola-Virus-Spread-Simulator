/*
 * Create cells and find neighbors using an individual array for 8 positions,
 */
void longCreate() {
  int x, y;
  for (x = 0; x < cellCount; x++) {
    for (y = 0; y < cellCount; y++) {
      cell c = cellDefault;

      c.mortalityChance = rand() % (90 + 1 - 25) + 25;

      /*
       * Higher number (1000) reduces chance for inital infection
       */
      if (rand() % 10000 - c.infectionChance == 0)
	c.currentState = 0;

      // Left, Right, Top, Bottom
      c.leftNeighbor[0] = (x - 1 + cellCount) % cellCount;
      c.leftNeighbor[1] = y;

      c.rightNeighbor[0] = (x + 1) % cellCount;
      c.rightNeighbor[1] = y;

      c.topNeighbor[0] = x;
      c.topNeighbor[1] = (y - 1 + cellCount) % cellCount;

      c.bottomNeighbor[0] = x;
      c.bottomNeighbor[1] = (y + 1) % cellCount;

      // Top Left, Top Right
      c.topLeftNeighbor[0] = (x - 1 + cellCount) % cellCount;
      c.topLeftNeighbor[1] = (y - 1 + cellCount) % cellCount;

      c.topRightNeighbor[0] = (x + 1) % cellCount;
      c.topRightNeighbor[1] = (y - 1 + cellCount) % cellCount;

      // Bottom Left, Bottom Right
      c.bottomLeftNeighbor[0] = (x - 1 + cellCount) % cellCount;
      c.bottomLeftNeighbor[1] = (y + 1) % cellCount;

      c.bottomRightNeighbor[0] = (x + 1) % cellCount;
      c.bottomRightNeighbor[1] = (y + 1) % cellCount;

      cells[x][y] = c;
    }
  }
}

/*
 * Create cells and find neigbors using two arrays for 8 positions.
 *
 * Needs Work.
 */
void shortCreate() {
  int x, y, i, j, n = 0;
  for (x = 0; x < cellCount; x++) {
    for (y = 0; y < cellCount; y++) {
      cell c = cellDefault;

      c.mortalityChance = rand() % (90 + 1 - 25) + 25;

      if (rand() % 1000 - c.infectionChance == 0)
	c.currentState = 0;

      for (j = -1; j <= 1; j++) {
	for (i = -1; i <= 1; i++) {
	  if (i == 0 && j == 0)
	    continue;

	  int nx = (x + i + cellCount) % cellCount;
	  int ny = (y + j + cellCount) % cellCount;

	  c.neighborX[n] = nx;
	  c.neighborY[n] = ny;

	  if (n++ > 8)
	    n = 0;
	}
      }

      cells[x][y] = c;
    }
  }
}

void createCells() {
  if (isLong == 1)
    longCreate();
  else
    shortCreate();
}
