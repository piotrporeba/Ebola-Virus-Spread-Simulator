struct cell_s {
  /*
   * 0 = infected
   * 1 = susceptible
   * 2 = recovered
   * 3 = dead
   */
  int currentState, infectionChance, mortalityChance;
  int toChangeState, nextState;
  int daysInfected;

  int neighborX[8];
  int neighborY[8];

  int leftNeighbor[2];
  int rightNeighbor[2];
  int topNeighbor[2];
  int bottomNeighbor[2];
  int topLeftNeighbor[2];
  int topRightNeighbor[2];
  int bottomLeftNeighbor[2];
  int bottomRightNeighbor[2];
} cellDefault = {1, 3};

typedef struct cell_s cell;
