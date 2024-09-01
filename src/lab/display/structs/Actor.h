#include "Map.h"

#ifndef ACTOR_H
#define ACTOR_H

enum TypeActor {
    HERO,
    ENEMY
};

struct Actor {
    char* name;
    enum TypeActor type;
};

#endif //ACTOR_H
