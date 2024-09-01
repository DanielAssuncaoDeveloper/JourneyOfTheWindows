#ifndef MAP_H
#define MAP_H

struct Position {
  int xPosition;
  int yPosition;
};

struct Map {
  int height;
  int width;
  struct Position** positions;
  struct Entity* entities;
};

#endif