#include "Map.h"

#ifndef ACTOR_H
#define ACTOR_H

enum TypeActor {
    HERO,
    ENEMY
  };

struct Actor {
    char name[100];
    struct Position* position;
    enum TypeActor type;
};

#endif //ACTOR_H
