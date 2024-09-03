
#ifndef ENTITYSERVICE_H
#define ENTITYSERVICE_H

enum Direction {
    NONE,   // -
    UP,     // ^
    RIGHT,  // >
    DOWN,   // v
    LEFT    // <
};

struct Entity {
    enum Direction direction;
    struct Position* position;
};

struct Entity* get_pointer_to_array_entities(int lentgh);

#endif //ENTITYSERVICE_H
