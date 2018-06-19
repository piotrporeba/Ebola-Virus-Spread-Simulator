cell recoveryCheck(cell c) {
  c.daysInfected++;

  /*
   * Days for symptons to arise (I saw betwenn 10 and 25 days). Some sites differ.
   * who.int/mediacentre/factsheets/fs103/en (Says 2 and 21 days).
   */
  /*
   * Chance of recovery is 12% so rand() is % 100 - 12 (88).
   */
  if (rand() % 100 - 12 == 0) {
    c.toChangeState = 1;
    c.nextState = 2;
    return c;
  }

  if (rand() % 100 < 20) {
    /*
     * Infection has lasted for x amount of days, yah ded!
     * Edit: Used to be based on the infection lasting 100 days or more.
     * Information suggests a mortaility rate of 25% to 90% from multiple online sources.
     * Mortaility chance of a cell will be set during the initialisation step.
     */
    c.toChangeState = 1;
    c.nextState = 3;
    return c;
  }

  /*
   * Otherwise, just return the same cell.
   */
  return c;
}

cell longCheck(cell c) {
  /*
   * May change cell state if already infected. Possibilities are 2 and 3 ("Recovered" and "Dead")
   */
  if (c.currentState == 0) {
    c = recoveryCheck(c);
    return c;
  }

  /*
   * If susceptible, try that whole infection shit.
   * Chance is 100 - infectionChance (3)(97)
   */
  int chance = 10;

  if(cells[c.leftNeighbor[0]][c.leftNeighbor[1]].currentState == 0) {
    if(rand() % chance == 0) {
      c.toChangeState = 1;
      c.nextState = 0;
    }
  }

  if(cells[c.rightNeighbor[0]][c.rightNeighbor[1]].currentState == 0) {
    if(rand() % chance == 0) {
      c.toChangeState = 1;
      c.nextState = 0;
    }
  }

  if(cells[c.bottomNeighbor[0]][c.bottomNeighbor[1]].currentState == 0) {
    if(rand() % chance == 0) {
      c.toChangeState = 1;
      c.nextState = 0;
    }
  }

  if(cells[c.topNeighbor[0]][c.topNeighbor[1]].currentState == 0) {
    if(rand() % chance == 0) {
      c.toChangeState = 1;
      c.nextState = 0;
    }
  }

  if(cells[c.topLeftNeighbor[0]][c.topLeftNeighbor[1]].currentState == 0) {
    if(rand() % chance == 0) {
      c.toChangeState = 1;
      c.nextState = 0;
    }
  }

  if(cells[c.topRightNeighbor[0]][c.topRightNeighbor[1]].currentState == 0) {
    if(rand() % chance == 0) {
      c.toChangeState = 1;
      c.nextState = 0;
    }
  }

  if(cells[c.bottomLeftNeighbor[0]][c.bottomLeftNeighbor[1]].currentState == 0) {
    if(rand() % chance == 0) {
      c.toChangeState = 1;
      c.nextState = 0;
    }
  }

  if(cells[c.bottomRightNeighbor[0]][c.bottomRightNeighbor[1]].currentState == 0) {
    if(rand() % chance == 0) {
      c.toChangeState = 1;
      c.nextState = 0;
    }
  }

  return c;
}

/*
 * Probably needs work too.
 */
cell shortCheck(cell c) {
  /*
   * May change cell state if already infected. Possibilities are 2 and 3 ("Recovered" and "Dead")
   */
  if (c.currentState == 0) {
    c = recoveryCheck(c);
    return c;
  }

  int chance = 100 - c.infectionChance;

  int i;
  for (i = 0; i < 8; i++) {
    int nx = c.neighborX[i];
    int ny = c.neighborY[i];

    if (cells[nx][ny].currentState == 3)
      continue;

    if (cells[nx][ny].currentState == 0) {
      if (rand() % chance == 0) {
	c.toChangeState = 1;
	c.nextState = 0;
      }
    }
  }

  return c;
}
