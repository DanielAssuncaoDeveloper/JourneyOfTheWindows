#ifndef MAP_H
#define MAP_H

#include "Actor.h"

struct Position {
  int xPosition;
  int yPosition;
  struct Actor actor;
};

struct Map {
  int height;
  int width;
  struct Position** positions;
};

#endif