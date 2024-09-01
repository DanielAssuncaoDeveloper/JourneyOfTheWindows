#ifndef ENTITY_H
#define ENTITY_H

#include "Actor.h"
#include "Object.h"

enum TypeEntity {
    ACTOR,
    OBJECT
};

enum Direction {
    NONE,   // -
    UP,     // ^
    RIGHT,  // >
    DOWN,   // v
    LEFT    // <
};

struct Entity {
    int id;
    enum Direction direction;
    struct Position* position;

    enum TypeEntity type;
    struct Actor actor;
    struct Object object;
};

struct EntityMapper {
    struct Position position;
    struct Entity entity;
};

#endif //ENTITY_H
